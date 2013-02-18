#include "symbol_table.h"

int address = 100;
struct {
	char *name;
	int address;
	int type;
} symbols[100];

int n_symbols  = 0;

int create_symbol(int type, char *name){
	symbols[n_symbols].address = address++;
	symbols[n_symbols].name = name;
	symbols[n_symbols].type = type;
	n_symbols++;
	
}
int lookup_symbol(char *name){
	int i;
	for(i = 0; i < n_symbols; i++){
		if(!strcmp(symbols[i].name, name))
			return symbols[i].address;
	}
	return -1;
}
int get_symbol_type(char *name){
	int i;
	for(i = 0; i < n_symbols; i++){
		if(!strcmp(symbols[n_symbols].name, name))
			return symbols[n_symbols].type;
	}
	return -1;
	
}
