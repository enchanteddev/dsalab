/*
	Name:		Kaushik Rawat
	Roll No:	112201015
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 9
	Tasks:		5 to 7
	Aim: 		Process an infix expression
*/

#include <stdio.h>
#include <limits.h>
#include "stack.h"
#include "token.h"

/* Task 5. Evaluate a given fully parenthesised infix expression 
*/
int infix_eval(char *str) {
/*
	Input: 	A fully parenthesised infix expression
	Output: The result of evaluating the expression
	Steps:
		1.	Tokenise str to get a token array (say ta)
		2.	Declare and initialise an operand stack (say valStack) of required size
			(num of tokens in ta is one way to estimate the size)
		3.	Declare and initialise an operator stack (say opStack) of required size
			(num of tokens in ta is one way to estimate the size)
			(int stack can also hold characters)
		3.	Linearly process ta till you hit a token of type EoS
			a) 	If the current token is an operand, push the value to valStack
			b) 	If the current token is a parOpen, push the paranthesis to opStack
			c) 	If the current token is an operator  push the operator (char) to opStack
			d) 	If the current token is a parClose then do the following computation
				- pop opStack and store the result in a character op
				-	If op is '('
					-	Skip over it
				-	Else If op is the unary negation ~
					-	pop valStack once, 
						(break the token scan if you get INT_MIN as value)
					-	negate the popped value, and 
					-	push the result back to valStack
				-	Else If op is a binary operator
					-	pop valStack twice to get val2 and val1 (in that order)
						(break the token scan if you get INT_MIN as either value)
					-	compute the result = val1 operator val2 using a switch case
						on the operator, and
					-	push the result back to valStack
				-	pop opStack once more and confirm that it is '('
					Otherwise break
		4.	If the current token is EoS, the final result can be popped from
			the valStack.
			Otherwise the token processing was not complete. In this case,
			free the stacks and return INT_MIN
		5.	Now check that the valStack and opStack are empty to make sure that
			the expression was valid.
			Otherwise the token processing was not complete. In this case,
			free the stacks and return INT_MIN

	Error repsonse:	 Print the following error messages to stderr and return INT_MIN
		1. Tokenise error:  "Error: Could not tokenise <str>. Returning <INT_MIN>.\n"
		2. Evalution error: "Error in infix_eval: Invalid infix expression\n"
*/
	Token*	ta = tokenise(str);
	if(ta == NULL){
		fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
		return INT_MIN;
	}

	int numTokens = 0;
	while(ta[numTokens++].type != EoS){
		if (ta[numTokens - 1].type == operand && !(ta[numTokens].type == operator || ta[numTokens].type == parClose)){
			fprintf(stderr, "Error in infix_eval: Invalid infix expression\n");
			return INT_MIN;
		} else if (ta[numTokens - 1].type == parClose && !(ta[numTokens].type == operator || ta[numTokens].type == parClose || ta[numTokens].type == EoS)){
			fprintf(stderr, "Error in infix_eval: Invalid infix expression\n");
			return INT_MIN;
		} else if (ta[numTokens - 1].type == operator && ta[numTokens].type == operator){
			fprintf(stderr, "Error in infix_eval: Invalid infix expression\n");
			return INT_MIN;
		}
	}

	iStack valStack;
	init_is(&valStack, numTokens);

	iStack opStack;		// Integer stack can also hold characters
	init_is(&opStack, numTokens);
	
	// Task 5. Solution
	int operatorsSinceLastBracket = 0;
	while(ta->type != EoS){
		if (ta->type == operand){
			push_is(&valStack, ta->value);
		} else if (ta->type == parOpen || ta->type == operator){
			if (ta->type == parOpen) operatorsSinceLastBracket = 0;
			else {
				operatorsSinceLastBracket++;
				// printf("count = %d\n", operatorsSinceLastBracket);
				if (operatorsSinceLastBracket > 1){
					fprintf(stderr, "Error in infix_eval: Invalid infix expression\n");
					return INT_MIN;
				}
			}
			push_is(&opStack, ta->op);
		}else if (ta->type == parClose){
			operatorsSinceLastBracket = 0;
			char op = pop_is(&opStack);
			while(op != '('){
				if (op == '~'){
					int val = pop_is(&valStack);
					if (val == INT_MIN) break;
					push_is(&valStack, -val);
				} else {
					int val2 = pop_is(&valStack);
					int val1 = pop_is(&valStack);
					if (val2 == INT_MIN || val1 == INT_MIN) break;
					int result;
					switch (op)
					{
						case '+':
							result = val1 + val2;
							break;
						case '-':
							result = val1 - val2;
							break;
						case '*':
							result = val1 * val2;
							break;
						case '/':
							result = val1 / val2;
							break;
						
						default:
							break;
					}
					push_is(&valStack, result);
				}
				op = pop_is(&opStack);
			}
		}
		ta++;
	}

	int answer = pop_is(&valStack);
	if (ta->type != EoS || !isempty_is(&valStack) || !isempty_is(&opStack)){
		fprintf(stderr, "Error in infix_eval: Invalid infix expression\n");
		answer = INT_MIN;
	}



	free_is(&valStack);
	free_is(&opStack);

	return answer; // You may want to edit this
}

