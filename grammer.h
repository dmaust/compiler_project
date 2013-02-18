#ifndef HAVE_GRAMMER_H
#define HAVE_GRAMMER_H

#include "lexer.h"

#define NONTERMINAL_START 			1
#define NONTERMINAL_CS905 			2
#define NONTERMINAL_FUNCTION_DEFINITION		3
#define NONTERMINAL_OPT_PARAMETER_LIST		4
#define NONTERMINAL_BODY			5
#define NONTERMINAL_IDS				6
#define NONTERMINAL_OPT_DECLARATION_LIST	7
#define NONTERMINAL_DECLARATION_LIST		8
#define NONTERMINAL_DECLARATION			9

#define NONTERMINAL_STATEMENT_LIST		10
#define NONTERMINAL_STATEMENT			11
#define NONTERMINAL_COMPOUND			12
#define NONTERMINAL_ASSIGN			13
#define NONTERMINAL_IF				14
#define NONTERMINAL_WHILE			15
#define NONTERMINAL_REPEAT			16
#define NONTERMINAL_RETURN			17
#define NONTERMINAL_PRINT			18
#define NONTERMINAL_SCAN			19

#define NONTERMINAL_CONDITION			20
#define NONTERMINAL_EXPRESSION			21
#define NONTERMINAL_TERM			22
#define NONTERMINAL_FACTOR			23
#define NONTERMINAL_PRIMARY			24
#define NONTERMINAL_EXPRESSION_LIST		25

#define TERMINAL_IDENTIFIER			26
#define TERMINAL_INTEGER 			27
#define TERMINAL_RELOP 				28
#define TERMINAL_OPERATOR 			29
#define TERMINAL_SEPARATOR 			30
#define TERMINAL_KEYWORD 			31
#define TERMINAL_ADDITION 			32
#define TERMINAL_MULTIPLICATION 		33
#define TERMINAL_EQUALS 			34
#define TERMINAL_FOR 				35
#define TERMINAL_WHILE 				36
#define TERMINAL_FUNCTION 			37
#define TERMINAL_TYPE 				38
#define TERMINAL_REPEAT 			39
#define TERMINAL_IF 				40
#define TERMINAL_FI 				41
#define TERMINAL_ELSE 				42
#define TERMINAL_TRUTH_VALUE 			43
#define TERMINAL_SCANF 				44
#define TERMINAL_UNTIL 				45
#define TERMINAL_RETURN 			46
#define TERMINAL_OPEN_PAREN 			47
#define TERMINAL_CLOSE_PAREN 			48
#define TERMINAL_OPEN_BRACE 			49
#define TERMINAL_CLOSE_BRACE 			50
#define TERMINAL_SEMICOLON 			51
#define TERMINAL_COMMA 				52
#define TERMINAL_PRINTF				53
#define TERMINAL_MINUS				54
#define TERMINAL_SLASH				55
#define TERMINAL_OPEN_BRACKET			56
#define TERMINAL_CLOSE_BRACKET			57
#define TERMINAL_EOF				58


#define SYNTAX_TERMINAL_TEST(n) (syntax_element_info[(n)].terminal)
#define SYNTAX_ELEMENT_NAME(n) (syntax_element_info[(n)].name)

