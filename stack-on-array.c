/*
	Course:		CS2024 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		02
	Task Set:	01 (Tasks 1 to 4)
	
	Aim: 		Implement Stack ADT over Array Data Structure
	Assume:		All data to be stored are characters except '$' 
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc

typedef struct {
	char* data;	// Pointer to the start of array. Space will be allocated by init()
	int size;	// Max size of stack
	int top;	// Index of next empty location
} Stack;

/* Initialize a stack */
void init(Stack* s, int size) {
	s->data = (char*) malloc(size * sizeof(char));
	if (s->data == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	s->size = size;
	s->top = 0;	// index of next empty location 
}

/* 	### Push function 
	Exit behaviour:
		- On success: returns 0
		- On error: Message to stderr and returns -1
*/
int push(Stack* s, char c) {
	if (s->top >= s->size) {
		// fprintf(stderr, "Stack Overflow\n");
		s->data = realloc(s->data, s->size * 2 * sizeof(char));
		s->size *= 2;
		printf("Doubled the size\n");
		// return -1;
	}

	s->data[s->top] = c;
	s->top++;
	

	return 0;
}

/* 	### Pop function 
	Exit behaviour:
		- On success: returns the character on top of stack
		- On error: Message to stderr and returns '$'
*/
char pop(Stack *s) {
	if (s->top <= 0) {
		fprintf(stderr, "Stack Empty\n");
		return '$';
	}
	if (s->top <= s->size / 2){
		s->data = realloc(s->data, (s->size / 2) * sizeof(char));
		s->size /= 2;
		printf("Halved the size\n");
	}

	s->top--;
	return s->data[s->top];
	

}
	
int main2() {
	Stack s;
	int i, flag;
	char c;

	init(&s, 16);

	for(i = 0; i < 26; i++) {
		flag = push(&s, 'a'+i);
		if(flag == -1)
			break;
		printf("Pushed %c\n", 'a'+i);
	}

	for(i = 0;; i++) {
		c = pop(&s);
		if (c == '$') {
			printf("\n");
			break;
		}
		printf("Popped %c\n", c);
	}


	return 0;
}



int matchParanthesis(char* str){
	Stack s;
	init(&s, 16);
	
	int i = 0;

	while(str[i] != '\0'){
		if (str[i] == '(') push(&s, str[i]);

		else if (str[i] == ')') {
			char last_bracket = pop(&s);
			if (last_bracket == '$' || last_bracket != '('){
				return 0;
			}
		}

		i++;
	}
	if (s.top != 0){
		return 0;
	}
	return 1;
}

int main(){
	char* str = "(())()";
	int res = matchParanthesis(str);
	printf("%d\n", res);
	return 0;
}
/* Task 2.	Unbounded Stack
	-	One main limitation of the current implementation is that the size
		of the stack is set by init() and then it remains fixed for life.
	-	Modify the push function to dynamically double the size of the array
		data when one tries to push a character onto a full stack.
	-	Hint. User realloc function in stdlib (read the manpage for realloc)
	-	This way the stack will get full if realloc() fails.
*/

/* Task 3.	Flexi Stack
	-	One drawback of the Unbounded stack is that once the stack grows
		it never shrinks back even if a lot of data is pushed out.
	-	Modify the pop function to dynamically half the size of the array
		data when only less that half the size is in use.
	-	Hint. User realloc function in stdlib (read the manpage for realloc)
*/

/* Task 4.	Checking balanced parentheses 
	-	Write a function which will take a string of opening and closing
		parentheses - i.e. '(' and ')' - and check whether every '(' has a
		matching ')' and vice-versa. 
	-	Hint. Use a stack - Push if '(', Pop and match if ')'.
*/