/* Task 6. Generate an expression tree from a given fully parenthesised infix expression
*/
eTree* infix_to_etree(char *str) {
/*
	Input: 	A fully parenthesised infix expression
	Output: Pointer to the root of the equivalent expression tree.
	Steps: 	Adapt the steps for infix_eval()
	Hint:	Use pointer stacks for node stack and operator stack
	Error response:	 Print the following error messages to stderr and return NULL
		1. Tokenise error: 	"Error in infix_to_etree : Could not tokenise <str>. 
		2. Evaluation error: "Error in infix_to_etree: Invalid infix expression."
*/

	Token*	ta = tokenise(str);
	if(ta == NULL){
		fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
		return NULL;
	}

	int numTokens = 0;
	while(ta[numTokens++].type != EoS){
		if (ta[numTokens - 1].type == operand && !(ta[numTokens].type == operator || ta[numTokens].type == parClose)){
			fprintf(stderr, "Error in infix_tree1: Invalid infix expression\n");
			return NULL;
		} else if (ta[numTokens - 1].type == parClose && !(ta[numTokens].type == operator || ta[numTokens].type == parClose || ta[numTokens].type == EoS)){
			fprintf(stderr, "Error in infix_eval: Invalid infix expression\n");
			return NULL;
		} else if (ta[numTokens - 1].type == operator && ta[numTokens].type == operator){
			fprintf(stderr, "Error in infix_tree2: Invalid infix expression\n");
			return NULL;
		}
	}

	pStack nodeStack;
	init_ps(&nodeStack, numTokens);
	
	pStack opStack;
	init_ps(&opStack, numTokens);
	
	// Task 6. Solution

	int operatorsSinceLastBracket = 0;
	while(ta->type != EoS){
		if (ta->type == operand){
			eTree* operandToken = create_node(*ta, NULL, NULL);
			push_ps(&nodeStack, operandToken);
		} else if (ta->type == parOpen || ta->type == operator){
			if (ta->type == parOpen) operatorsSinceLastBracket = 0;
			else {
				operatorsSinceLastBracket++;
				// printf("count = %d\n", operatorsSinceLastBracket);
				if (operatorsSinceLastBracket > 1){
					fprintf(stderr, "Error in infix_to_etree3: Invalid infix expression\n");
					return NULL;
				}
			}
			eTree* operatorToken = create_node(*ta, NULL, NULL);
			push_ps(&opStack, operatorToken);
		}else if (ta->type == parClose){
			operatorsSinceLastBracket = 0;
			eTree* op = pop_ps(&opStack);
			if (op == NULL) break;
			while(op->token.op != '('){
				if (op->token.op == '~'){
					eTree* val = pop_ps(&nodeStack);
					if (val == NULL) break;
					op->right = val;
					push_ps(&nodeStack, op);
				} else {
					eTree* val2 = pop_ps(&nodeStack);
					eTree* val1 = pop_ps(&nodeStack);
					if (val2 == NULL || val1 == NULL) break;
					op->left = val1;
					op->right = val2;
					push_ps(&nodeStack, op);
				}
				op = pop_ps(&opStack);
				if (op == NULL){
					fprintf(stderr, "Error in infix_tree4: Invalid infix expression\n");
					return NULL;
				}
			}
		}
		ta++;
	}

	eTree* root = pop_ps(&nodeStack);
	if (ta->type != EoS || !isempty_ps(&nodeStack) || !isempty_ps(&opStack)){
		fprintf(stderr, "Error in infix_tree5: Invalid infix expression\n");
		root = NULL;
	}

	free_ps(&nodeStack);
	free_ps(&opStack);

	return root; // You may want to edit this
}

/* Task 7. Generate a postfix expression from a given expression tree
*/
void etree_to_postfix(eTree *t) {
/* 	Input:	The root of an expression tree
	Action: Print the postfix expression of this tree
*/
	if (t == NULL)
		return;
		
	// Task 8. Solution
	if (t->token.type == operator){
		etree_to_postfix(t->left);
		etree_to_postfix(t->right);
		printf(" %c ", t->token.op);
	} else if (t->token.type == operand){
		printf(" %d ", t->token.value);
	}
}

/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	Token *ta;

	// Testing postfix_eval()
	printf("\nTesting Tasks 5 to 8.\n");
	printf("=======================\n");

	int nTests = 10;
	char infix[][100] = {
		"(2+31)",					// 33	
		"(2+(~31))", 				//-29
		"(10/(~(2+3)))", 			// ~2
		"((2+(3*1))-9)", 			// -4
		"(((2-3)+4)*(5+(6*7)))",	// 141
		"(1+2))",					// Invalid
		"(()+4)*(5+(6*7)))",	// Invalid
		"(((1+2-3)+4)*(5+(6*7)))",	// Invalid
		"(((2-3))+4)*(5+(6*7)))",	// Invalid
		"((1 + 2) (3 + 4) +)"					// Guess what
	};

	int result;
	eTree *root;
	for(int i = 0; i < nTests; i++) {
		char* s = infix[i];
		// Task 5 Test
		printf("\n%d. Processing \"%s\"\n", i+1, s);
		printf("-----------------------------\n");
		result = infix_eval(s);
		printf("Task 5. Evaluate infix expression: Result = %d\n", result);
		// Task 5 Test
		root = infix_to_etree(s);
		if(root == NULL){
			printf("Task 6. Invalid infix expression\n");
		}
		else {
			printf("Task 6. Expression Tree\n", 
				root->token.value, root->token.op);
			print_etree(root);
		}
		// Task 7 Test
		printf("Task 7. Postfix expression: ");
		etree_to_postfix(root);
		printf("\n");

	}

	return 0;
}