static int follow_set_Start[] = { TERMINAL_EOF ,0};
static int follow_set_CS905s04[] = { TERMINAL_EOF ,0};
static int follow_set_Function_Definition[] = { TERMINAL_FUNCTION, TERMINAL_EOF ,0} ;
static int follow_set_Opt_Parameter_List[] = { TERMINAL_CLOSE_PAREN ,0};
static int follow_set_Body[] = { TERMINAL_FUNCTION, TERMINAL_EOF ,0} ;
static int follow_set_Opt_Declaration_List[] = { TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN ,0};
static int follow_set_Declaration_List[] = {  TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN ,0};
static int follow_set_Declaration[] = { TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_TYPE, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN ,0};
static int follow_set_IDs[] = {  TERMINAL_SEMICOLON, TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_TYPE, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_PAREN ,0};
static int follow_set_Statement_List[] = { TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Statement[] = { TERMINAL_PRINTF, TERMINAL_SCANF,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Compound[] = { TERMINAL_PRINTF, TERMINAL_SCANF,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Assign[] = {  TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_If[] = {   TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_While[] = {  TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Repeat[] = {  TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Return[] = {  TERMINAL_PRINTF, TERMINAL_SCANF,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Print[] = {  TERMINAL_PRINTF, TERMINAL_SCANF,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Scan[] = {  TERMINAL_PRINTF, TERMINAL_SCANF,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE ,0};
static int follow_set_Condition[]  = { TERMINAL_PRINTF, TERMINAL_SCANF,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE, TERMINAL_CLOSE_PAREN ,TERMINAL_SEMICOLON,0} ;
static int follow_set_Expression[] = { TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_RELOP, TERMINAL_ADDITION, TERMINAL_MINUS,  TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE, TERMINAL_CLOSE_PAREN,TERMINAL_SEMICOLON,0} ;
static int follow_set_Term[] = { TERMINAL_MULTIPLICATION, TERMINAL_SLASH, TERMINAL_RELOP, TERMINAL_ADDITION, TERMINAL_MINUS , TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE, TERMINAL_CLOSE_PAREN, TERMINAL_SEMICOLON,0}  ;
static int follow_set_Factor[] = {  TERMINAL_MULTIPLICATION, TERMINAL_SLASH, TERMINAL_RELOP, TERMINAL_ADDITION, TERMINAL_MINUS , TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE, TERMINAL_CLOSE_PAREN ,TERMINAL_SEMICOLON,0}  ;
static int follow_set_Primary[] = {  TERMINAL_MULTIPLICATION, TERMINAL_SLASH, TERMINAL_RELOP, TERMINAL_ADDITION, TERMINAL_MINUS, TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE, TERMINAL_CLOSE_PAREN ,TERMINAL_SEMICOLON,0} ;
static int follow_set_Expression_List[] = { TERMINAL_RELOP, TERMINAL_ADDITION, TERMINAL_MINUS, TERMINAL_PRINTF, TERMINAL_SCANF, TERMINAL_IF, TERMINAL_IDENTIFIER, TERMINAL_WHILE, TERMINAL_OPEN_BRACE, TERMINAL_REPEAT, TERMINAL_RETURN, TERMINAL_CLOSE_BRACE, TERMINAL_CLOSE_PAREN,0};


static struct {
	char * name;
	int terminal;
	int *follow;
} syntax_element_info[] = {
	{"NONE", 1, 0},
	{"<Start>", 0, follow_set_Start},
	{"<CS905s04>", 0, follow_set_CS905s04},
	{"<Function Definition>", 0, follow_set_Function_Definition},
	{"<Opt Parameter List>", 0, follow_set_Opt_Parameter_List},
	{"<Body>", 0, follow_set_Body},
	{"<IDs>", 0, follow_set_IDs},
	{"<Opt Declaration List>", 0, follow_set_Opt_Declaration_List},
	{"<Declaration List>", 0,follow_set_Declaration_List },
	{"<Declaration>", 0,follow_set_Declaration },
	{"<Statement List>", 0, follow_set_Statement_List},
	{"<Statement>", 0, follow_set_Statement},
	{"<Compound>", 0, follow_set_Compound},
	{"<Assign>", 0, follow_set_Assign},
	{"<If>", 0, follow_set_If},
	{"<While>", 0, follow_set_While},
	{"<Repeat>", 0, follow_set_Repeat},
	{"<Return>", 0, follow_set_Return},
	{"<Print>", 0, follow_set_Print},
	{"<Scan>", 0, follow_set_Scan},
	{"<Condition>", 0, follow_set_Condition},
	{"<Expression>", 0, follow_set_Expression},
	{"<Term>", 0, follow_set_Term},
	{"<Factor>", 0, follow_set_Factor},
	{"<Primary>", 0, follow_set_Primary},
	{"<Expression List>", 0, follow_set_Expression_List},
	{"<Identifier>", 1, 0},
	{"<Integer>", 1,0},
	{"<Relop>", 1,0},
	{"ERROR OPERATOR", 1,0},
	{"ERROR SEPARATOR", 1,0},
	{"ERROR KEYWORD", 1,0},
	{"+", 1,0},
	{"*", 1,0},
	{"=", 1,0},
	{"for", 1,0},
	{"while", 1,0},
	{"function",1,0},
	{"<VarType>", 1,0},
	{"repeat", 1,0},
	{"if", 1,0},
	{"fi", 1,0},
	{"else", 1,0},
	{"truth_value", 1,0},
	{"scanf", 1,0},
	{"until", 1,0},
	{"return", 1,0},
	{"(", 1,0},
	{")", 1,0},
	{"{", 1,0},
	{"}", 1,0},
	{";", 1,0},
	{",", 1,0},
	{"printf", 1,0},
	{"-", 1,0},
	{"/", 1,0},
	{"[", 1,0},
	{"]", 1,0},
	{"EOF", 1, 0}
};

static int production_rule_0[] = {0};
static int production_rule_1[] = {NONTERMINAL_CS905, 0};
static int production_rule_2[] = {NONTERMINAL_FUNCTION_DEFINITION, NONTERMINAL_CS905, 0};
static int production_rule_3[] = {NONTERMINAL_FUNCTION_DEFINITION, 0};
static int production_rule_4[] = {TERMINAL_FUNCTION, TERMINAL_IDENTIFIER, TERMINAL_OPEN_PAREN, NONTERMINAL_OPT_PARAMETER_LIST, TERMINAL_CLOSE_PAREN, TERMINAL_SEMICOLON, NONTERMINAL_BODY, 0};
static int production_rule_5[] = {NONTERMINAL_IDS,0};
static int production_rule_6[] = {0};
static int production_rule_7[] = {TERMINAL_OPEN_BRACE, NONTERMINAL_OPT_DECLARATION_LIST, NONTERMINAL_STATEMENT_LIST, TERMINAL_CLOSE_BRACE, 0};
static int production_rule_8[] = {NONTERMINAL_DECLARATION_LIST,0};
static int production_rule_9[] = {0};
static int production_rule_10[] = {NONTERMINAL_DECLARATION, 0};
static int production_rule_11[] = {NONTERMINAL_DECLARATION, NONTERMINAL_DECLARATION_LIST, 0};
static int production_rule_12[] = {TERMINAL_TYPE, NONTERMINAL_IDS, TERMINAL_SEMICOLON, 0};
static int production_rule_13[] = {TERMINAL_IDENTIFIER, 0};
static int production_rule_14[] = {TERMINAL_IDENTIFIER, TERMINAL_COMMA, NONTERMINAL_IDS, 0};
static int production_rule_15[] = {NONTERMINAL_STATEMENT, 0};
static int production_rule_16[] = {NONTERMINAL_STATEMENT, NONTERMINAL_STATEMENT_LIST, 0};
static int production_rule_17[] = {NONTERMINAL_COMPOUND, 0};
static int production_rule_18[] = {NONTERMINAL_ASSIGN, 0};
static int production_rule_19[] = {NONTERMINAL_IF, 0};
static int production_rule_20[] = {NONTERMINAL_WHILE, 0};
static int production_rule_21[] = {NONTERMINAL_REPEAT, 0};
static int production_rule_22[] = {NONTERMINAL_RETURN, 0};
static int production_rule_23[] = {NONTERMINAL_PRINT, 0};
static int production_rule_24[] = {NONTERMINAL_SCAN, 0};
static int production_rule_25[] = {TERMINAL_OPEN_BRACE, NONTERMINAL_STATEMENT_LIST, TERMINAL_CLOSE_BRACE  ,0};
static int production_rule_26[] = {TERMINAL_IDENTIFIER, TERMINAL_EQUALS, NONTERMINAL_EXPRESSION, TERMINAL_SEMICOLON, 0};
static int production_rule_27[] = {TERMINAL_IF, TERMINAL_OPEN_PAREN, NONTERMINAL_CONDITION, TERMINAL_CLOSE_PAREN, NONTERMINAL_STATEMENT, TERMINAL_FI, 0};
static int production_rule_28[] = {TERMINAL_IF, TERMINAL_OPEN_PAREN, NONTERMINAL_CONDITION, TERMINAL_CLOSE_PAREN, NONTERMINAL_STATEMENT, TERMINAL_ELSE, NONTERMINAL_STATEMENT, TERMINAL_FI, 0};
static int production_rule_29[] = {TERMINAL_WHILE, TERMINAL_OPEN_PAREN, NONTERMINAL_CONDITION, TERMINAL_CLOSE_PAREN, NONTERMINAL_STATEMENT, 0};
static int production_rule_30[] = {TERMINAL_REPEAT, NONTERMINAL_STATEMENT, TERMINAL_UNTIL, NONTERMINAL_CONDITION, TERMINAL_SEMICOLON, 0};
static int production_rule_31[] = {TERMINAL_RETURN, TERMINAL_SEMICOLON, 0};
static int production_rule_32[] = {TERMINAL_RETURN, NONTERMINAL_EXPRESSION, TERMINAL_SEMICOLON, 0};
static int production_rule_33[] = {TERMINAL_PRINTF, TERMINAL_OPEN_PAREN, NONTERMINAL_EXPRESSION, TERMINAL_CLOSE_PAREN, TERMINAL_SEMICOLON, 0};
static int production_rule_34[] = {TERMINAL_SCANF, TERMINAL_OPEN_PAREN, NONTERMINAL_IDS, TERMINAL_CLOSE_PAREN, TERMINAL_SEMICOLON, 0};
static int production_rule_35[] = {NONTERMINAL_EXPRESSION, TERMINAL_RELOP, NONTERMINAL_EXPRESSION, 0};
static int production_rule_36[] = {NONTERMINAL_EXPRESSION, TERMINAL_ADDITION, NONTERMINAL_TERM, 0};
static int production_rule_37[] = {NONTERMINAL_EXPRESSION, TERMINAL_MINUS, NONTERMINAL_TERM,0};
static int production_rule_38[] = {NONTERMINAL_TERM, 0};
static int production_rule_39[] = {NONTERMINAL_TERM, TERMINAL_MULTIPLICATION, NONTERMINAL_FACTOR, 0};
static int production_rule_40[] = {NONTERMINAL_TERM, TERMINAL_SLASH, NONTERMINAL_FACTOR, 0};
static int production_rule_41[] = {NONTERMINAL_FACTOR, 0};
static int production_rule_42[] = {TERMINAL_MINUS, NONTERMINAL_PRIMARY, 0};
static int production_rule_43[] = {NONTERMINAL_PRIMARY, 0};
static int production_rule_44[] = {TERMINAL_IDENTIFIER, 0};
static int production_rule_45[] = {TERMINAL_INTEGER, 0};
static int production_rule_46[] = {TERMINAL_OPEN_PAREN, NONTERMINAL_EXPRESSION, TERMINAL_CLOSE_PAREN, 0};
static int production_rule_47[] = {TERMINAL_TRUTH_VALUE, 0};
static int production_rule_48[] = {TERMINAL_IDENTIFIER, TERMINAL_OPEN_BRACKET, NONTERMINAL_EXPRESSION_LIST, TERMINAL_CLOSE_BRACKET,0};
static int production_rule_49[] = {NONTERMINAL_EXPRESSION,0};
static int production_rule_50[] = {NONTERMINAL_EXPRESSION, TERMINAL_COMMA, NONTERMINAL_EXPRESSION_LIST, 0};
static int production_rule_51[] = {0};


#define N_PRODUCTION_RULES 52
static struct {
	int lhs;
	int *rhs;
	char *description;
} production_rules[N_PRODUCTION_RULES]  = {
	{0, production_rule_0, "ERROR"},
	{NONTERMINAL_START,production_rule_1, "<Start> ::= <CS905s04>"},
	{NONTERMINAL_CS905,production_rule_2,"<CS905s04> ::= <Function Definition> <CS905s04>"},
	{NONTERMINAL_CS905,production_rule_3, "<CS905s04> ::= <Function Definition>"},
	{NONTERMINAL_FUNCTION_DEFINITION,production_rule_4,"<Function Definition> ::= function <Identifier> ( <Opt Parameter List> ) ; <Body>"},
	{NONTERMINAL_OPT_PARAMETER_LIST,production_rule_5,"<Opt Parameter List> ::= <IDs>"},
	{NONTERMINAL_OPT_PARAMETER_LIST,production_rule_6,"<Opt Parameter List> ::= e"},
	{NONTERMINAL_BODY,production_rule_7,"<Body> ::= { <Opt Declaration List> < Statement List> }"},
	{NONTERMINAL_OPT_DECLARATION_LIST,production_rule_8,"<Opt Declaration List> ::= <Declaration List>"},
	{NONTERMINAL_OPT_DECLARATION_LIST,production_rule_9,"<Opt Declaration List> ::= e"},
	{NONTERMINAL_DECLARATION_LIST,production_rule_10,"<Declaration List> ::= <Declaration>"},
	{NONTERMINAL_DECLARATION_LIST,production_rule_11,"<Declaration List> ::= <Declaration> < Declaration List>"},
	{NONTERMINAL_DECLARATION,production_rule_12,"<Declaration> ::= <VarType> <IDs>;"},
	{NONTERMINAL_IDS,production_rule_13,"<IDs> ::= <Identifier>"},
	{NONTERMINAL_IDS,production_rule_14,"<IDs> ::= <Identifier>, <IDs>"},
	{NONTERMINAL_STATEMENT_LIST,production_rule_15,"<Statement List> ::= <Statement>"},
	{NONTERMINAL_STATEMENT_LIST,production_rule_16,"<Statement List> ::= <Statement> <Statement List>"},
	{NONTERMINAL_STATEMENT,production_rule_17,"<Statement> ::= <Compound>"},
	{NONTERMINAL_STATEMENT,production_rule_18,"<Statement> ::= <Assign>"},
	{NONTERMINAL_STATEMENT,production_rule_19,"<Statement> ::=<If>"},
	{NONTERMINAL_STATEMENT,production_rule_20,"<Statement> ::= <While>"},
	{NONTERMINAL_STATEMENT,production_rule_21,"<Statement> ::= <Repeat>"},
	{NONTERMINAL_STATEMENT,production_rule_22,"<Statement> ::= <Return>"},
	{NONTERMINAL_STATEMENT,production_rule_23,"<Statement> ::= <Print>"},
	{NONTERMINAL_STATEMENT,production_rule_24,"<Statement> ::= <Scan>"},
	{NONTERMINAL_COMPOUND,production_rule_25,"<Compound> ::= { <Statement List> }"},
	{NONTERMINAL_ASSIGN,production_rule_26,"<Assign> ::= <Identifier> = <Expression> ;"},
	{NONTERMINAL_IF,production_rule_27,"<If> ::= if ( <Condition> ) <Statement> fi"},
	{NONTERMINAL_IF,production_rule_28,"<if> ::= if ( <Condition> ) <Statement> else <Statement> fi"},
	{NONTERMINAL_WHILE,production_rule_29,"<While> ::= while ( <Condition> ) <Statement>"},
	{NONTERMINAL_REPEAT,production_rule_30,"<Repeat> ::= repeat <Statement> until <Condition> ;"},
	{NONTERMINAL_RETURN,production_rule_31,"<Return> ::= return ;"},
	{NONTERMINAL_RETURN,production_rule_32,"<Return> ::= return <Expression> ;"},
	{NONTERMINAL_PRINT,production_rule_33,"<Print> ::= printf ( <Expression> ) ;"},
	{NONTERMINAL_SCAN,production_rule_34,"<Scan> ::= scanf ( <IDs> );"},
	{NONTERMINAL_CONDITION,production_rule_35,"<Condition> ::= <Expression> <Relop> <Expression>"},
	{NONTERMINAL_EXPRESSION,production_rule_36,"<Expression> ::= <Expression> + <Term>"},
	{NONTERMINAL_EXPRESSION,production_rule_37,"<Expression> ::= <Expression> - <Term>"},
	{NONTERMINAL_EXPRESSION,production_rule_38,"<Expression> ::= <Term>"},
	{NONTERMINAL_TERM,production_rule_39,"<Term> ::= <Term> * <Factor>"},
	{NONTERMINAL_TERM,production_rule_40,"<Term> ::= <Term> / <Factor>"},
	{NONTERMINAL_TERM,production_rule_41,"<Term> ::= <Factor>"},
	{NONTERMINAL_FACTOR,production_rule_42,"<Factor> ::= - <Primary>"},
	{NONTERMINAL_FACTOR,production_rule_43,"<Factor> ::= <Primary>"},
	{NONTERMINAL_PRIMARY,production_rule_44,"<Primary> ::= <Identifier>"},
	{NONTERMINAL_PRIMARY,production_rule_45,"<Primary> ::= <Integer>"},
	{NONTERMINAL_PRIMARY,production_rule_46,"<Primary> ::= ( <Expression> )"},
	{NONTERMINAL_PRIMARY,production_rule_47,"<Primary> ::= truth_value"},
	{NONTERMINAL_PRIMARY,production_rule_48,"<Primary> ::= <Identifier> [<Expression List>]"},
	{NONTERMINAL_EXPRESSION_LIST,production_rule_49,"<Expression List> ::= <Expression>"},
	{NONTERMINAL_EXPRESSION_LIST,production_rule_50,"<Expression List> ::= <Expression> , <Expression List>"},
	{NONTERMINAL_EXPRESSION_LIST,production_rule_51,"<Expression List> ::= e"}
};

#endif
