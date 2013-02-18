#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv)
{
	lexer_t lexer;
	if(argc < 1)
	{
		fprintf(stderr, "Error: no argv[0]\n");
		return 1;
	} else if(argc < 2){
		fprintf(stderr, "%s: Usage: %s <sourcefile>\n", argv[0], argv[0]);
		return 1;
	}
	if(lexer_init(&lexer, argv[1])< 0)
	{
		fprintf(stderr, "%s: failed to open %s\n", argv[0], argv[1]);
		return 1;
	}
	{
		if(parse(&lexer)){
		} else {
			printf("parse failed\n");
		}
	}
				
	lexer_destroy(&lexer);	
	return 0;
}

