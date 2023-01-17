#include "SyntaxTree.hpp"
#include <iostream>
#include <stack>
#include <sstream>
#include "Serialization.hpp"
#include "Leafs.hpp"
#include "Commands.hpp"
#include "OtherNodes.hpp"
#include "Expressions.hpp"

void SyntaxTreeNode::m_errorHandler() {
    std::cout << Msaga::NodeTypeToString(this -> getNodeType()) << " ::=";
    for(size_t i = 0;i < m_children.size();i++) {
        std::cout << ' ' << Msaga::NodeTypeToString(m_children[i] -> getNodeType());

        if(Msaga::isLeaf(m_children[i] -> getNodeType())) {
            GenericLeaf *l = static_cast<GenericLeaf*>(m_children[i].get());
            std::cout << '(' << l -> getRow() << ',' << l -> getLexicalUnit() << ')';
        }
    }

    std::cout << '\n';
    exit(1);
}

void SyntaxTreeNode::generateCode(std::ostream& stream) {
    Msaga::allChildrenGenerateCode(stream, this);
}

StackItem::StackItem(SyntaxTreeNode *n, int indLevel, bool inLoop, ExprType funRetType, int charArrayLen)
    : node(n), indentLevel(indLevel), insideLoop(inLoop), functionReturnType(funRetType), characterArrayLength(charArrayLen) {}

void SyntaxTree::load(std::istream &stream) {
    std::stack<StackItem> node_stack;

    std::string line;
    getline(stream, line);
    m_root = std::make_unique<TranslationUnit>();
    m_contextNodes.push_back(std::make_unique<ContextNode>(nullptr));
    m_root -> setLocalContextNode(m_contextNodes.back().get());
    node_stack.push({m_root.get(), 0, false, ExprType::Error, -1});

    while(getline(stream, line)) {
        int indent_level = 0;
        while(line[indent_level++] == ' ') {}
        indent_level --;

        std::istringstream iss(line);

        while(node_stack.top().indentLevel > indent_level - 1) {
            int length = node_stack.top().characterArrayLength;
            if(node_stack.top().node -> getChildrenCnt() != 1)
                length = -1;

            if(node_stack.top().node -> getNodeType() == NodeType::AssignmentExpression) {
                AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(node_stack.top().node);
                aExpr -> setCharacterArrayLength(length);
                length = -1;
            }
            node_stack.pop();
            node_stack.top().characterArrayLength = length;
        }

        if(line[indent_level] == '<') {
            // inner node
            std::string ch;
            iss >> ch;

            SyntaxTreeNode *parent = node_stack.top().node;
            auto p = Msaga::constructInnerNode(ch, parent);



            if(ch == "<slozena_naredba>" && parent -> getNodeType() == NodeType::Command) {
                m_contextNodes.push_back(std::make_unique<ContextNode>(parent -> getLocalContextNode()));
                p -> setLocalContextNode(m_contextNodes.back().get());
            } else if(ch == "<definicija_funkcije>") {
                m_contextNodes.push_back(std::make_unique<ContextNode>(parent -> getLocalContextNode()));
                p -> setLocalContextNode(m_contextNodes.back().get());
            } else {
                p -> setLocalContextNode(parent -> getLocalContextNode());
            }

            bool inside_loop = node_stack.top().insideLoop;
            if(ch == "<naredba_petlje>")
                inside_loop = true;

            ExprType function_ret_type = node_stack.top().functionReturnType;
            if(ch == "<slozena_naredba>" && parent -> getNodeType() == NodeType::FunctionDefinition) {
                parent -> getChild(0) -> check();
                TypeName *tn = static_cast<TypeName*>(parent -> getChild(0));
                function_ret_type = tn -> getExprType();
            }

            if(ch == "<naredba_skoka>") {
                JumpCommand *jc = static_cast<JumpCommand*>(p);
                jc -> setInsideLoop(inside_loop);
                jc -> setFunctionReturnType(function_ret_type);
            }

            node_stack.push({p, indent_level, inside_loop, function_ret_type, -1});
        } else {
            // leaf
            std::string ch, lexicalUnit;
            int row;
            iss >> ch >> row >> lexicalUnit;

            if(ch == "NIZ_ZNAKOVA")
                node_stack.top().characterArrayLength = lexicalUnit.size() - 2;

            Msaga::constructLeafNode(ch, row, lexicalUnit, node_stack.top().node);
        }
    }
}


void SyntaxTree::m_printHelper(SyntaxTreeNode *node, int indent_level) {
    std:: cout << std::string(indent_level, '-') << Msaga::NodeTypeToString(node -> getNodeType()) << ' ' << node -> getLocalContextNode() << '\n';
    if(node -> getNodeType() == NodeType::JumpCommand) {
        JumpCommand *jc = static_cast<JumpCommand*>(node);
        std::cout << jc -> isInsideLoop() << ' ' << Msaga::exprTypeToString(jc -> getFunctionReturnType()) << '\n';
    }

    if(node -> getNodeType() == NodeType::AssignmentExpression) {
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(node);
        std::cout << aExpr -> getCharacterArrayLength() << '\n';
    }

    for(size_t i = 0;i < node -> getChildrenCnt(); i++)
        m_printHelper(node -> getChild(i), indent_level + 1);
}

