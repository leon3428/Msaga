#include "Serialization.hpp"
#include "Leafs.hpp"
#include "Expressions.hpp"
#include "OtherNodes.hpp"
#include "Commands.hpp"
#include "Declarations.hpp"

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

SyntaxTreeNode* Msaga::constructInnerNode(const std::string &s, SyntaxTreeNode *parent){
	if(s == "<prijevodna_jedinica>")
		return parent -> addChild<TranslationUnit>();
	if(s == "<primarni_izraz>")
		return parent -> addChild<PrimaryExpression>();
	if(s == "<postfiks_izraz>")
		return parent -> addChild<PostfixExpression>();
	if(s == "<lista_argumenata>")
		return parent -> addChild<ArgumentList>();
	if(s == "<unarni_izraz>")
		return parent -> addChild<UnaryExpression>();
	if(s == "<unarni_operator>")
		return parent -> addChild<UnaryOperator>();
	if(s == "<cast_izraz>")
		return parent -> addChild<CastExpression>();
	if(s == "<ime_tipa>")
		return parent -> addChild<TypeName>();
	if(s == "<specifikator_tipa>")
		return parent -> addChild<TypeSpecifier>();
	if(s == "<multiplikativni_izraz>")
		return parent -> addChild<MultiplicativeExpression>();
	if(s == "<aditivni_izraz>")
		return parent -> addChild<AdditiveExpression>();
	if(s == "<odnosni_izraz>")
		return parent -> addChild<ComparisonExpression>();
	if(s == "<jednakosni_izraz>")
		return parent -> addChild<EqualsExpression>();
	if(s == "<bin_i_izraz>")
		return parent -> addChild<BitwiseAndExpression>();
	if(s == "<bin_xili_izraz>")
		return parent -> addChild<BitwiseXorExpression>();
	if(s == "<bin_ili_izraz>")
		return parent -> addChild<BitwiseOrExpression>();
	if(s == "<log_i_izraz>")
		return parent -> addChild<LogicalAndExpression>();
	if(s == "<log_ili_izraz>")
		return parent -> addChild<LogicalOrExpression>();
	if(s == "<izraz_pridruzivanja>")
		return parent -> addChild<AssignmentExpression>();
	if(s == "<izraz>")
		return parent -> addChild<Expression>();
	if(s == "<slozena_naredba>")
		return parent -> addChild<ComplexCommand>();
	if(s == "<lista_naredbi>")
		return parent -> addChild<ListCommand>();
	if(s == "<naredba>")
		return parent -> addChild<Command>();
	if(s == "<izraz_naredba>")
		return parent -> addChild<ExpressionCommand>();
	if(s == "<naredba_grananja>")
		return parent -> addChild<BranchCommand>();
	if(s == "<naredba_petlje>")
		return parent -> addChild<LoopCommand>();
	if(s == "<naredba_skoka>")
		return parent -> addChild<JumpCommand>();
	if(s == "<vanjska_deklaracija>")
		return parent -> addChild<ExternalDeclaration>();
	if(s == "<definicija_funkcije>")
		return parent -> addChild<FunctionDefinition>();
	if(s == "<lista_parametara>")
		return parent -> addChild<ParameterList>();
	if(s == "<deklaracija_parametra>")
		return parent -> addChild<ParameterDeclaration>();
	if(s == "<lista_deklaracija>")
		return parent -> addChild<DeclarationList>();
	if(s == "<deklaracija>")
		return parent -> addChild<Declaration>();
	if(s == "<lista_init_deklaratora>")
		return parent -> addChild<DeclaratorInitList>();
	if(s == "<init_deklarator>")
		return parent -> addChild<InitDeclarator>();
	if(s == "<izravni_deklarator>")
		return parent -> addChild<DirectDeclarator>();
	if(s == "<inicijalizator>")
		return parent -> addChild<Initializer>();
	if(s == "<lista_izraza_pridruzivanja>")
		return parent -> addChild<JoinExpressionList>();
	return nullptr;
}

