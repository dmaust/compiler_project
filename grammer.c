#include <stdio.h>
#include <stdlib.h>

#include "grammer.h"




typedef struct {
	int rules[30];
	int positions[30];
	int n;
	int outgoing_elements[30];
	int outgoing_states[30];
	int n_outgoing;
} state;



void find_outgoing_elements(state *this, int * elements, int *n){
	int i;
	*n = 0;
	int outgoing_elements[100];
	for(i = 0; i < 100; i++){
		outgoing_elements[i] = 0;
	}
	for(i = 0 ; i < this->n; i++){
		int rule_num = this->rules[i];
		int position = this->positions[i];
		int next_element = production_rules[rule_num].rhs[position];
		outgoing_elements[next_element] = 1;
	}
	for(i = 0 ; i < 100; i++){
		if(outgoing_elements[i]){
			elements[*n] = i;
			(*n)++;
		}
	}
}

int check_existance_of_rule(state *this, int rule_num, int position){
	int i;
	for(i = 0; i < this->n; i++){
		if(this->rules[i] == rule_num){
			if(this->positions[i] == position || position == -1){
				return 1;
			}
		}
	}
	return 0;
}
void check_and_append_closure(state *this, int element){
	int i;
	for(i = 0; i < N_PRODUCTION_RULES; i++){
		if(production_rules[i].lhs == element){
			if(!check_existance_of_rule(this, i, 0)){
				this->rules[this->n] = i;
				this->positions[this->n] = 0;
				this->n++;
			}
		}
	}
}

void perform_closure_rule(state *this){
	int outgoing_elements[30];
	int n;
	int i;
	int old_num_rules = 0;
	while(this->n != old_num_rules){
		old_num_rules = this->n;
		find_outgoing_elements(this, outgoing_elements, &n);
		for(i = 0; i < n; i++){
			int element = outgoing_elements[i];
			if( !SYNTAX_TERMINAL_TEST(element)){
				check_and_append_closure(this, element);
			}
		}
	}

}

void print_state(state *this){
	int i;
	for(i = 0; i < this->n; i++){
		int rule = this->rules[i];
		int j;
		printf("%s -> ", SYNTAX_ELEMENT_NAME(production_rules[rule].lhs));
		for(j = 0; j < this->positions[i]; j++){
			printf("%s ", SYNTAX_ELEMENT_NAME(production_rules[rule].rhs[j]));
			
		}
		printf(".");
		while(production_rules[rule].rhs[j] != 0){
			printf("%s ", SYNTAX_ELEMENT_NAME(production_rules[rule].rhs[j]));
			j++;
		}
		printf("\n");
	}
	for(i = 0; i < this->n_outgoing; i++){
		if(this->outgoing_elements[i])
			printf("Outgoing %s: %d\n", SYNTAX_ELEMENT_NAME(this->outgoing_elements[i]), this->outgoing_states[i]);
		else
			printf("Completed item\n");
	}
}

state *states[200];
int n_states = 1;

state * advance_state(state *previous, int element){
	state * next_state;
	int i;
	next_state = (state *)malloc(sizeof(state));
	next_state->n = 0;
	for(i = 0; i < previous->n; i++){
		int rule = previous->rules[i];
		int position = previous->positions[i];
		if(production_rules[rule].rhs[position] == element){
			next_state->rules[next_state->n] = rule;
			next_state->positions[next_state->n] = position+1;
			next_state->n++;
		}
	}
	perform_closure_rule(next_state);
	return next_state;
}

int match_state(state *state1, state *state2){
	int i,j;
	if(state1->n != state2-> n) return 0;
	for(i = 0; i < state1-> n; i++){
		int found_in_state2 = 0;
		for(j = 0; j < state2->n; j++){
			if(state1->rules[i] == state2->rules[j] && state1->positions[i] == state2->positions[j])
				found_in_state2 = 1;
		}
		if(!found_in_state2)
			return 0;
	}
	return 1;
}
int find_state(state *this){
	int i;
	for(i = 1; i < n_states; i++){
		if(match_state(this, states[i])){
			return i;
		} 
	}
	return 0;
}

