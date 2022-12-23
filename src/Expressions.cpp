#include "SyntaxTree.h"
#include "Expressions.h"
#include "Global.h"
#include "Utils.h"

// Expression
GenericExpression::GenericExpression(const std::string &exprType, bool isLValue)
    : m_exprType(exprType), m_isLValue(isLValue) {}


// Primary expression
PrimaryExpression::PrimaryExpression(const std::string &exprType, bool isLValue)
    : GenericExpression(exprType, isLValue) {}

bool PrimaryExpression::check() {
    if(m_children.size() == 1) {
        if(Leaf *leaf = dynamic_cast<Leaf*>(m_children[0].get())) {
            
            switch(leaf -> getUniformCharacter()) {
                case UniformCharacter::Idn:
                    if(!identifierTableContains(leaf -> getLexicalUnit()))
                        return false;

                    m_exprType = identifierTable[leaf -> getLexicalUnit()].type;
                    m_isLValue = identifierTable[leaf -> getLexicalUnit()].LValue;
                    break;

                case UniformCharacter::Number:
                    m_exprType = "int";
                    m_isLValue = false;
                    break;
                
                case UniformCharacter::Character:
                    m_exprType = "char";
                    m_isLValue = false;
                    break;

                case UniformCharacter::CharacterArray:
                    m_exprType = "array(const(char))";
                    m_isLValue = false;
                    break;

                default:
                    return false;
            }
        }
    } else if(m_children.size() == 3) {
        // TODO: implement this rule
    } else {
        return false;
    }
    


    return true;
}