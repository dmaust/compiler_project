#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

/* Code follows Doxygen documentation conventions */


static struct 
{
	char *desc;
} 
token_type_info [31] =
{
	{""},
	{"identifier"},
	{"integer"},
	{"rel operator"},
	{"operator"},
	{"separator"},
	{"keyword"},
	{"add_op"},
	{"mul_op"},
	{"eq_op"},
	{"for_keyword"},
	{"while"},
	{"function"},
	{"var_type"},
	{"repeat"},
	{"if"},
	{"fi"},
	{"else"},
	{"truth_value"},
	{"scanf"},
	{"until"},
	{"return"},
	{"open_paren"},
	{"close_paren"},
	{"open_bracket"},
	{"close_bracket"},
	{"semicolon"},
	{"comma"},
	{"printf"},
	{"minus"},
	{"slash"},
	{"EOF"}
};

/**
 * \brief gets a description given the token type
 * 
 * \param type integer to tell the type
 */

char *lexer_get_type(token_type_t type)
{
	if(type < 31)
		return token_type_info[type].desc;
	else
		return "other";
}

/* types of characters */

#define CHAR_L 1 /* letter */
#define CHAR_D 2 /* digit */
#define CHAR_EXCL 3 /* exclamation point */
#define CHAR_EQ 4 /* = */
#define CHAR_LT 5 /* < */
#define CHAR_GT 6 /* > */
#define CHAR_OP 7 /* ( */
#define CHAR_CP 8 /* ) */
#define CHAR_OB 9 /* { */
#define CHAR_CB 10 /* } */
#define CHAR_SC 11 /* ; */
#define CHAR_COMMA 12 /* , */
#define CHAR_PLUS 13 /* + */
#define CHAR_MINUS 14 /* - */
#define CHAR_AST 15 /* * (asterisk) */
#define CHAR_DIV 16 /* / (slash/ division) */


/* "Accepting","l","d","!","=","<",">","(",")","{","}",";",",","+","-","*","/" */

static unsigned int chartype[256] = { 
/*   0 -   9 */ 0,0,0,0,0,0,0,0,0,0, 
/*  10 -  19 */ 0,0,0,0,0,0,0,0,0,0, 
/*  20 -  29 */ 0,0,0,0,0,0,0,0,0,0, 
/*  30 -  39 */ 0,0,0,CHAR_EXCL,0,0,0,0,0,0, 
/*  40 -  49 */ CHAR_OP,CHAR_CP,CHAR_AST,CHAR_PLUS,CHAR_COMMA,
			CHAR_MINUS,0,CHAR_DIV,CHAR_D,CHAR_D, 
/*  50 -  59 */ CHAR_D,CHAR_D,CHAR_D,CHAR_D,CHAR_D,CHAR_D,CHAR_D,CHAR_D,0,CHAR_SC, 
/*  60 -  69 */ CHAR_LT,CHAR_EQ,CHAR_GT,0,0,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L, 
/*  70 -  79 */ CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L, 
/*  80 -  89 */ CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,
/*  90 -  99 */ CHAR_L,0,0,0,0,CHAR_L,0,CHAR_L,CHAR_L,CHAR_L, 
/* 100 - 109 */ CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,
/* 110 - 119 */ CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,CHAR_L,
/* 120 - 129 */ CHAR_L,CHAR_L,CHAR_L,CHAR_OB,0,CHAR_CB,0,0,0,0, 
/* 130 - 139 */ 0,0,0,0,0,0,0,0,0,0, 
/* 140 - 149 */ 0,0,0,0,0,0,0,0,0,0, 
/* 150 - 159 */ 0,0,0,0,0,0,0,0,0,0, 
/* 160 - 169 */ 0,0,0,0,0,0,0,0,0,0, 
/* 170 - 179 */ 0,0,0,0,0,0,0,0,0,0, 
/* 180 - 189 */ 0,0,0,0,0,0,0,0,0,0, 
/* 190 - 199 */ 0,0,0,0,0,0,0,0,0,0, 
/* 200 - 209 */ 0,0,0,0,0,0,0,0,0,0, 
/* 210 - 219 */ 0,0,0,0,0,0,0,0,0,0, 
/* 220 - 229 */ 0,0,0,0,0,0,0,0,0,0, 
/* 230 - 239 */ 0,0,0,0,0,0,0,0,0,0, 
/* 240 - 249 */ 0,0,0,0,0,0,0,0,0,0, 
/* 250 - 255 */ 0,0,0,0,0,0 
};


/* next state indexed by previous state and character read in */

