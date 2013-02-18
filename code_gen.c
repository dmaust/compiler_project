#include <stdio.h>
#include <stdlib.h>

#include "symbol_table.h"
#include "code_gen.h"
#include "parser.h"
#include "grammer.h"


void process_opt_declaration_list(parse_tree_node *opt_decl_list);
void process_body(parse_tree_node *body);
void process_declaration_list(parse_tree_node *decl_list);
void process_declaration(parse_tree_node *declaration);
void process_function(parse_tree_node *function);
void process_statement_list(parse_tree_node * statement_list);
void process_statement(parse_tree_node * statement);
void process_scan(parse_tree_node *scan);
void process_compound(parse_tree_node * compound);
void process_print(parse_tree_node *print);
void process_assign(parse_tree_node *assign);
void process_while(parse_tree_node *while_node);
void process_if(parse_tree_node *if_node);
void process_repeat(parse_tree_node *repeat_node);
void process_return(parse_tree_node *repeat_node);
void process_expression(parse_tree_node *expression);
void process_term(parse_tree_node *term);
void process_factor(parse_tree_node *factor);
void process_primary(parse_tree_node *primary);

void process_conditional(parse_tree_node *conditional, int false_label);

int label_num = 0; 

parse_tree_node * get_child(child_linked_list_node *list, int n){
	int i;
	child_linked_list_node *temp = list;
	for(i = 0; i < n; i++){
		temp=temp->next_child;
	}
	return temp->child;
}

void process_cs905s04(parse_tree_node *root){
	process_function(get_child(root->first_child, 0));	
}
void process_function(parse_tree_node *function){
	process_body(get_child(function->first_child, 6));

}

void process_body(parse_tree_node *body){
	process_opt_declaration_list(get_child(body->first_child, 1));
	process_statement_list(get_child(body->first_child, 2));
}

void process_opt_declaration_list(parse_tree_node *opt_decl_list){
	if(opt_decl_list->first_child != NULL)
	process_declaration_list(opt_decl_list->first_child->child);
}

void process_declaration_list(parse_tree_node *decl_list){
	process_declaration(decl_list->first_child->child);
	if(decl_list->first_child->next_child != NULL)
		process_declaration(decl_list->first_child->next_child->child);
}

void process_declaration(parse_tree_node *declaration){
	char *ctype = declaration->first_child->child->lexeme;
	int type;
	if(!strcmp(ctype, "boolean")) type = 1;
	else if(!strcmp(ctype, "int")) type = 2;
	parse_tree_node *IDs = declaration->first_child->next_child->child;
	while(1){
		
		create_symbol(type, IDs->first_child->child->lexeme);
		if(IDs->first_child->next_child == NULL)
			break;
		else 
		 	IDs = IDs->first_child->next_child->next_child->child;
		
	}
}

void process_statement_list(parse_tree_node * statement_list){
	process_statement(statement_list->first_child->child);
	if(statement_list->first_child->next_child){
		process_statement_list(statement_list->first_child->next_child->child);
	}
}

void process_statement(parse_tree_node * statement){
	switch(statement->first_child->child->element){
		case NONTERMINAL_ASSIGN:
			process_assign(statement->first_child->child);
			break;
		case NONTERMINAL_PRINT:
			process_print(statement->first_child->child);
			break;
		case NONTERMINAL_SCAN:
			process_scan(statement->first_child->child);
			break;
		case NONTERMINAL_IF:
			process_if(statement->first_child->child);
			break;
		case NONTERMINAL_REPEAT:
			process_repeat(statement->first_child->child);
			break;
		case NONTERMINAL_RETURN:
			process_return(statement->first_child->child);
			break;
		case NONTERMINAL_WHILE:
			process_while(statement->first_child->child);
			break;
		case NONTERMINAL_COMPOUND:
			process_compound(statement->first_child->child);
			break;
			
		default: 
			printf("error\n");
	}
}

void process_compound(parse_tree_node * compound){
	process_statement_list(compound->first_child->next_child->child);
}

void process_scan(parse_tree_node *scan){
	parse_tree_node * IDs = get_child(scan->first_child, 2);
        while(1){
		printf("PUSHS\n");
		printf("PUSHM %d\n", lookup_symbol(IDs->first_child->child->lexeme));
		if(IDs->first_child->next_child == NULL)
			break;
		else   
			IDs = IDs->first_child->next_child->next_child->child;
	}

}

void process_print(parse_tree_node *print){
	process_expression(get_child(print->first_child, 2));
	printf("POPS\n");
}