SyntaxTreeNode* Msaga::constructLeafNode(const std::string &s, int row, const std::string &lexicalUnit, SyntaxTreeNode *parent){
	if(s == "IDN")
		return parent -> addChild<LeafIdn>(row, lexicalUnit);
	if(s == "BROJ")
		return parent -> addChild<LeafNum>(row, lexicalUnit);
	if(s == "ZNAK")
		return parent -> addChild<LeafCharacter>(row, lexicalUnit);
	if(s == "NIZ_ZNAKOVA")
		return parent -> addChild<LeafCharArray>(row, lexicalUnit);
	if(s == "KR_BREAK")
		return parent -> addChild<LeafKwBreak>(row, lexicalUnit);
	if(s == "KR_CHAR")
		return parent -> addChild<LeafKwChar>(row, lexicalUnit);
	if(s == "KR_CONST")
		return parent -> addChild<LeafKwConst>(row, lexicalUnit);
	if(s == "KR_CONTINUE")
		return parent -> addChild<LeafKwContinue>(row, lexicalUnit);
	if(s == "KR_ELSE")
		return parent -> addChild<LeafKwElse>(row, lexicalUnit);
	if(s == "KR_FOR")
		return parent -> addChild<LeafKwFor>(row, lexicalUnit);
	if(s == "KR_IF")
		return parent -> addChild<LeafKwIf>(row, lexicalUnit);
	if(s == "KR_INT")
		return parent -> addChild<LeafKwInt>(row, lexicalUnit);
	if(s == "KR_RETURN")
		return parent -> addChild<LeafKwReturn>(row, lexicalUnit);
	if(s == "KR_VOID")
		return parent -> addChild<LeafKwVoid>(row, lexicalUnit);
	if(s == "KR_WHILE")
		return parent -> addChild<LeafKwWhile>(row, lexicalUnit);
	if(s == "PLUS")
		return parent -> addChild<LeafPlus>(row, lexicalUnit);
	if(s == "OP_INC")
		return parent -> addChild<LeafInc>(row, lexicalUnit);
	if(s == "MINUS")
		return parent -> addChild<LeafMinus>(row, lexicalUnit);
	if(s == "OP_DEC")
		return parent -> addChild<LeafDec>(row, lexicalUnit);
	if(s == "OP_PUTA")
		return parent -> addChild<LeafMult>(row, lexicalUnit);
	if(s == "OP_DIJELI")
		return parent -> addChild<LeafDiv>(row, lexicalUnit);
	if(s == "OP_MOD")
		return parent -> addChild<LeafMod>(row, lexicalUnit);
	if(s == "OP_PRIDRUZI")
		return parent -> addChild<LeafAssignment>(row, lexicalUnit);
	if(s == "OP_LT")
		return parent -> addChild<LeafLt>(row, lexicalUnit);
	if(s == "OP_LTE")
		return parent -> addChild<LeafLte>(row, lexicalUnit);
	if(s == "OP_GT")
		return parent -> addChild<LeafGt>(row, lexicalUnit);
	if(s == "OP_GTE")
		return parent -> addChild<LeafGte>(row, lexicalUnit);
	if(s == "OP_EQ")
		return parent -> addChild<LeafEq>(row, lexicalUnit);
	if(s == "OP_NEQ")
		return parent -> addChild<LeafNeq>(row, lexicalUnit);
	if(s == "OP_NEG")
		return parent -> addChild<LeafNeg>(row, lexicalUnit);
	if(s == "OP_TILDA")
		return parent -> addChild<LeafTilde>(row, lexicalUnit);
	if(s == "OP_I")
		return parent -> addChild<LeafLogAnd>(row, lexicalUnit);
	if(s == "OP_ILI")
		return parent -> addChild<LeafLogOr>(row, lexicalUnit);
	if(s == "OP_BIN_I")
		return parent -> addChild<LeafBitAnd>(row, lexicalUnit);
	if(s == "OP_BIN_ILI")
		return parent -> addChild<LeafBitOr>(row, lexicalUnit);
	if(s == "OP_BIN_XILI")
		return parent -> addChild<LeafBitXor>(row, lexicalUnit);
	if(s == "ZAREZ")
		return parent -> addChild<LeafComma>(row, lexicalUnit);
	if(s == "TOCKAZAREZ")
		return parent -> addChild<LeafSemicolon>(row, lexicalUnit);
	if(s == "L_ZAGRADA")
		return parent -> addChild<LeafLeftBracket>(row, lexicalUnit);
	if(s == "D_ZAGRADA")
		return parent -> addChild<LeafRightBracket>(row, lexicalUnit);
	if(s == "L_UGL_ZAGRADA")
		return parent -> addChild<LeafLeftSquareBracket>(row, lexicalUnit);
	if(s == "D_UGL_ZAGRADA")
		return parent -> addChild<LeafRightSquareBracket>(row, lexicalUnit);
	if(s == "L_VIT_ZAGRADA")
		return parent -> addChild<LeafLeftCurlyBracket>(row, lexicalUnit);
	if(s == "D_VIT_ZAGRADA")
		return parent -> addChild<LeafRightCurlyBracket>(row, lexicalUnit);
	return nullptr;
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