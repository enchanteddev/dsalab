/*
	Course:		CS2024 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab No:		1
	Aim: 		Simple data analysis on a list of non-zero integers. 
	Instructions:
		1.	Read a list of numbers from the terminal and store it in an array.
		2.	You can also read the list by redirecting a file data.txt to the input 
		3.	Complete a set of data analytic tasks on these numbers.
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#define N 100		// The maximum amount of data the program will handle



int main() {
	int a[N];
	int i, len, temp;

	for(i = 0; i < N; i++)
	{
		scanf("%d", &temp);
		if(temp == 0){
			len = i;
			break;
		}
		else {
			a[i] = temp;
		}
	}

	/* Task 1. Modify the loop below to print the numbers in reverse order
	*/
	for(i = len - 1; i >= 0; i--)
		printf("%d\n", a[i]);

	/* Task 2. Find some cumulative statistics of the data
		a) 	Average 
		b)	Standard Deviation
		c)	Minimum value
		d) 	Maximum value
	*/

	int total_sum = 0;
	int max = -__INT_MAX__;
	int min = __INT_MAX__;

	for (int i = 0; i < len; i++) {
		total_sum += a[i];
		if (a[i] > max) {
			max = a[i];
		}

		if (a[i] < min) {
			min = a[i];
		}
	}

	float avg = (float) total_sum / (float) len;

	int sum_diff_from_avg_squared = 0;
	for (int i = 0; i < len; i++) {
		sum_diff_from_avg_squared += (avg - a[i]) * (avg - a[i]);
	}

	float standard_deviation = sqrt((float) sum_diff_from_avg_squared / (float) len);

	printf("Avg: %f\n", avg);	
	printf("Max: %d\n", max);
	printf("Min: %d\n", min);
	printf("Standard Deviation: %f\n", standard_deviation);

	/* Task 3. Generate a histogram of the data in the following form
		01 - 10 : ####
		11 - 20 : ########
		...
		91 -100 : ##
		
		Here the number of #'s after i-j denote the number of numbers in the
		list which are between i and j (i and j included)
	*/

	int hist[N / 10] = {};
	for (int i = 0; i < len; i++) {
		if (a[i] < 1) continue;
		hist[(a[i] - 1) / 10]++;
	}

	for (int i = 0; i < N / 10; i++)
	{
		printf("%d - %d : ", i * 10 + 1, i * 10 + 10);
		for (int j = 0; j < hist[i]; j++) printf("#");
		printf("\n");
	}
	
	

	/* Task 4. Search type tasks
		a) 	Find the number of times the maximum value repeats in the list
		b)	Find the value which repeats the maximum number of times in the list
			(this is called the mode of the list)
	*/

	int fd[max];
	memset(fd, 0, max * sizeof(int));
	for (int i = 0; i < len; i++) {
		fd[a[i] - 1]++;
	}

	printf("The maximum number (%d) is present %d time(s) in the given array.\n", max, fd[max - 1]);
	
	int mode = a[0];
	int mode_freq = fd[a[0] - 1];
	for (int i = 1; i < len; i++) {
		if (fd[a[i] - 1] > mode_freq) {
			mode = a[i];
		    mode_freq = fd[a[i] - 1];
		}
	}
	
	printf("The mode (%d) is present %d time(s) in the given array.\n", mode, mode_freq);

	/* Task 5. Sorting
		a) Sort the array in the non-decreasing order 
		b) Print the array in sorted order
	*/

	printf("Sorted Array:\n");

	int sorted = 0;
	while (!sorted) {
		int flag = 1;
		for (int i = 0; i < len - 1; i++) {
			if (a[i + 1] < a[i]) {
				int temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				flag = 0;
			}
		}
		if (flag){
			break;
		}
	}

	for (int i = 0; i < len; i++) printf("%d\n", a[i]);
	

	/* Task 6.  Uniqueness
		a) Create a new array which contains all elements of the first 
				but without any repetition.
		b) Print this array
	*/

	printf("Unique Array:\n");

	int unique[len];
	int u_len = 0;
	for (int i = 0; i < len; i++) {
		int exist = 0;
		for (int j = 0; j < u_len; j++){
			if (a[i] == unique[j]){
				exist = 1;
				break;
			};
		}
		if (!exist){
			unique[u_len] = a[i];
			u_len++;
		}
	}
	
	for (int i = 0; i < u_len; i++) printf("%d\n", unique[i]);


	return 0;
}
