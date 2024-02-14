/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		03 | Linked Lists
	Task Set:	2 | Doubly Linked Lists (dLL)

	Aim: 		Implement a doubly linked list with some basic functions.
	Assume:		All data to be stored are integers
*/

#include <limits.h>	// For INT_MAX
#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc

/* 	Unlike a singly linked list, it is not easy to define a doubly linked
	list in a recursive style. So we need two stucts - 
		(a) One struct for node, which holds the data and two pointers - 
			one to the next node and one to the previous node.
		(b)	One struct for the list itself - which contains two pointers -
			one to the fist node in the list and one to the last.
	When implementing a dLL the following two additional functionalities
	(one transparent one opaque) are needed to make a dLL useful.
		(a) insert_at_pos(), get_from_pos(), and delete_at_pos() functions
			should accept negative integers also as position argument. 
			-1 : last node (tail), -2 is previous to -1 and so on.
		(b) if the given position is negative, the list should be traversed
			backwards from the tail. This speeds up data access in the 
			second half of large lists 
*/
typedef struct node{
	int 			data;	// The data stored in the node
	struct node*	prev;	// Pointer to previous node
	struct node*	next;	// Pointer to next node
} node;

typedef struct dLL{
	struct node*	head;	// Pointer to first node in the list
	struct node*	tail;	// Pointer to last node in the list
} dLL;

node* create_node(int data, node *next, node *prev) {
/*
	Inputs:
		1. 	Data for the new node to be inserted
		2.	A node pointer to be set as the next pointer of the new node
		2.	A node pointer to be set as the prev pointer of the new node
	Actions:
		1.	Memory required for a new node is allotted.
		2.	The data and the two pointers of the new node are set from the inputs
	Error Response:
		1.	Prints "Error: Memory allocation for new node failed." to stderr if
			malloc fails.	
		2.	Returns NULL if the new node cannot be created
*/
	node* new = (node *) malloc(sizeof(node));
	if(new == NULL) {
		fprintf(stderr, "Error: Memory allocation for new node failed\n");
		return NULL;
		}
	new->data = data;
	new->next = next;
	new->prev = prev;
	return new;
}

dLL* create_dLL(node *head, node *tail) {
/*
	Inputs:
		2.	A pointer to the head of the list (NULL is allowed)
		2.	A pointer to the tail of the list (NULL is allowed)
	Actions:
		1. 	A new dLL struct with the given head and tail is returned
*/
	dLL* list = (dLL *) malloc(sizeof(dLL));
	if(list == NULL) {
		fprintf(stderr, "Error: Memory allocation for dLL failed\n");
		return NULL;
		}
	list->head = head;
	list->tail = tail;
	return list;
}


/* Task 6. 
	Copy all the functions (including main) that you have in simple-linked-list.c
	here and edit all the COMMENTS to reflect the changes needed.
*/


/* Task 1. 
	Implement a function to create a new node with the given data and add it to
	the beginning of the given list and return a pointer to the start of the
	bigger list.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error response have to be as in the comments below.
*/
dLL* insert_at_start(int data, dLL* list) {
/*
	Inputs:
		1. 	Data for the new node to be inserted
		2.	A list
	Actions:
		1.	A new node with the received data is inserted at the head of the
			received list
		2.	The pointer to the list (with the head now pointing to the new node) is returned.
	Error Response:
		1.	Prints "Error: Insertion at start failed." to stderr
		2.	Returns NULL if the new node cannot be created
*/
// Task 1 - Edit one line below to solve Task 1
	node* new = create_node(data, list->head, NULL);
	if(new == NULL) {
		fprintf(stderr, "Error: Insertion at start failed\n");
		return NULL;
		}
	if (list->head != NULL) list->head->prev = new;
	if (list->tail == NULL) list->tail = new;
	list->head = new;
	return list;
}


/* Task 2. 
	Implement a function to create a new node with the given data and add it to
	the specified position in the given list and return a pointer to the start
	of the bigger list.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
	-	Instead of directly using create_node() use insert_at_start() to insert
		the new node at the appropriate position.
*/
dLL* insert_at_pos(int data, dLL* list, int pos) {
/*
	Inputs:
		1. Data for the new node to be inserted
		2. A list
		3. The position in the list where to insert the new node (0 = start) 
	Actions:
		1.	If position is within range, a new node with the given data is
			inserted to the list at the specified position. 
		2.	The pointer to the list is returned.
	Error Responses:
		1	If the position is larger than the current length of the list, an
			error message "Error: Position out of range." is printed and a NULL
			pointer is returned.
		2	Returns NULL pointer also if the new node could not be created
*/
// Task 2 Solution
	if (pos == 0){
		return insert_at_start(data, list);
	}

	if (pos > 0){
		node* curr = list->head->next;
		for(unsigned int i = 1; i < pos ; i++){
			curr = curr->next;
			if (curr == NULL){
				printf("Error: Position out of range.");
				return NULL;
			}
		}
		node* new = create_node(data, curr, curr->prev);
		curr->prev->next = new;
		curr->prev = new;
		return list;
	} else {
		node* curr = list->tail;
		for(int i = 0; i < -pos - 1 ; i++){
			curr = curr->prev;
			if (curr == NULL){
				printf("Error: Position out of range.");
				return NULL;
			}
		}
		node* new = create_node(data, curr->next, curr);
		if (curr->next != NULL) curr->next->prev = new;
		else list->tail = new;
		curr->next = new;
		return list;
	}
}

