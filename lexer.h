#ifndef HAVE_LEXER_H
#define HAVE_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef unsigned int token_type_t;

#define TOKEN_IDENTIFIER 1
#define TOKEN_INTEGER 2
#define TOKEN_RELOP 3
#define TOKEN_OPERATOR 4
#define TOKEN_SEPARATOR 5
#define TOKEN_KEYWORD 6
#define TOKEN_ADDITION 7
#define TOKEN_MULTIPLICATION 8
#define TOKEN_EQUALS 9
#define TOKEN_FOR 10
#define TOKEN_WHILE 11
#define TOKEN_FUNCTION 12
#define TOKEN_TYPE 13
#define TOKEN_REPEAT 14
#define TOKEN_IF 15
#define TOKEN_FI 16
#define TOKEN_ELSE 17
#define TOKEN_TRUTH_VALUE 18
#define TOKEN_SCANF 19
#define TOKEN_UNTIL 20
#define TOKEN_RETURN 21
#define TOKEN_OPEN_PAREN 22
#define TOKEN_CLOSE_PAREN 23
#define TOKEN_OPEN_BRACE 24
#define TOKEN_CLOSE_BRACE 25
#define TOKEN_SEMICOLON 26
#define TOKEN_COMMA 27
#define TOKEN_PRINTF 28
#define TOKEN_SUBTRACTION 29
#define TOKEN_DIVISION 30
#define TOKEN_OPEN_BRACKET 31
#define TOKEN_CLOSE_BRACKET 32
#define TOKEN_EOF 33


char *lexer_get_type(token_type_t type);


typedef struct _lexer_t lexer_t;
struct _lexer_t
{
	char * buffer;
	long buffersize;
	int position;
};

int lexer_init(lexer_t *lexer, char *filename);
void lexer_destroy(lexer_t *lexer);
int lexer_get_token(lexer_t *lexer, token_type_t *token_type, char **lexeme);

#endif
