/**
@file
Data Structures and Algorithms Spring 2018 Final Homework.

This project takes user input as infix form, translate it into postfix form, calculates it's result and
saves the result in one character variables.
You can make simple calculation.

@author

Name:				Numan Kemal Kazanc?

Student no: 		14011092

Date:				24.05.2018

E-Mail:				l1114092@std.yildiz.edu.tr

Compiler used:		Clang 3.8.0

IDE:				Visual Studio 2017 15.5.6

Operating System:	Windows 10 64bit
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STACK FUNCTONS START


typedef struct Stack {
	int *values;
	int size;
	int top;

}Stack;

char isEmpty(Stack *stack) {

	if (stack->top == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

char isFull(Stack *stack) {
	if (stack->top == stack->size - 1) {
		return 1;
	}
	else {
		return 0;
	}
}
//Initializes the stack dynamicly with given size
Stack *InitStack(int size) {
	Stack *stack = (Stack*)malloc(sizeof(Stack));

	stack->values = (int*)malloc(size * sizeof(int));

	stack->size = size;
	stack->top = 0;
	return stack;
}

int Pop(Stack *stack) {
	if (stack == NULL) {
		puts("Stack is not initialized");
		return (int)NULL;
	}
	if (!isEmpty(stack)) {
		stack->top--;
		return stack->values[stack->top];
	}
	else {
		puts("Stack Empty");
		return (int)NULL;
	}

}

void Push(Stack *stack, int newValue) {
	if (stack == NULL) {
		puts("Stack is not initialized");
		return;
	}
	if (!isFull(stack)) {

		stack->values[stack->top] = newValue;
		stack->top++;

	}
	else {
		puts("Stack Full");
	}
}



int Peek(Stack* stack) {
	
	return stack->values[stack->top - 1];
}

void PrintStack(Stack *stack, char isChar) {
	int count = stack->top;
	if (!isChar) {
		while (count > 0) {
			count--;
			if (count != 0)
				printf(" %d\n---\n", stack->values[count]);
			else
				printf(" %d\n---\n", stack->values[count]);

		}
	}
	else {
		while (count > 0) {
			count--;
			if (count != 0)
				printf(" %c\n---\n", stack->values[count]);
			else
				printf(" %c\n---\n", stack->values[count]);

		}
	}

}
char* myitoa(int number) {
	Stack *buffer = InitStack(10);
	int x;
	int i = 0;

	while (number > 0) {
		x = number % 10;
		Push(buffer, x);
		number /= 10;
		i++;
	}

	char *numbers = (char*)malloc(i+1);
	i = 0;
	while (!isEmpty(buffer)) {
		numbers[i] = Pop(buffer) + 48;
		i++;
	}

	numbers[i] = '\0';

	return numbers;

}

char* stackToString(Stack *stack,char isChar) {
	char *result = (char*)malloc((stack->top + 1) * sizeof(char)*(isChar?1:5));
	result[0] = '\0';
	int j = stack->top;
	int i = 0;
	
	while (j > 0) {
		j--;
		if (isChar) {
			result[i] = stack->values[j];
		}else{
			result = strcat(result, myitoa(stack->values[j]));
			result = strcat(result, " ");
		}
		
		
		i++;
	}
	result[i++] = '\0';
	return result;

}

//STACK FUNCTIONS END

//VARIABLES FUNCTIONS START

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

//VARIABLES FUNCTIONS END

#define MAX_VARIABLE_SIZE 50

char *filename = "expressions.txt";

//compares expression's priorities if a > b return 1, if equal 0 else -1
char expcmp(char a, char b) {
	if (b == '(')
		return 1;
	if (a == '+' || a == '-') {
		if (b == '+' || b == '-') {
			return 0;
		}
		else if (b == '*' || b == '/') {
			return -1;
		}
	}
	else if (a == '*' || a == '/' ) {
		if (b == '+' || b == '-') {
			return 1;
		}
		else if (b == '*' || b == '/') {
			return 0;
		}
	}
	
	return 1;//variables or numbers
}

//controls the input if its a number
char isNumber(char a) {
	if (a > 47 && a < 58 ) {
		return 1;
	}
	else {
		return 0;
	}
}

//controls the input if its an expression
char isExp(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(') {
		return 1;
	}
	else {
		return 0;
	}
}

//returns string in the given range
//I.E. ("abcdf",2,4) for this input the return value will be "cdf"
//if last == -1, result will include all the chars till the end of the string
char *substring(char* str, int first, int last) {
	int i = first;
	if (last != -1) {
		int x = last - first;
		if (x < 0) {
			return NULL;
		}
		int j = 0;

		char *result = (char*)malloc(sizeof(char)*(x + 1));
		while (i < last) {
			result[j] = str[i];
			i++;
			j++;
		}
		result[j] = '\0';
		return result;
	}
	else {
		int size;
		while (str[i]) {
			i++;
		}
		size = i - first;
		
		char *result = (char*)malloc(sizeof(char)*(size + 1));
		int j = 0;
		i = first;
		while (str[i]) {
			result[j] = str[i];
			i++;
			j++;
		}
		result[j] = '\0';
		return result;
	}
}

//translates the given infix expression to postfix
char *InfixToPostfix(char* str) {
	char *postfix = (char*)malloc(sizeof(char)*255);//for result
	
	Stack *stack = InitStack(MAX_VARIABLE_SIZE);

	char exp,stackPeek;//temporary variables
	char *temp = (char*)malloc(sizeof(char) * 255);
	int i=0;//counter for input
	int j;//counter for postfix
	j = 0;
	while (str[i] != ';' && str[i] != '\n') {

		if (str[i] != ' ') {

 			if (str[i] == '(') {
				Push(stack, str[i]);
				i++;
			}
			else if (str[i] == ')') {
				do {
					exp = Pop(stack);
					if (exp != '(') {
						postfix[j++] = exp;
						postfix[j++] = ' ';
						
					}
					
				} while (exp != '(');

				i++;
			}
			else if (isExp(str[i])) {
				exp = str[i];
				stackPeek = Peek(stack);

				if ( expcmp(exp,stackPeek) == 0 || expcmp(exp, stackPeek) == 1) {
					Push(stack, exp);
				}
				else {
					postfix[j++] = Pop(stack);
					postfix[j++] = ' ';
					
					i--;
				}
				i++;
			}
			else if(isNumber(str[i])){
				
				while (str[i] != ';' && str[i] != ' ') {
					postfix[j] = str[i];
					i++;
					j++;
				}
				postfix[j++] = ' ';
				
				
			}
			else {//variables
				postfix[j++] = str[i];
				postfix[j++] = ' ';
				

				i++;
			}
			//puts(postfix);
		}
		else {//space
			i++;
			
			printf("Postfix:");
			for (int k = 0; k < j; k++) {
				printf("%c", postfix[k]);
			}
			
			printf("\t\t");

			printf("Stack:%-10s\n",stackToString(stack,1));
			
		}
	}
	while (!isEmpty(stack)) {
		postfix[j++] = Pop(stack);
		postfix[j++] = ' ';
	}
	//postfix[j++] = ';';
	postfix[j++] = '\0';

	free(stack);
	return postfix;
}

//calculates the given postfix expressions result
int CalculatePostfix(char *str,Variables *vars,int variablePos) {
	
	Stack *stack = InitStack(MAX_VARIABLE_SIZE);

	char *number = malloc(10);//temporary string for atoi input

	int x,y;//temporary variables

	int temp;

	int i = 0;//counter for input
	int j;//counter for postfix

	while (str[i] != ';' && str[i] != '\0') {

		if (str[i] != ' ') {
			if (isNumber(str[i])) {
				j = 0;
				while (str[i] != ';' && str[i] != ' ') {
					number[j] = str[i];
					i++;
					j++;
				}
				number[j++] = '\0';

				Push(stack, atoi(number));
				printf("Stack:%-10s \n", stackToString(stack, 0));
			}
			else if(isExp(str[i])){
				y = Pop(stack);
				x = Pop(stack);
				if (str[i] == '-') {
					Push(stack, x - y);
				}else if (str[i] == '+') {
					Push(stack, x + y);

				}else if (str[i] == '/') {
					Push(stack, x / y);

				}else if (str[i] == '*') {
					Push(stack, x * y);

				}
				printf("Stack:%-10s \n", stackToString(stack, 0));
				i++;
			}
			else {

				int pos = SearchVariable(vars, str[i]);
				if (pos != -1) {
					temp = vars->arr[pos].value;
					Push(stack, temp);
					printf("Stack:%-10s \n", stackToString(stack, 0));
				}
				else {
					printf("Undefined variable found -> %c\n", str[i]);
				}

				i++;
			}
		}
		else {//space
			i++;
		}
		
		
		
	}
	int result = Pop(stack);
	vars->arr[variablePos].value = result;
	free(stack);
	return result;

}

//this function starts the calculations
void Calculation(char *input,Variables *vars) {
	

	int currentVarPos = SearchVariable(vars, input[0]);

	if (currentVarPos == -1) {//if variable doesn't exist create one
		Var *newVar;
		newVar = (Var*)malloc(sizeof(Var));
		newVar->name = input[0];
		newVar->value = 0;
		currentVarPos = AddVariable(vars, newVar);

	}

	strcpy(input, substring(input, 3, -1));

	printf("\nInfix => %c := ", vars->arr[currentVarPos].name);
	puts(input);

	puts("\n---------------------------------");
	printf("\nINFIX TO POSTFIX\n");
	strcpy(input, InfixToPostfix(input));
	
	printf("\nPostfix => %c := ", vars->arr[currentVarPos].name);
	puts(input);

	puts("\n---------------------------------");
	printf("\nCALCULATE POSTFIX\n");
	int x = CalculatePostfix(input, vars, currentVarPos);
	printf("\nResult => %c := %d\n", vars->arr[currentVarPos].name, x);
	puts("\n---------------------------------");
	
}

//prints help info
void help() {
	puts("--------------------------------------------------------------------");
	puts("-help\t			:help");
	puts("-clear\t			:clear screen");
	puts("-clearall\t		:clear all variables");
	puts("-printall			:print all variables to the console");
	printf("-readfile\t\t	:read expressions from \"%s\" file\n",filename);
	puts("-exit\t\t\t\t:exit");
	puts("\tExample Input := a = 4 + 3 ;");
	puts("--------------------------------------------------------------------");

}

//evaluates the user input
char Console(char *input,Variables *vars) {
	if (strcmp(input, "-help\n") == 0) {
		help();
	}
	else if (strcmp(input, "-clear\n") == 0) {
		system("cls");
	}
	else if (strcmp(input, "-clearall\n") == 0) {
		vars->count = 0;
		puts("All variables cleared.");
	}
	else if (strcmp(input, "-printall\n") == 0) {
		PrintAllVariables(vars);
	}
	else if (strcmp(input, "-readfile\n") == 0) {
		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			puts("expressions.txt could not found!");
		}
		for (int i = 0; fgets(input, 255, fp); i++)
		{
			Calculation(input, vars);
		}
		fclose(fp);
		puts("File read successful.");
	}
	else if (strcmp(input, "-exit\n") == 0) {
		return 1;
	}
	return 0;
}

int main() {
	char input[255]="";
	int inputPos=0;

	//keeps all the variables that user entered at runtime
	Variables vars = InitVariables(MAX_VARIABLE_SIZE);

	//prints help information
	help();

	char exit = 0;
	do {
		
	    fgets(input, 255, stdin);

		if (input[0] == '\n') {//if user enters empty
			continue;
		}
		else if (input[0] == '-') {
			exit = Console(input,&vars);
		}
		else {
			puts("");//newline
			if (input[2] == '=') {
				Calculation(input, &vars);
			}
		}

	} while (!exit);
	
}