void process_assign(parse_tree_node *assign){
	process_expression(get_child(assign->first_child, 2));
	printf("PUSHM %d\n", lookup_symbol(assign->first_child->child->lexeme));
}
void process_while(parse_tree_node *while_node){
	int start_label = label_num++;
	int end_label = label_num++;
	printf("LABEL label%d\n", start_label);
	process_conditional(get_child(while_node->first_child,2), end_label);
	process_statement(get_child(while_node->first_child,4));
	printf("LABEL label%d\n", end_label);
}

void process_if(parse_tree_node *if_node){
	int else_label = label_num++;
	int end_label = label_num++;
	process_conditional(get_child(if_node->first_child,2), end_label);
	process_statement(get_child(if_node->first_child,4));
	printf("GOTO label%d\n", end_label);
	printf("LABEL label%d\n", else_label);
	if(get_child(if_node->first_child,5)->element == TERMINAL_ELSE)
		process_statement(get_child(if_node->first_child,6));
	printf("LABEL label%d\n", end_label);
}

void process_repeat(parse_tree_node *repeat_node){
	int start_label = label_num++;
	int end_label = label_num++;
	printf("LABEL label%d\n", start_label);
	process_statement(get_child(repeat_node->first_child,1));
	process_conditional(get_child(repeat_node->first_child,3), end_label);
	printf("LABEL label%d\n", end_label);

}

void process_return(parse_tree_node *repeat_node){
	printf("not implemented as functions are not allowed\n");
}


void process_expression(parse_tree_node *expression){
	if(expression->first_child->child->element == NONTERMINAL_EXPRESSION){
		process_expression(expression->first_child->child);
		process_term(get_child(expression->first_child, 2));
		if(!strcmp(expression->first_child->next_child->child->lexeme, "+"))
			printf("ADD\n");
		else
			printf("SUB\n");
	} else if (expression->first_child->child->element == NONTERMINAL_TERM){
		process_term(expression->first_child->child);
	}
	else 
		printf("expression/term error %s\n", SYNTAX_ELEMENT_NAME(expression->first_child->child->element));
}

void process_term(parse_tree_node *term){
	if(term->first_child->child->element == NONTERMINAL_TERM){
		process_term(term->first_child->child);
		process_factor(get_child(term->first_child, 2));
		if(!strcmp(term->first_child->next_child->child->lexeme, "*"))
			printf("MUL\n");
		else
			printf("DIV\n");
	} else if (term->first_child->child->element == NONTERMINAL_FACTOR){
		process_factor(term->first_child->child);
	}
}

void process_factor(parse_tree_node *factor){
	if(factor->first_child->child->element == TERMINAL_MINUS){
		printf("PUSHI 0");
		process_primary(factor->first_child->next_child->child);
		printf("SUB");
	}else {
		process_primary(factor->first_child->child);
	}
}

void process_primary(parse_tree_node *primary){
	switch(primary->first_child->child->element){
		case TERMINAL_INTEGER:
			printf("PUSHI %s\n",primary->first_child->child->lexeme); 
			break;
		case TERMINAL_IDENTIFIER:
			printf("POPM %d\n",lookup_symbol(primary->first_child->child->lexeme));
			break;
		case TERMINAL_TRUTH_VALUE:
			if(!strcmp(primary->first_child->child->lexeme, "true"))
				printf("PUSHI 1\n");
			else
				printf("PUSHI 0\n");
			break;
		case TERMINAL_OPEN_PAREN:
			process_expression(primary->first_child->next_child->child);
			break;
	}
}
void process_conditional(parse_tree_node *conditional, int false_label){
	int skip_label = label_num++;
	char *operator;
	process_expression(get_child(conditional->first_child, 0));
	process_expression(get_child(conditional->first_child, 2));
	operator = get_child(conditional->first_child, 1)->lexeme ;
	if(!strcmp(operator, "==")){
		printf("EQU\n");
		printf("GOTOZ label%d\n", false_label);
	} else if (!strcmp(operator, "<")){
		printf("LES\n");
		printf("GOTOZ label%d\n", false_label);
	}else if (!strcmp(operator, ">")){
		printf("GRT\n");
		printf("GOTOZ label%d\n", false_label);
	}else if (!strcmp(operator, "!=")){
		printf("EQU\n");
		printf("GOTOZ label%d\n", skip_label);
		printf("GOTO label%d\n", false_label);
		printf("LABEL label%d\n", skip_label);
	}else if (!strcmp(operator, ">=")){
		printf("LES\n");
		printf("GOTOZ label%d\n", skip_label);
		printf("GOTO label%d\n", false_label);
		printf("LABEL label%d\n", skip_label);
	}else if (!strcmp(operator, "<=")){
		printf("GRT\n");
		printf("GOTOZ label%d\n", skip_label);
		printf("GOTO label%d\n", false_label);
		printf("LABEL label%d\n", skip_label);
	}




}
