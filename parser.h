#ifndef HAVE_PARSER_H
#define HAVE_PARSER_H

#include "lexer.h"
typedef struct _parse_tree_node parse_tree_node;
typedef struct _child_linked_list_node child_linked_list_node;

int parse(lexer_t *lexer);
	
typedef struct {
	int state;
	int element;
	char *lexeme;
	parse_tree_node * tree_element;
} stack_frame;

struct _parse_tree_node{
	int element;
	char * lexeme;
	child_linked_list_node *first_child;
};
struct _child_linked_list_node {
	parse_tree_node *child;
	child_linked_list_node *next_child;
};


#endif
