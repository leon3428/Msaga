#include "Serialization.hpp"

std::string Msaga::NodeTypeToString(NodeType nt) {
	if(nt == NodeType::PrimaryExpression)
		return "<primarni_izraz>";
	if(nt == NodeType::Expression)
		return "<izraz>";
	if(nt == NodeType::AssignmentExpression)
		return "<izraz_pridruzivanja>";
	if(nt == NodeType::EqualsExpression)
		return "<jednakosni_izraz>";
	if(nt == NodeType::ComparisonExpression)
		return "<odnosni_izraz>";
	if(nt == NodeType::AdditiveExpression)
		return "<aditivni_izraz>";
	if(nt == NodeType::MultiplicativeExpression)
		return "<multiplikativni_izraz>";
	if(nt == NodeType::CastExpression)
		return "<cast_izraz>";
	if(nt == NodeType::LogicalOrExpression)
		return "<log_ili_izraz>";
	if(nt == NodeType::LogicalAndExpression)
		return "<log_i_izraz>";
	if(nt == NodeType::BitwiseOrExpression)
		return "<bin_ili_izraz>";
	if(nt == NodeType::BitwiseXorExpression)
		return "<bin_xili_izraz>";
	if(nt == NodeType::BitwiseAndExpression)
		return "<bin_i_izraz>";
	if(nt == NodeType::PostfixExpression)
		return "<postfiks_izraz>";
	if(nt == NodeType::UnaryExpression)
		return "<unarni_izraz>";
	if(nt == NodeType::ComplexCommand)
		return "<slozena_naredba>";
	if(nt == NodeType::ListCommand)
		return "<lista_naredbi>";
	if(nt == NodeType::Command)
		return "<naredba>";
	if(nt == NodeType::ExpressionCommand)
		return "<izraz_naredba>";
	if(nt == NodeType::BranchCommand)
		return "<naredba_grananja>";
	if(nt == NodeType::LoopCommand)
		return "<naredba_petlje>";
	if(nt == NodeType::JumpCommand)
		return "<naredba_skoka>";
	if(nt == NodeType::TranslationUnit)
		return "<prijevodna_jedinica>";
	if(nt == NodeType::ExternalDeclaration)
		return "<vanjska_deklaracija>";
	if(nt == NodeType::FunctionDefinition)
		return "<definicija_funkcije>";
	if(nt == NodeType::ParameterList)
		return "<lista_parametara>";
	if(nt == NodeType::ParameterDeclaration)
		return "<deklaracija_parametra>";
	if(nt == NodeType::DeclarationList)
		return "<lista_deklaracija>";
	if(nt == NodeType::Declaration)
		return "<deklaracija>";
	if(nt == NodeType::DeclaratorInitList)
		return "<lista_init_deklaratora>";
	if(nt == NodeType::InitDeclarator)
		return "<init_deklarator>";
	if(nt == NodeType::DirectDeclarator)
		return "<izravni_deklarator>";
	if(nt == NodeType::Initializer)
		return "<inicijalizator>";
	if(nt == NodeType::JoinExpressionList)
		return "<lista_izraza_pridruzivanja>";
	if(nt == NodeType::LeafIdn)
		return "IDN";
	if(nt == NodeType::LeafNum)
		return "BROJ";
	if(nt == NodeType::LeafCharacter)
		return "ZNAK";
	if(nt == NodeType::LeafCharArray)
		return "NIZ_ZNAKOVA";
	if(nt == NodeType::LeafComma)
		return "ZAREZ";
	if(nt == NodeType::LeafAssignment)
		return "OP_PRIDRUZI";
	if(nt == NodeType::LeafLogOr)
		return "OP_ILI";
	if(nt == NodeType::LeafLogAnd)
		return "OP_I";
	if(nt == NodeType::LeafBitOr)
		return "OP_BIN_ILI";
	if(nt == NodeType::LeafBitXor)
		return "OP_BIN_XILI";
	if(nt == NodeType::LeafBitAnd)
		return "OP_BIN_I";
	if(nt == NodeType::LeafEq)
		return "OP_EQ";
	if(nt == NodeType::LeafNeq)
		return "OP_NEQ";
	if(nt == NodeType::LeafLt)
		return "OP_LT";
	if(nt == NodeType::LeafGt)
		return "OP_GT";
	if(nt == NodeType::LeafLte)
		return "OP_LTE";
	if(nt == NodeType::LeafGte)
		return "OP_GTE";
	if(nt == NodeType::LeafRightBracket)
		return "D_ZAGRADA";
	if(nt == NodeType::LeafLeftBracket)
		return "L_ZAGRADA";
	if(nt == NodeType::LeafRightSquareBracket)
		return "D_UGL_ZAGRADA";
	if(nt == NodeType::LeafLeftSquareBracket)
		return "L_UGL_ZAGRADA";
	if(nt == NodeType::LeafLeftCurlyBracket)
		return "L_VIT_ZAGRADA";
	if(nt == NodeType::LeafRightCurlyBracket)
		return "D_VIT_ZAGRADA";
	if(nt == NodeType::LeafPlus)
		return "PLUS";
	if(nt == NodeType::LeafMinus)
		return "MINUS";
	if(nt == NodeType::LeafMult)
		return "OP_PUTA";
	if(nt == NodeType::LeafDiv)
		return "OP_DIJELI";
	if(nt == NodeType::LeafMod)
		return "OP_MOD";
	if(nt == NodeType::LeafInc)
		return "OP_INC";
	if(nt == NodeType::LeafDec)
		return "OP_DEC";
	if(nt == NodeType::LeafSemicolon)
		return "TOCKAZAREZ";
	if(nt == NodeType::LeafTilde)
		return "OP_TILDA";
	if(nt == NodeType::LeafNeg)
		return "OP_NEG";
	if(nt == NodeType::LeafKwIf)
		return "KR_IF";
	if(nt == NodeType::LeafKwElse)
		return "KR_ELSE";
	if(nt == NodeType::LeafKwWhile)
		return "KR_WHILE";
	if(nt == NodeType::LeafKwFor)
		return "KR_FOR";
	if(nt == NodeType::LeafKwConst)
		return "KR_CONST";
	if(nt == NodeType::LeafKwInt)
		return "KR_INT";
	if(nt == NodeType::LeafKwChar)
		return "KR_CHAR";
	if(nt == NodeType::LeafKwVoid)
		return "KR_VOID";
	if(nt == NodeType::LeafKwContinue)
		return "KR_CONTINUE";
	if(nt == NodeType::LeafKwBreak)
		return "KR_BREAK";
	if(nt == NodeType::LeafKwReturn)
		return "KR_RETURN";
	if(nt == NodeType::TypeName)
		return "<ime_tipa>";
	if(nt == NodeType::TypeSpecifier)
		return "<specifikator_tipa>";
	if(nt == NodeType::UnaryOperator)
		return "<unarni_operator>";
	if(nt == NodeType::ArgumentList)
		return "<lista_argumenata>";
	return "error";
}

