/**
@file
Data Structures and Algorithms Spring 2018 Final Homework.

This project takes user input as infix form, translate it into postfix form, calculates it's result and
saves the result in one character variables.
You can make simple calculation.

@author

Name:				Numan Kemal Kazanci

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
#include "stack.c"
#include "variable.c"

#define MAX_VARIABLE_SIZE 50


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
	//char postfix[255] = "";//for result
    
	char *postfix = (char*)malloc(sizeof(char)*255);
	Stack *stack = InitStack(MAX_VARIABLE_SIZE);

	char exp,stackPeek;//temporary variables

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

	char number[10];//temporary string for atoi input

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

				i++;
			}
			else {

				int pos = SearchVariable(vars, str[i]);
				if (pos != -1) {
					temp = vars->arr[pos].value;
					Push(stack, temp);
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

	printf("Infix => %c := ", vars->arr[currentVarPos].name);
	puts(input);

	strcpy(input, InfixToPostfix(input));
	
	printf("Postfix => %c := ", vars->arr[currentVarPos].name);
	puts(input);

	int x = CalculatePostfix(input, vars, currentVarPos);
	printf("\nResult => %c := %d\n\n", vars->arr[currentVarPos].name, x);
	
}

//prints help info
void help() {
	puts("--------------------------------------------------------------------");
	puts("-help\t			:help");
	puts("-clear\t			:clear screen");
	puts("-clearall\t		:clear all variables");
	puts("-printall			:print all variables to the console");
	puts("-readfile\t\t	:read expressions from \"expressions.txt\" file");
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
		FILE *fp = fopen("expressions.txt", "r");
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
