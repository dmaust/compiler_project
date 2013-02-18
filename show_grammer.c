#include <stdio.h>

#include "grammer.h"
int main(int argc, char **argv){
	int i;
	for(i = 1; i < 52; i++){
		int j = 0;
		printf("%d: %s --> ", i, syntax_element_info[production_rules[i].left_hand_side].name);
		while(production_rules[i].right_hand_side[j] != 0){
			printf("%s ", syntax_element_info[production_rules[i].right_hand_side[j]]);
			j++;
		}
		printf("\n    %s\n", production_rules[i].description);
	}
	return 0;
}
	