NodeType Msaga::StringToNodeType(const std::string &s) {
	if(s == "<prijevodna_jedinica>")
		return NodeType::TranslationUnit;
	if(s == "<primarni_izraz>")
		return NodeType::PrimaryExpression;
	if(s == "<postfiks_izraz>")
		return NodeType::PostfixExpression;
	if(s == "<lista_argumenata>")
		return NodeType::ArgumentList;
	if(s == "<unarni_izraz>")
		return NodeType::UnaryExpression;
	if(s == "<unarni_operator>")
		return NodeType::UnaryOperator;
	if(s == "<cast_izraz>")
		return NodeType::CastExpression;
	if(s == "<ime_tipa>")
		return NodeType::TypeName;
	if(s == "<specifikator_tipa>")
		return NodeType::TypeSpecifier;
	if(s == "<multiplikativni_izraz>")
		return NodeType::MultiplicativeExpression;
	if(s == "<aditivni_izraz>")
		return NodeType::AdditiveExpression;
	if(s == "<odnosni_izraz>")
		return NodeType::ComparisonExpression;
	if(s == "<jednakosni_izraz>")
		return NodeType::EqualsExpression;
	if(s == "<bin_i_izraz>")
		return NodeType::BitwiseAndExpression;
	if(s == "<bin_xili_izraz>")
		return NodeType::BitwiseXorExpression;
	if(s == "<bin_ili_izraz>")
		return NodeType::BitwiseOrExpression;
	if(s == "<log_i_izraz>")
		return NodeType::LogicalAndExpression;
	if(s == "<log_ili_izraz>")
		return NodeType::LogicalOrExpression;
	if(s == "<izraz_pridruzivanja>")
		return NodeType::AssignmentExpression;
	if(s == "<izraz>")
		return NodeType::Expression;
	if(s == "<slozena_naredba>")
		return NodeType::ComplexCommand;
	if(s == "<lista_naredbi>")
		return NodeType::ListCommand;
	if(s == "<naredba>")
		return NodeType::Command;
	if(s == "<izraz_naredba>")
		return NodeType::ExpressionCommand;
	if(s == "<naredba_grananja>")
		return NodeType::BranchCommand;
	if(s == "<naredba_petlje>")
		return NodeType::LoopCommand;
	if(s == "<naredba_skoka>")
		return NodeType::JumpCommand;
	if(s == "<vanjska_deklaracija>")
		return NodeType::ExternalDeclaration;
	if(s == "<definicija_funkcije>")
		return NodeType::FunctionDefinition;
	if(s == "<lista_parametara>")
		return NodeType::ParameterList;
	if(s == "<deklaracija_parametra>")
		return NodeType::ParameterDeclaration;
	if(s == "<lista_deklaracija>")
		return NodeType::DeclarationList;
	if(s == "<deklaracija>")
		return NodeType::Declaration;
	if(s == "<lista_init_deklaratora>")
		return NodeType::DeclaratorInitList;
	if(s == "<init_deklarator>")
		return NodeType::InitDeclarator;
	if(s == "<izravni_deklarator>")
		return NodeType::DirectDeclarator;
	if(s == "<inicijalizator>")
		return NodeType::Initializer;
	if(s == "<lista_izraza_pridruzivanja>")
		return NodeType::JoinExpressionList;
	if(s == "IDN")
		return NodeType::LeafIdn;
	if(s == "BROJ")
		return NodeType::LeafNum;
	if(s == "ZNAK")
		return NodeType::LeafCharacter;
	if(s == "NIZ_ZNAKOVA")
		return NodeType::LeafCharArray;
	if(s == "KR_BREAK")
		return NodeType::LeafKwBreak;
	if(s == "KR_CHAR")
		return NodeType::LeafKwChar;
	if(s == "KR_CONST")
		return NodeType::LeafKwConst;
	if(s == "KR_CONTINUE")
		return NodeType::LeafKwContinue;
	if(s == "KR_ELSE")
		return NodeType::LeafKwElse;
	if(s == "KR_FOR")
		return NodeType::LeafKwFor;
	if(s == "KR_IF")
		return NodeType::LeafKwIf;
	if(s == "KR_INT")
		return NodeType::LeafKwInt;
	if(s == "KR_RETURN")
		return NodeType::LeafKwReturn;
	if(s == "KR_VOID")
		return NodeType::LeafKwVoid;
	if(s == "KR_WHILE")
		return NodeType::LeafKwWhile;
	if(s == "PLUS")
		return NodeType::LeafPlus;
	if(s == "OP_INC")
		return NodeType::LeafInc;
	if(s == "MINUS")
		return NodeType::LeafMinus;
	if(s == "OP_DEC")
		return NodeType::LeafDec;
	if(s == "OP_PUTA")
		return NodeType::LeafMult;
	if(s == "OP_DIJELI")
		return NodeType::LeafDiv;
	if(s == "OP_MOD")
		return NodeType::LeafMod;
	if(s == "OP_PRIDRUZI")
		return NodeType::LeafAssignment;
	if(s == "OP_LT")
		return NodeType::LeafLt;
	if(s == "OP_LTE")
		return NodeType::LeafLte;
	if(s == "OP_GT")
		return NodeType::LeafGt;
	if(s == "OP_GTE")
		return NodeType::LeafGte;
	if(s == "OP_EQ")
		return NodeType::LeafEq;
	if(s == "OP_NEQ")
		return NodeType::LeafNeq;
	if(s == "OP_NEG")
		return NodeType::LeafNeg;
	if(s == "OP_TILDA")
		return NodeType::LeafTilde;
	if(s == "OP_I")
		return NodeType::LeafLogAnd;
	if(s == "OP_ILI")
		return NodeType::LeafLogOr;
	if(s == "OP_BIN_I")
		return NodeType::LeafBitAnd;
	if(s == "OP_BIN_ILI")
		return NodeType::LeafBitOr;
	if(s == "OP_BIN_XILI")
		return NodeType::LeafBitXor;
	if(s == "ZAREZ")
		return NodeType::LeafComma;
	if(s == "TOCKAZAREZ")
		return NodeType::LeafSemicolon;
	if(s == "L_ZAGRADA")
		return NodeType::LeafLeftBracket;
	if(s == "D_ZAGRADA")
		return NodeType::LeafRightBracket;
	if(s == "L_UGL_ZAGRADA")
		return NodeType::LeafLeftSquareBracket;
	if(s == "D_UGL_ZAGRADA")
		return NodeType::LeafRightSquareBracket;
	if(s == "L_VIT_ZAGRADA")
		return NodeType::LeafLeftCurlyBracket;
	if(s == "D_VIT_ZAGRADA")
		return NodeType::LeafRightCurlyBracket;
	return NodeType::Error;
}

