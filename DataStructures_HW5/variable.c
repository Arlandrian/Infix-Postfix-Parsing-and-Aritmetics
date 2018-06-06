#include <stdio.h>
//a struct for one variable
typedef struct Var {
	char name;
	int value;
}Var;

//a struct for keeping multiple variables (List)
typedef struct Variables {
	Var *arr;
	int count;
	int maxSize;
}Variables;

//Initializes a variables list
Variables InitVariables(int maxSize) {
	Variables variables;
	variables.maxSize = maxSize;
	variables.count = 0;
	variables.arr = (Var*)malloc(sizeof(Var)*maxSize);
	return variables;
}

//Add new variable to the given list
int AddVariable(Variables *vars,Var *newVar) {
	if (vars->count < vars->maxSize) {
		vars->arr[vars->count] = *newVar;
		vars->count++;
		return vars->count-1;
	}
	else {
		printf("Variables is full!\n");
		return -1;
	}
	
}

//linear search of the variable return value is the position of variable
int SearchVariable(Variables *vars, char name) {
	for (int i = 0; i < vars->count; i++)
	{
		if (vars->arr[i].name == name) {
			return i;
		}
	}
	return -1;
}

//prints all variables
void PrintAllVariables(Variables *vars) {
	if (vars->count == 0) {
		printf("There is no variables yet.\n");

	}else if (vars->count == 1) {
		printf("There is one Variable.\n");

	}else {
		printf("There are %d Variables.\n", vars->count);

	}
	for (int i = 0; i < vars->count; i++)
	{
		printf("%c := %d\n", vars->arr[i].name, vars->arr[i].value);
	}
}