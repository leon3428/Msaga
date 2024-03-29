#include "Common.hpp"
#include "SyntaxTree.hpp"

// true if a can be implicitly converted to b
bool Msaga::implicitlyConvertible(ExprType a, ExprType b) {
    if(a == b)
        return true;

    //const
    if(a == ExprType::ConstInt && b == ExprType::Int)
        return true;
    if(a == ExprType::Int && b == ExprType::ConstInt)
        return true;

    if(a == ExprType::ConstChar && b == ExprType::Char)
        return true;
    if(a == ExprType::Char && b == ExprType::ConstChar)
        return true;

    //char
    if(a == ExprType::Char && b == ExprType::Int)
        return true;
    if(a == ExprType::Char && b == ExprType::ConstInt)
        return true;
    if(a == ExprType::ConstChar && b == ExprType::Int)
        return true;
    if(a == ExprType::ConstChar && b == ExprType::ConstInt)
        return true;

    //array
    if(a == ExprType::ArrayInt && b == ExprType::ArrayConstInt)
        return true;

    if(a == ExprType::ArrayChar && b == ExprType::ArrayConstChar)
        return true;

    return false;
}

bool Msaga::explicitlyConvertible(ExprType a, ExprType b) {
    if(implicitlyConvertible(a,b))
        return true;
    if(a == ExprType::Int && b == ExprType::Char)
        return true;
    if(a == ExprType::Int && b == ExprType::ConstChar)
        return true;
    if(a == ExprType::ConstInt && b == ExprType::Char)
        return true;
    if(a == ExprType::ConstInt && b == ExprType::ConstChar)
        return true;

    return false;
}

ExprType Msaga::arrayBaseType(ExprType a) {
    if(a == ExprType::ArrayChar)
        return ExprType::Char;

    if(a == ExprType::ArrayInt)
        return ExprType::Int;

    if(a == ExprType::ArrayConstChar)
        return ExprType::ConstChar;

    if(a == ExprType::ArrayConstInt)
        return ExprType::ConstInt;

    return ExprType::Void;
}

ExprType Msaga::baseTypeToArray(ExprType a) {
    if(a == ExprType::Char)
        return ExprType::ArrayChar;

    if(a == ExprType::Int)
        return ExprType::ArrayInt;

    if(a == ExprType::ConstChar)
        return ExprType::ArrayConstChar;

    if(a == ExprType::ConstInt)
        return ExprType::ArrayConstInt;

    return ExprType::Void;
}

Msaga::FunctionType::FunctionType(const std::vector<ExprType> &argsTypes, ExprType retType) 
    : argumentsTypes(argsTypes), returnType(retType) {}

bool Msaga::isValidChar(const std::string &s) {
    if(s.size() == 3 && s[1] != '\\')
        return true;
    if(s.size() == 4 && (s == "'\\t'" || s == "'\\n'" || s == "'\\0'" || s == "'\\''" || s == "'\\\"'" || s == "'\\\\'"))
        return true;
    return false;
}

bool Msaga::isValidCharArray(const std::string &s) {
    for(size_t i = 1;i < s.size() - 1; i++) {
        if(s[i] == '\\') {
            if(i + 1 >= s.size() - 1)
                return false;
            if(s[i+1] != 't' && s[i+1] != 'n' && s[i+1] != '0' && s[i+1] != '\'' && s[i+1] != '\"' && s[i+1] != '\\')
                return false;
            i++;
        }
    }
    return true;
}

std::string Msaga::exprTypeToString(ExprType t) {
    if(t == ExprType::Int)
        return "Int";
    if(t == ExprType::Char)
        return "Char";
    if(t == ExprType::ConstChar)
        return "ConstChar";
    if(t == ExprType::ConstInt)
        return "ConstInt";
    if(t == ExprType::ArrayChar)
        return "ArrayChar";
    if(t == ExprType::ArrayInt)
        return "ArrayInt";
    if(t == ExprType::ArrayConstChar)
        return "ArrayConstChar";
    if(t == ExprType::ArrayConstInt)
        return "ArrayConstInt";
    if(t == ExprType::Function)
        return "Function";
    
    return "Error";
}

std::map<int, int> Msaga::constants;