bool Msaga::isLeaf(NodeType nt) {
	if(nt == NodeType::LeafIdn)
		return true;
	if(nt == NodeType::LeafNum)
		return true;
	if(nt == NodeType::LeafCharacter)
		return true;
	if(nt == NodeType::LeafCharArray)
		return true;
	if(nt == NodeType::LeafComma)
		return true;
	if(nt == NodeType::LeafAssignment)
		return true;
	if(nt == NodeType::LeafLogOr)
		return true;
	if(nt == NodeType::LeafLogAnd)
		return true;
	if(nt == NodeType::LeafBitOr)
		return true;
	if(nt == NodeType::LeafBitXor)
		return true;
	if(nt == NodeType::LeafBitAnd)
		return true;
	if(nt == NodeType::LeafEq)
		return true;
	if(nt == NodeType::LeafNeq)
		return true;
	if(nt == NodeType::LeafLt)
		return true;
	if(nt == NodeType::LeafGt)
		return true;
	if(nt == NodeType::LeafLte)
		return true;
	if(nt == NodeType::LeafGte)
		return true;
	if(nt == NodeType::LeafRightBracket)
		return true;
	if(nt == NodeType::LeafLeftBracket)
		return true;
	if(nt == NodeType::LeafRightSquareBracket)
		return true;
	if(nt == NodeType::LeafLeftSquareBracket)
		return true;
	if(nt == NodeType::LeafLeftCurlyBracket)
		return true;
	if(nt == NodeType::LeafRightCurlyBracket)
		return true;
	if(nt == NodeType::LeafPlus)
		return true;
	if(nt == NodeType::LeafMinus)
		return true;
	if(nt == NodeType::LeafMult)
		return true;
	if(nt == NodeType::LeafDiv)
		return true;
	if(nt == NodeType::LeafMod)
		return true;
	if(nt == NodeType::LeafInc)
		return true;
	if(nt == NodeType::LeafDec)
		return true;
	if(nt == NodeType::LeafSemicolon)
		return true;
	if(nt == NodeType::LeafTilde)
		return true;
	if(nt == NodeType::LeafNeg)
		return true;
	if(nt == NodeType::LeafKwIf)
		return true;
	if(nt == NodeType::LeafKwElse)
		return true;
	if(nt == NodeType::LeafKwWhile)
		return true;
	if(nt == NodeType::LeafKwFor)
		return true;
	if(nt == NodeType::LeafKwConst)
		return true;
	if(nt == NodeType::LeafKwInt)
		return true;
	if(nt == NodeType::LeafKwChar)
		return true;
	if(nt == NodeType::LeafKwVoid)
		return true;
	if(nt == NodeType::LeafKwContinue)
		return true;
	if(nt == NodeType::LeafKwBreak)
		return true;
	if(nt == NodeType::LeafKwReturn)
		return true;
	return false;
}