int get_state_position(state *this){
	int position = find_state(this);
	if(position){
		free(this);
		return position;
	} else {
		states[n_states] = this;
		n_states++;
		return n_states-1;
	}
}

void generate_outgoing_states(state *this){
	int n;
	int i;
	find_outgoing_elements(this, this->outgoing_elements, &this->n_outgoing);
	for(i = 0 ; i < this->n_outgoing; i++){
		if(this->outgoing_elements[i] == 0){
			/* use follow sets to reduce */
			this->outgoing_states[i] = 0;
		} else {
			int position;
			state * next_state;
			int element = this->outgoing_elements[i];
			next_state = advance_state(this, element);
			position = get_state_position(next_state);
			this->outgoing_states[i] = position;
		}
	}
}

void generate_initial_state(){
	state * initial;
	initial = (state *)malloc(sizeof(state));
	initial -> n = 1;
	initial -> rules[0] = 1;
	initial -> positions[0] = 0;
	perform_closure_rule(initial);
	states[1] = initial;
	n_states++;


}

void generate_other_states(){
	int i;
	for(i = 1; i < n_states; i++){
		generate_outgoing_states(states[i]);
	}
	
}
void print_states(){
	int i;
	for(i = 1; i < n_states; i++){
		printf("------------------------------------\n");
		printf("state: %d\n", i);
		print_state(states[i]);
	}
}

#define OPERATION_SHIFT  1
#define OPERATION_REDUCE 2
struct {
	int Operation; /** < 0 = no_operation, 1 = shift, 2 = reduce */
	int Rule_Number; /** < For reductions */
	int Next_State; /** < For shifts */
} parse_table [1000][59];

void fill_in_table_line(int state_number){
	int i;
	for(i = 0; i < states[state_number]->n_outgoing; i++){
		state* current_state = states[state_number];
		if(current_state->outgoing_elements[i]){
			/* shift */
			parse_table[state_number][current_state->outgoing_elements[i]].Operation = OPERATION_SHIFT;
			parse_table[state_number][current_state->outgoing_elements[i]].Next_State = current_state->outgoing_states[i];
		} else {
			int j;
			/* completed item */
			
			for(j = 0 ; j < current_state->n; j++){
				int rule_num = current_state->rules[j];
				int position = current_state->positions[j];
				int next_element = production_rules[rule_num].rhs[position];
				if(next_element == 0){
					int k = 0;
					int lhs = production_rules[rule_num].lhs;
					while(syntax_element_info[lhs].follow[k]){
						parse_table[state_number][syntax_element_info[lhs].follow[k]].Operation = OPERATION_REDUCE;
						parse_table[state_number][syntax_element_info[lhs].follow[k]].Rule_Number = rule_num;
						k++;
					}
				}
			}

		}
	}
}

void fill_in_table(){
	int i,j;
	for(i = 0; i < n_states; i++){
		for(j = 0; j < 59; j++){
		parse_table[i][j].Operation = 0;
		}
	}
	for(i = 1; i < n_states; i++){
		fill_in_table_line(i);
	}
}

void write_table(FILE * outfile){
	int i,j;
	fprintf(outfile, "struct { int operation; int arg } parse_table[%d][%d] = {\n", n_states, 59);
	for(i = 0; i < n_states; i++){
		fprintf(outfile, "{");
		for(j = 0; j < 59; j++){
			if(parse_table[i][j].Operation == 0)
				fprintf(outfile, " {0, 0} ");
			if(parse_table[i][j].Operation == OPERATION_SHIFT)
				fprintf(outfile, " {1, %d} ", parse_table[i][j].Next_State);
			if(parse_table[i][j].Operation == OPERATION_REDUCE)
				fprintf(outfile, " {2, %d} ", parse_table[i][j].Rule_Number);
			if(j < 58) fprintf(outfile, ",");

		}
		fprintf(outfile, "}");
		if(i < n_states-1) fprintf(outfile, ",");
		fprintf(outfile, "\n");
		
	}
	fprintf(outfile, "};\n");
}
int main(int argc, char **argv){
	FILE *outfile;
	generate_initial_state();
	generate_other_states();
	print_states();
	fill_in_table();
	outfile = fopen("parse_table.h", "w");
	write_table(outfile);
	fclose(outfile);
	return 0;
}
	