void SyntaxTree::check() {
    m_root -> check();

    Identifier *idn = m_contextNodes[0] -> getIdentifier("main");
    if(idn == nullptr || 
       idn -> functionType -> argumentsTypes.size() != 1 || 
       idn -> functionType -> argumentsTypes[0] != ExprType::Void || 
       idn -> functionType -> returnType != ExprType::Int)
    {
        std::cout << "main" << std::endl;
        return;
    }

    bool allDefined = true;
    ContextNode *globalContext = m_contextNodes[0].get();
    for(size_t i = 0;i < m_contextNodes.size(); i++) {
        allDefined = allDefined && m_contextNodes[i] -> allDefined(globalContext);
    }
    if(!allDefined)
        std::cout << "funkcija" << std::endl;
}


void SyntaxTree::generateCode(std::ostream &stream) const {
    stream << "p_start ";
    stream << '\t' << "MOVE 40000, R7\n";

    auto idn = m_root -> getLocalContextNode() -> getIdentifier("main");
    stream << '\t' << "PUSH R6\n";
    stream << '\t' << "CALL func" << idn -> id << '\n';
    stream << '\t' << "POP R6\n";
    stream << '\t' << "MOVE R5, R6\n";
    stream << '\t' << "HALT\n\n"; 

    for(auto [constant, id] : Msaga::constants){
        stream << "const" << id << " DW 0" << std::hex << constant << '\n';
	}
	stream << "funcmul\n";
	stream << "\tLOAD r1, (r6+4)\n";
	stream << "\tLOAD r0, (r6+8)\n";
	stream << "\tCMP r0, 0\n";
	stream << "\tJP_P mulpoz1\n";
	stream << "\tXOR r2, 1, r2\n";
	stream << "mulpoz1\n";
	stream << "\tCMP r1, 0\n";
	stream << "\tJP_P mulpoz2\n";
	stream << "\tXOR r2, 1, r2\n";
	stream << "mulpoz2\n";
	stream << "\tASHR R0, 31, R5\n";
	stream << "\tADD R0, R5, R0\n";
	stream << "\tXOR R0, R5, R0\n";
	stream << "\tASHR R1, 31, R5\n";
	stream << "\tADD R1, R5, R1\n";         
	stream << "\tXOR R1, R5, R1\n";
	stream << "\tMOVE 0, r5\n";
	stream << "\tCMP r1, 0\n";
	stream << "\tJP_Z loopmulend\n";
	stream << "loopmul\n";
	stream << "\tADD r5, r0, r5\n";
	stream << "\tSUB r1, 1, r1\n";
	stream << "\tCMP r1, 0\n";
	stream << "\tJP_NZ loopmul\n";
	stream << "loopmulend\n";
	stream << "\tCMP r2, 0\n";
	stream << "\tJP_Z mulend\n";
	stream << "\tMOVE -1, R0\n";
	stream << "\tXOR r5, r0, r5\n";
	stream << "\tADD r5, 1, r5\n";
	stream << "mulend\n";
	stream << "\tRET\n";

	stream << "funcdiv\n";
	stream << "\tLOAD r1, (r6+4)\n";
	stream << "\tLOAD r0, (r6+8)\n";
	stream << "\tCMP r0, 0\n";
	stream << "\tJP_P divpoz1\n";
	stream << "\tXOR r2, 1, r2\n";
	stream << "divpoz1\n";
	stream << "\tCMP r1, 0\n";
	stream << "\tJP_P divpoz2\n";
	stream << "\tXOR r2, 1, r2\n";
	stream << "divpoz2\n";
	stream << "\tASHR R0, 31, R5\n";
	stream << "\tADD R0, R5, R0\n";
	stream << "\tXOR R0, R5, R0\n";
	stream << "\tASHR R1, 31, R5\n";
	stream << "\tADD R1, R5, R1\n";         
	stream << "\tXOR R1, R5, R1\n";
	stream << "\tMOVE 0, r5\n";
	stream << "\tCMP r1, 0\n";
	stream << "\tJP_Z loopdivend\n";
	stream << "loopdiv\n";
	stream << "\tSUB r0, r1, r0\n";
	stream << "\tCMP r0, 0\n";
	stream << "\tJP_N loopdivend\n";
	stream << "\tADD r5, 1, r5\n";
	stream << "\tJP loopdiv\n";
	stream << "loopdivend\n";
	stream << "\tCMP r2, 0\n";
	stream << "\tJP_Z divend\n";
	stream << "\tMOVE -1, R0\n";
	stream << "\tXOR r5, r0, r5\n";
	stream << "\tADD r5, 1, r5\n";
	stream << "divend\n";
	stream << "\tRET\n";

	stream << "funcmod\n";
	stream << "\tLOAD r1, (r6+4)\n";
	stream << "\tLOAD r0, (r6+8)\n";
	stream << "loopmod\n";
	stream << "\tSUB r0, r1, r0\n";
	stream << "\tCMP r0, 0\n";
	stream << "\tJP_NN loopmod\n";
	stream << "\tADD r0, r1, r0\n";
	stream << "modend\n";
	stream << "\tMOVE r0, r5\n";
	stream << "\tRET\n";

    m_root -> generateCode(stream);
}