void print_list(node *start) {
/*
	Input:	A list
	Actions:
		Prints the data in the linked list from start to end
		in the format:  D0 - D1 - ... - Dn - NULL
*/
	// node* start = list->head;
	printf("%d, ", start->data);
	if(start->next == NULL){
		printf("NULL\n");
		return;
	}
	else
		print_list(start->next);
}

int get_from_start(dLL* list) {
/*
	Inputs:
		1. A list
	Actions:
		1. Returns the data stored in the first node.
	Error Response:
		1.	Prints an error message "Error: Attempt to ready from empty list."
			to stderr and returns INT_MAX if the list is empty.
*/
	if(list == NULL) {
		fprintf(stderr, "Error: Attempt to ready from empty list.\n");
		return INT_MAX;
		}
	else
		return list->head->data;
}

/* Task 3. 
	Implement a function to get the data from a node at a given position in a
	given list.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
int get_from_pos(dLL* list, int pos) {
/*
	Inputs
		1. 	A list 
		2. 	Position from which to read the data
	Action
		1.	Returns the data stored in the node at the given position (start = 0).
	Error Responses:
		1.	Prints an error message "Error: Attempt to read outside of the
			list." to stderr and returns INT_MAX if one tries to read from
			outside the index-range of the list
*/
// Task 3 Solution
	if (pos >= 0){
		node* curr = list->head;
		for(unsigned int i = 0; i < pos ; i++){
			curr = curr->next;
			if (curr == NULL){
				printf("Error: Position out of range.");
				return INT_MAX;
			}
		}
		return curr->data;
	} else {
		node* curr = list->tail;
		for(int i = 0; i < -pos - 1 ; i++){
			curr = curr->prev;
			if (curr == NULL){
				printf("Error: Position out of range.");
				return INT_MAX;
			}
		}
		return curr->data;
	}

}

/* Task 4. 
	Implement a function to search for a particular data in the given list and
	return the position of the first node in the list which contains that data.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
int find(int data, dLL* list) {
/*
	Inputs
		1. 	The data to search for
		2. 	A list.
	Action
		1. 	Returns the position of the first node with the given data.
		2.	Returns -1 if the given data is not in the list
	Error Response:
*/
// Task 4. Solution
	node* curr = list->head;
	int i = 0;
	while(curr != NULL){
		if (curr->data == data){
			return i;
		}
		curr = curr->next;
		if (curr == NULL){
			return -1;
		}
		i++;
	}

}

void delete_node(node* start){
	while(start != NULL) {
		delete_node(start->next);
		free(start); 
	}
}
void delete_list(dLL* list) {
/*
	Inputs
		1. A list
	Actions
		1. Frees the memory location for all the nodes in this list
		2. Frees the memory location for the dLL struct
			
*/
	node* start = list->head;
	delete_node(start);
	free(list);
}

dLL* delete_first(dLL* list) {
/*
	Inputs
		1. 	A list
	Actions
		1. 	Frees the memory allotted for the start node
		2.  Head of list points to the next element
		3.	Returns the pointer to the list.
	Error Responses:
		1.	Prints an error message "Error: Attempt to delete from and empty
			list." to stderr and returns NULL if the input list is empty.
*/
	node* start = list->head;
	if(start == NULL) {
		fprintf(stderr, "Error: Attempt to delete from and empty list.\n");
		return NULL;
	}
	list->head = start->next;
	free(start);
	return list;
}

dLL* delete_last(dLL* list) {
/*
	Inputs
		1. 	A list
	Actions
		1. 	Frees the memory allotted for the end node
		2.  Tail of list points to the prev element
		3.	Returns the pointer to the list.
	Error Responses:
		1.	Prints an error message "Error: Attempt to delete from and empty
			list." to stderr and returns NULL if the input list is empty.
*/
	node* end = list->tail;
	if(end == NULL) {
		fprintf(stderr, "Error: Attempt to delete from and empty list.\n");
		return NULL;
	}
	list->tail = end->prev;
	list->tail->next = NULL;
	free(end);
	return list;
}

