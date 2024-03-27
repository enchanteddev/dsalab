/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 6 | 22/Feb/2024
	Tasks:		4,5,6,7
	
	Aim: 		1. Implement Quick Sort
	Assume:	All data to be stored are of type int
*/

#include <stdio.h>


#define ARRAY_SIZE 16


int print_array(int* array){

 /*Prints the contents of the given array*/
 
	int i;
	for (i =0; i< ARRAY_SIZE; i++){
		printf("%d,", array[i]);
	}
	printf("\n");
	
	return 0;

}

/*Task 4: Write a function to swap two elements (given by their indices) of an array.*/

int swap(int* array, int index1, int index2){
	if (index1 >= ARRAY_SIZE || index2 >= ARRAY_SIZE){
		return -1;
	}

	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;

	return 0;
}

/* Task 5: Write a function to generate a pivot element*/

int get_pivot(int* array, int start_index, int end_index){

/* Takes as input an array and two boundary indices. Generates a pivot element for the sub-array given by the start_index and end_index. Swaps the pivot element with the element with the element given by the end_index*/ 
	
	return start_index;
}

/* Task 6: Write a function to partition a given sub-array based on a pivot*/

int partition(int* array, int start_index, int end_index){

/* Takes as input an array and two boundary indices. Partitions the sub-array given by the boundary indices based on a pivot and returns the partition index. That is, all the elements from the left boundary to the partition index are less than or equal to the pivot, and all the elements from (partition index+1)-th location to the right boundary are greater than pivot. This pivot should be generated by calling the get_pivot() function.*/

	int pivot = get_pivot(array, start_index, end_index);
	int left = start_index;
	int right = end_index;
	while (left < right){
		while (array[left] <= array[pivot]){
			left ++;
		}
		while (array[right] > array[pivot]){
			right --;
		}
		if (left < right){
			swap(array, left, right);
		}
	}
	swap(array, pivot, right);
	return right;
}

/*Task 7: Implement Quick Sort recursively using the partition function*/

int quick_sort(int* array, int start_index, int end_index){

/* Takes as input an array and two boundary indices. Returns the subarray given by the boundary indices sorted in the non-decreasing order. Implment this using the function partition and making recursive calls to itself*/
	
	if (start_index >= end_index){
		return 0;
	}
	int p_index = partition(array, start_index, end_index);
	quick_sort(array, start_index, p_index - 1);
	quick_sort(array, p_index + 1, end_index);
	return 0;
}

int main()
{

	/* Create test array*/
	int array[ARRAY_SIZE] = {3,2,1,6,5,4,9,8,7,12,12,10,10,13,14,15};
	// int array[ARRAY_SIZE] = {3,223,1,6,5,4,9,8,7,125090,12,10,10,13,14,15};
	// int array[ARRAY_SIZE] = {3,223,1,6,5,4,9,8,7,125090,12,10,10,13,14,10};
	// int array[ARRAY_SIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	// int array[ARRAY_SIZE] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,4,0};

	/*Test Task 5*/
	
	int partition_index;
	int left_boundary=6;
	int right_boundary=14;
	print_array(array);
	printf("\n-----------------------------\n");
	printf("left boundary = %d     right boundary = %d\n",left_boundary, right_boundary);
	partition_index=partition(array, left_boundary, right_boundary);
	printf("partition index = %d \n", partition_index);
	printf("\n-----------------------------\n");
	print_array(array);
	printf("\n-----------------------------\n");

	/*Test Task 6*/
	
	print_array(array);
	printf("\n-----------------------------\n");
	quick_sort(array,0, ARRAY_SIZE-1);
	printf("sorted array\n");
	print_array(array);

} 
