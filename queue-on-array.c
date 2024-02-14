/*
	Course:		CS2024 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		02
	Task Set:	02 (Tasks 5 to 8)
	
	Aim: 		Implement Queue ADT over Array Data Structure
	Assume:		All data to be stored are characters except '$' 
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc

typedef struct {
	char* data;	// Pointer to the start of array. Space will be allocated by init()
	int size;	// Max size of queue
	int front;
	int rear;	// Index of next empty location 
} Queue;

/* Initialize a stack */
void init(Queue* q, int size) {
	q->data = (char*) malloc(size * sizeof(char));
	if (q->data == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	q->size = size;
	q->front = 0;
	q->rear = 0;	// index of next empty location 
}

int is_full(Queue* q){
	if (q->front == 0 && q->rear == q->size){
		return 1;
	}
	if (q->front - q->rear == 1){
		return 1;
	}
	return 0;
}



/* 	### Enqueue function 
	Exit behaviour:
		- On success: returns 0
		- On error: Message to stderr and returns -1
*/
int enqueue(Queue* q, char c) {
	if (is_full(q)) {
		fprintf(stderr, "Queue Overflow: %c\n", c);
		return -1;
	}

	printf("Adding element %c, at position %d\n", c, q->rear);
	q->data[q->rear] = c;
	q->rear++;

	printf("Underlying Array:\n");
	for (int i = 0; i < q->size; i++){
		printf("%c, ", q->data[i]);
	}
	printf("\b\b\n");
	
	
	if (q->rear == q->size + 1){
		q->rear = 0;
	}

	return 0;
}


int is_empty(Queue* q){
	return q->rear == q->front;
}

/* 	### Dequeue function 
	Exit behaviour:
		- On success: returns the character on the front of the queue
			(and shifts everyone in the queue one step forward)
		- On error: Message to stderr and returns '$'
*/
char dequeue(Queue *q) {
	char head;
	if (is_empty(q)) {
		fprintf(stderr, "Queue Empty\n");
		return '$';
	}

	head = q->data[q->front];
	q->front++;
	if (q->front == q->size + 1){
		q->front = 0;
	}
	return head;
}

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

int printQ(Queue* q){
	if (is_empty(q)){
		return 0;
	}
	// printf("%d %d\n", q->front, q->rear);
	if (q->rear > q->front){
		for (int i = q->front; i < q->rear; i++){
			printf("%c ", q->data[i]);
		}
	} else {
		for (int i = q->front; i <= q->size; i++){
			printf("%c ", q->data[i]);
		}
		for (int i = 0; i < q->rear; i++){
			printf("%c ", q->data[i]);
		}
	}
	printf("; %d - %d\n", q->front, q->rear);
}


void service(){
	srand(time(NULL));
	Queue q;
	init(&q, 10);
	int failed = 0;
	for (int i = 0; i < 10000; i++) {
		if (rand() < RAND_MAX / 5) {
			if (enqueue(&q, 't') == -1){
				failed++;
			}
		}
		if (i % 6 == 0){
			dequeue(&q);
		}
	}
	printf("%d tasks failed.\n", failed);
	
}

int main(){
	Queue q;
	init(&q, 4);

	enqueue(&q, 'a');
	enqueue(&q, 'b');
	enqueue(&q, 'c');
	enqueue(&q, 'd');
	printQ(&q);
	dequeue(&q);
	printQ(&q);
	enqueue(&q, 'e');
	printQ(&q);
}
	
int main5() {
	Queue q;
	int i, flag;
	char c;

	init(&q, 16);

	for(i = 0; i < 26; i++) {
		flag = enqueue(&q, 'a'+i);
		if(flag == -1)
			break;
		printf("Enqueued %c\n", 'a'+i);
		printQ(&q);
	}

	for(i = 0;; i++) {
		c = dequeue(&q);
		if (c == '$') {
			printf("\n");
			break;
		}
		printf("Dequeued %c\n", c);
		printQ(&q);
	}

	return 0;
}

int main2(){
	Queue q;
	init(&q, 16);

	for (int i = 0; i < 100; i++)
	{
		enqueue(&q, 'a');
		enqueue(&q, 'b');
		enqueue(&q, 'c');
		enqueue(&q, 'd');
		dequeue(&q);
		dequeue(&q);
		printQ(&q);
		dequeue(&q);
		dequeue(&q);
		printf("iteration %d\n", i + 1);
	}
	


	return 0;
}

int main4(){
	service();
}

/* Task 6. 	Queue using circular indexing of two pointers
	-	One main problem with the current implementation is that dequeue
		needs to shift all the remaining elements in the array and this
		is very inefficient.
	-	Modify the implementation to use two indexes q->rear and q->front
		together with a circular view of the array so that both enqueue and
		dequeue can be done in O(1) time.
	-	Warning: How do you identify the full and empty states of the queue?
*/

/* Task 7.	Helper functions
	-	Write the following helper functions for a queue
		a) int is_empty(Queue q) which return 1 if q is empty and 0 if not
		b) int is_full(Queue q) which return 1 if q is full and 0 if not
		c) print_queue(Queue q) which prints the queue from front to rear
		Note that we can use pass by value in these functions since they
		do not modify the contents of the queue.
*/

/* Task 8.	Buffering random service requests using a queue.
	Write a function to model the following scenario.
	 -  At each time-step a service request comes to a machine with 
	 	probability p = 1/5.
	-	The requests are stored in a buffer which can hold at most 10 requests
	 -	The machine takes 6 time steps to service each request. After finishing
	 	one requests it takes up the oldest pending request in the buffer.
	 -	Run this simulation for 10,000 time steps and count how many requests
	 	had to be dropped due to buffer overflow.
*/


