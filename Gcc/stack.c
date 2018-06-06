#include <stdio.h>

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
		return NULL;
	}
	if (!isEmpty(stack)) {
		stack->top--;
		return stack->values[stack->top];
	}
	else {
		puts("Stack Empty");
		return NULL;
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

void Pause() {
	puts("Paused");
	//getch();
}