static unsigned int fsm[19][17]={
{0,			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0,			2, 3, 4, 8, 9, 9, 7,10,11,12,13,14,15,17,16,18}, /* initial state */
{TOKEN_IDENTIFIER,	2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_INTEGER,		0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0,			0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_RELOP,		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_OPERATOR,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_OPEN_PAREN,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_EQUALS,		0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_RELOP,		0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_CLOSE_PAREN,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_OPEN_BRACE,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_CLOSE_BRACE,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_SEMICOLON,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_COMMA,		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_ADDITION,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_MULTIPLICATION,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_SUBTRACTION,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{TOKEN_DIVISION,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

};


static void skip_whitespace(lexer_t * lexer);

/** 
 * \brief initialize parser object
 *
 * \param lexer object to initalize
 * \param filename to open and load
 * 
 * Initializes a new lexer object.  Opens file and reads data into buffer.  
 * Returns -1 on error, 0 on success.
 */

int lexer_init(lexer_t *lexer, char *filename)
{
	FILE *fh = NULL;
	lexer->buffer = NULL;
	lexer->position = 0;
	fh = fopen(filename, "r");
	if(!fh)
		goto err;
	if(fseek(fh, 0, SEEK_END) < 0)
		goto err;
	lexer->buffersize = ftell(fh);
	if(lexer->buffersize < 0)
		goto err;
	if(fseek(fh, 0, SEEK_SET) < 0)
		goto err;
	lexer->buffer = (char *)malloc(lexer->buffersize);
	if(lexer->buffer == NULL)
		goto err;

	lexer->buffersize = fread(lexer->buffer, 1, lexer->buffersize, fh);
	
	fclose(fh);
	skip_whitespace(lexer);
	return 0;

	
	/* clean up code */
err:
	if(fh)
		fclose(fh);
	if(lexer->buffer)
		free(lexer->buffer);
	return -1;
	
}

/**
 * \brief destroys a lexer object
 *
 * \param lexer object to destroy
 */ 

void lexer_destroy(lexer_t *lexer)
{
	free(lexer->buffer);
}


typedef struct {
	char *name;
	int type;
} keyword_entry_t;

static keyword_entry_t keywords[] = {
	{"for", TOKEN_FOR},
	{"while", TOKEN_WHILE},
	{"function", TOKEN_FUNCTION},
	{"int", TOKEN_TYPE},
	{"boolean", TOKEN_TYPE},
	{"repeat", TOKEN_REPEAT},
	{"if", TOKEN_IF},
	{"fi", TOKEN_FI},
	{"else", TOKEN_ELSE},
	{"true", TOKEN_TRUTH_VALUE},
	{"false", TOKEN_TRUTH_VALUE},
	{"printf", TOKEN_PRINTF},
	{"scanf", TOKEN_SCANF},
	{"until", TOKEN_UNTIL},
	{"return", TOKEN_RETURN }
};

static int is_keyword(char *lexeme)
{
	int i;
	for(i = 0; i < sizeof(keywords)/sizeof(keyword_entry_t); i++)
	{
		if(!strcmp(lexeme, keywords[i].name))
		{
			return keywords[i].type;
		}
	}
	return 0;
}

static void skip_whitespace(lexer_t * lexer)
{
	while(
			lexer->position < lexer->buffersize && 
			(lexer->buffer[lexer->position] == ' ' 
			 || lexer->buffer[lexer->position] == '\n'
			 || lexer->buffer[lexer->position] == '\t')
			)
	{
		lexer->position++;
	}
}
/** 
 * \brief gets next token
 * 
 * \param lexer to extract token from
 * \param token_type location to place extracted token
 * \param lexeme location to place lexeme
 */

int lexer_get_token(lexer_t *lexer, token_type_t *token_type, char **lexeme)
{
	int lexeme_buffer_size = 16;
	int lexeme_size = 0;
	char next_char;
	unsigned int state;
	unsigned int next_state;
	unsigned int char_type;
	if(lexer_eof(lexer)){
		*token_type=TOKEN_EOF;
	}
	*lexeme = (char *)malloc(lexeme_buffer_size);
	if(!*lexeme)
		goto err1;
	state = 1; /* set initial state */
	while(lexer->position < lexer->buffersize){
		next_char = lexer->buffer[lexer->position];
		char_type = chartype[(int)next_char];
		if(!char_type)  break;
		next_state = fsm[state][char_type];
		if(next_state == 0)
			break;

		(*lexeme)[lexeme_size] = next_char;
		state = next_state;

		lexeme_size++;
		if(lexeme_size == lexeme_buffer_size){
			char *old_buffer;
			old_buffer = *lexeme;
			lexeme_buffer_size += 16;
			*lexeme = (char *)realloc(*lexeme, lexeme_buffer_size);
			if(*lexeme == NULL) {
				free(old_buffer);
				goto err1;
			}
		}
		lexer->position++;
	
	}
	skip_whitespace(lexer);
	if(fsm[state][0]){
		(*lexeme)[lexeme_size] = '\0';
		*token_type = fsm[state][0];
		if(*token_type == TOKEN_IDENTIFIER){
			int retval = 0;
			retval = is_keyword(*lexeme);
			if(retval) *token_type = retval;
		}
		return 0;
	}
err1:
	if(*lexeme)
		free(*lexeme);
	return -1;
		
}

/**
 * \brief determines if end of file has been reached
 *
 * \param lexer to determine end of file status
 *
 * returns 1 (true) to indicate end of file, 0 (false) to indicate 
 * end of file was not reached
 */
int lexer_eof(lexer_t* lexer)
{
	return (lexer->position >= lexer->buffersize);
}