/* Task 5. 
	Implement a function to delete a single node from the given list at the
	given position and stitch the list back together.
	-	Do not change the function interface given below.
	-	Inputs, Actions and Error Responses have to be as in the comments below.
*/
dLL* delete_at_pos(dLL* list, int pos) {
/*
	Inputs
		1. 	A list
		2. 	The position of the node to be deleted
	Actions
		1. 	Frees the memory allotted for the node at the specified position
		2.	Links the next pointer of the previous node to 	the next node.
		3.	Links the prev pointer of the next node to 	the previous node.
		4.	Returns the pointer of the list
	Error Responses:
		1.	Prints an error message "Error: Attempt to delete outside of the
			list." to stderr and returns NULL if one tries to delete a node
			outside the index-range of the list.
*/
// Task 5 Solution
	if (pos == 0){
		return delete_first(list);
	}
	if (pos == -1){
		return delete_last(list);
	}
	if (pos > 0){
		node* curr = list->head->next;
		for(int i = 1; i < pos ; i++){
			curr = curr->next;
			if (curr == NULL){
				printf("Error: Position out of range.");
				return NULL;
			}
		}
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free(curr);
		return list;
	} else {
		node* curr = list->tail;
		for(int i = 1; i < -pos ; i++){
			curr = curr->prev;
			if (curr == NULL){
				printf("Error: Position out of range.");
				return NULL;
			}
		}
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free(curr);
		return list;
	}

}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	int i;
	dLL *list = create_dLL(NULL, NULL), *tempList = create_dLL(NULL, NULL);

	// Test for Task 1: insert_at_start()
	printf("Testing Task 1: insert_at_start()\n");
	for(i = 0; i < 10; i++) {
		list = insert_at_start(i, list);
		print_list(list->head);
	}	
	printf("============================\n");


	// Test for Task 2: insert_at_pos()
	
	printf("Testing Task 2: insert_at_pos()\n");
	for(i = -4; i < 10; i++) {
		list = insert_at_pos(i, list, i);
		print_list(list->head);
	}
	// Testing insert outside of the range
	tempList = insert_at_pos(32, list, 32);
	if(tempList == NULL) {
		printf("NULL pointer returned.\n");
	}
	printf("============================\n");
	tempList = insert_at_pos(32, list, -32);
	if(tempList == NULL) {
		printf("NULL pointer returned.\n");
	}
	printf("============================\n");
	


	// Test for Task 3: get_from_pos()
	
	printf("Testing Task 3: get_from_pos()\n");
	print_list(list->head);
	for(i = -16; i < 25; i += 4)
		printf("Data at pos %d is %d\n", i, get_from_pos(list, i));
	printf("============================\n");
	

	// Test for Task 4: find()
	
	printf("Testing Task 4: find()\n");
	print_list(list->head);
	for(i = 0; i < 16; i+=3)
		printf("Position of %d is %d\n", i, find(i, list)); 
	printf("============================\n");
	

	// Test for Task 5: delete_at_pos()
	
	printf("Testing Task 5: delete_at_pos()\n\n");
	print_list(list->head);
	for(i = -6; i < 10; i += 3) {
		printf("Deleting data (%d) at pos %d\n", get_from_pos(list, i), i);
		list = delete_at_pos(list, i);
		print_list(list->head);
	}
	// Testing delete outside of the range
	tempList = delete_at_pos(list, 1000);
	if(tempList == NULL) {
		printf("NULL pointer returned.\n");
	}
	printf("============================\n");
	

	free(list);
	return 0;
}


/* Task 7. 
	Edit the code inside of each function to implement the functionality on doubly
	linked lists. You can assume that position indices will still be non-negative.
	Hence you need to do forward traversal for this Task. (Negative indices and
	reverse traversals is the next Task.
*/

/* 
	Task 8. Allow negative indices and implement reverse traversal for them.
	(a) insert_at_pos(), get_from_pos(), and delete_at_pos() functions
		should accept negative integers also as position argument. 
		-1 : last node (tail), -2 is previous to -1 and so on.
	(b) if the given position is negative, the list should be traversed
		backwards from the tail. This speeds up data access in the 
		second half of large lists 
	(c) Modify the Testing loops for these functions in main to test for
		negative indices also.
*/

/* 	This main() only contains stuff to test the data structures
	Replace this with the main from simple-linked-list.c
*/
// int main() {

// 	node 	*new = create_node(10, NULL, NULL);
// 	dLL	 	*list = create_dLL(new, new);

// 	printf("%d\n", new->data);
// 	printf("%d\n", list->head->data);
// 	printf("%d\n", list->tail->data);

// 	return 0;
// }
