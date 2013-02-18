#ifndef HAVE_SYMTABLE_H
#define HAVE_SYMTABLE_H

int create_symbol(int type, char *name);
int lookup_symbol(char *name);
int get_symbol_type(char *name);

#endif
