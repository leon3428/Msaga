#include "SyntaxTree.h"
#include "Expressions.h"
#include "Global.h"
#include "Utils.h"

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
                    m_exprType.push_front(PrimitiveExprType::Int);
                    m_isLValue = false;
                    break;
                
                case UniformCharacter::Character:
                    m_exprType.push_front(PrimitiveExprType::Char);
                    m_isLValue = false;
                    break;

                case UniformCharacter::CharacterArray:
                    m_exprType.push_front(PrimitiveExprType::Char);
                    m_exprType.push_front(PrimitiveExprType::Const);
                    m_exprType.push_front(PrimitiveExprType::Array);
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