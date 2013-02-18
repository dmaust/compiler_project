#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "parse_table.h"
#include "grammer.h"
#include "code_gen.h"





int parse(lexer_t *lexer){
	stack_frame parse_stack[1000];
	int stack_pointer = 0;


	int state = 1;
	token_type_t token_type;
	char *lexeme;
	int next_token;
	lexer_get_token(lexer, &token_type, &lexeme);
	next_token = token_type+25;
	int have_buffer = 0;
	parse_tree_node * tree_node_buffer;
	while(state != 2){
		int operation = parse_table[state][next_token].operation;
		int argument = parse_table[state][next_token].arg;
		if(operation == 1){
			
			/* shift to stack */
			parse_stack[stack_pointer].state = state;
			parse_stack[stack_pointer].element = next_token;
			parse_stack[stack_pointer].lexeme = lexeme;
			if(have_buffer){
				parse_stack[stack_pointer].tree_element = tree_node_buffer;
			} else {
				parse_stack[stack_pointer].tree_element = (parse_tree_node *)malloc(sizeof(parse_tree_node));
				parse_stack[stack_pointer].tree_element->element = next_token;
				parse_stack[stack_pointer].tree_element->lexeme = strdup(lexeme);
				parse_stack[stack_pointer].tree_element->first_child = NULL;
			}
			state = argument;
			stack_pointer++;
			
			if(!have_buffer){
				/* fetch token */
				lexer_get_token(lexer, &token_type, &lexeme);
			}
			next_token = token_type+25;
			have_buffer = 0;
		} else if (operation == 2){
			/* reduce */
			int i;
			child_linked_list_node * next = NULL;
			for(i = 0; production_rules[argument].rhs[i] != 0; i++){
				child_linked_list_node * temp;
				stack_pointer--;
				state = parse_stack[stack_pointer].state;
				temp = (child_linked_list_node *)malloc(sizeof(child_linked_list_node));
				temp->child = parse_stack[stack_pointer].tree_element;
				temp->next_child = next;
				next = temp;
			}
			next_token = production_rules[argument].lhs;
			tree_node_buffer = (parse_tree_node *)malloc(sizeof(parse_tree_node));
			tree_node_buffer->first_child = next;
			tree_node_buffer->element = production_rules[argument].lhs;
			tree_node_buffer->lexeme = NULL;
			have_buffer = 1;
		} else {
			/* syntax error */
			return 0;
		}
	}
	process_cs905s04(tree_node_buffer);	
	return 1;
}