void Msaga::allChildrenGenerateCode(std::ostream& stream, SyntaxTreeNode *node) {
    for(size_t i = 0;i < node -> getChildrenCnt(); i++)
        node -> getChild(i) -> generateCode(stream);
}

int Msaga::getConstLabelId(int constant) {
    if(constants.find(constant) == constants.end())
        constants[constant] = constants.size();

    return constants[constant];
}

static int tempLabelCounter = 0;

int Msaga::getTmpLabelId() {
    return tempLabelCounter++;
}

void Msaga::loadVarToReg(std::ostream& stream, SyntaxTreeNode *node, std::string_view rd, const std::string &name, std::string_view offsetReg) {
    auto [localOffset, isGlobal] = node -> getLocalContextNode() -> getOffset(name);
    auto exprType = node -> getLocalContextNode() -> getIdentifier(name) -> exprType;

    if(localOffset < 0 && Msaga::isArrayType(exprType)) {
        stream << '\t' << "LOAD R3, (R6+0" << localOffset * -1 << ")\n"; // load pointer to reg
        stream << '\t' << "ADD R3, " << offsetReg << ", R3\n";
        stream << '\t' << "LOAD " << rd << ", (R3)\n";
        return;
    }

    char sign = '-';
    if(localOffset < 0) {
        localOffset *= -1;
        sign = '+';
    }
    
    if(isGlobal) { 
        if(offsetReg != ""){
            stream << '\t' << "MOVE 040000, R3\n";
            stream << '\t' << "ADD R3, " << offsetReg << ", R3\n";
            stream << '\t' << "LOAD " << rd << ", (R3" << sign << "0" << std::hex << localOffset << ")\n";
        } else {
            stream << '\t' << "LOAD " << rd << ", (" << std::hex << 0x40000 - localOffset << ")\n";
        }
    } else {
        if(offsetReg != "") {
            stream << '\t' << "ADD R6, " << offsetReg << ", R3\n";
            stream << '\t' << "LOAD " << rd << ", (R3" << sign << '0' << std::hex << localOffset << ")\n";
        } else {
            stream << '\t' << "LOAD " << rd << ", (R6" << sign << '0' << std::hex << localOffset << ")\n";
        }
        
    }
}

void Msaga::storeRegToVar(std::ostream& stream, SyntaxTreeNode *node, std::string_view rs, const std::string &name, std::string_view offsetReg) {
    auto [localOffset, isGlobal] = node -> getLocalContextNode() -> getOffset(name);
    auto exprType = node -> getLocalContextNode() -> getIdentifier(name) -> exprType;

    if(localOffset < 0 && Msaga::isArrayType(exprType)) {
        stream << '\t' << "LOAD R3, (R6+0" << localOffset * -1 << ")\n"; // load pointer to reg
        stream << '\t' << "ADD R3, " << offsetReg << ", R3\n";
        stream << '\t' << "STORE " << rs << ", (R3)\n";
        return;
    }

    char sign = '-';
    if(localOffset < 0) {
        localOffset *= -1;
        sign = '+';
    }

    if(isGlobal) {
        if(offsetReg != ""){
            stream << '\t' << "MOVE 040000, R3\n";
            stream << '\t' << "ADD R3, " << offsetReg << ", R3\n";
            stream << '\t' << "STORE " << rs << ", (R3" << sign << "0" << std::hex << localOffset << ")\n";
        } else {
            stream << '\t' << "STORE " << rs << ", (" << std::hex << 0x40000 - localOffset << ")\n";
        }
    }
    else {
        if(offsetReg != "") {
            stream << '\t' << "ADD R6, " << offsetReg << ", R3\n";
            stream << '\t' << "STORE " << rs << ", (R3" << sign << '0' << std::hex << localOffset << ")\n";
        } else {
            stream << '\t' << "STORE " << rs << ", (R6" << sign << '0' << std::hex << localOffset << ")\n";
        }
    }
}

void Msaga::blockOffsetHelper(ContextNode *node, int& offset) {
    node -> setBlockOffset(offset);
    offset += node -> getMaxOffset() - 4;

    for(int i = 0;i < node -> getChildrenCnt();i++) {
        Msaga::blockOffsetHelper(node -> getChild(i), offset);
    }
}