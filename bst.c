/*
	Name:		Kaushik Rawat
	Roll No:	112201015
	Course:		CS2130 DSA Lab
	Semester:	2024 Jan-Apr
	Lab:		Week 8
	Tasks:		1 to 6
	
	Aim: 		Implement a Binary Search Tree (BST)
	Definition:	A BST is a binary tree such that the value (key) at every node is
				more than that of the largest key in it's left subtree (if it exists) and
				less than that of the smallest key it's right subtree (if it exists).
				Check the function is_bst()
	Assume:		All keys to be stored are integers.
				No two keys are the same.
	Inst:		Do not change any function interface
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <time.h>	// To seed random number generator
#include <limits.h>	// For INT_MIN
#include "quick-sort.c"

/* 	The stucture to store the key and pointers for a single node.
	The same structure also can be treated as the definition of a binary tree
	-	A null pointer is a binary tree (empty tree)
	-	A node with a key and two pointers to two binary trees is a binary tree.
*/
typedef struct Tree {
    int key;
    struct Tree* left;
    struct Tree* right;
} Tree;		

Tree* create_node(int key, Tree* left, Tree* right) {
/*
	Inputs:
		1. 	Key for the new node to be inserted
		2.	A pointer to be set as the left child
		3.	A pointer to be set as the right child
	Actions:
		1.	Memory required for a new node is allotted.
		2.	The data and the child pointers of the new node are set from the inputs
	Error Response:
		1.	Prints "Error: Memory allocation for new node failed." to stderr if
			malloc fails.	
		2.	Returns NULL if the new node cannot be created
*/
	Tree* new = (Tree *) malloc(sizeof(Tree));
	if(new == NULL) {
		fprintf(stderr, "Error: Memory allocation for new node failed\n");
		return NULL;
		}
	new->key 	= key;
	new->left 	= left;
	new->right 	= right;

	return new;
}

void free_tree(Tree* t) {
	if (t == NULL)
		return;
	else {
		free_tree(t->left);
		free_tree(t->right);
		free(t);
		return;
	}
}

/* Helper function to return the height of a binary tree */
int height(Tree *tree) {
	if (tree == NULL)
		return 0;
	else {
		int hl 	= height(tree->left);
		int hr 	= height(tree->right);
		int hmax = (hl > hr) ? hl : hr;
		return hmax + 1;
	}
}

/*	Helper function to print one level of a binary tree
*/
void print_level(Tree* t, int t_level, int p_level, int height) {
/*
	Inputs:
		1.	Top level node t
		2.	Height of the top level node (t) in the whole binary tree
		3.	Level of the binary tree to be printed
		4.	Height of the whole binary tree
*/
	if(t_level > p_level) {
		fprintf(stderr, "Error in print_level\n");
		return;
		}
	if(t_level < p_level) {
		if (t != NULL)
			print_level(t->left, t_level+1, p_level, height);
		else
			print_level(NULL, t_level+1, p_level, height);

		if (t != NULL)
			print_level(t->right, t_level+1, p_level, height);
		else
			print_level(NULL, t_level+1, p_level, height);
		return;
	}

	// t_level == p_level
	int padding = 1;	// for alignment
	for (int i = p_level; i < height-1; i++)
		padding = padding * 2 + 1;

	// To prefix some space and a line 
	for (int i = 0; i < (padding+1)/2; i++)
		printf("  ");
	for (int i = (padding+1)/2; i < padding; i++)
		printf("__");

	if (t != NULL)
		printf("%2d", t->key);	
	else
		printf("()");	

	// To suffix a line and some space
	for (int i = (padding+1)/2; i < padding; i++)
		printf("__");
	for (int i = 0; i < (padding+1)/2; i++)
		printf("  ");

	printf("  ");
	return;
}

/*	Helper function to print the binary tree in a tree-like way.
*/
void print_tree(Tree* t) {
	int h = height(t);
	for(int l = 0; l < h; l++) {
		print_level(t, 0, l, h);
		printf("\n");
		}
	return;
}

/* Task 1. Insert
	Implement a function to create a new node with the given key and add it to
	a BST such that the resulting binary tree also satisfies the BST property.
	No change is to be made if the given key is already in the BST.
*/
Tree* insert(int key, Tree* tree) {
/*
	Inputs:
		1. 	Key for the new node to be inserted
		2.	A BST 
	Actions:
		1.	If the key is present in the tree, do nothing.
		2.	Else create a node with the received key and insert it at the correct
			position in tree.
		2.	The pointer to the root of the tree is returned (this will change
			only if the insert happens at the root).
	Error Response:
		1.	Prints "Error: Insertion failed." to stderr
		2.	Returns NULL if the actions fail
*/

	Tree* curr = tree;
	Tree* node = create_node(key, NULL, NULL);
	if (node == NULL){
		fprintf(stderr, "Error: Insertion failed.\n");
		return NULL;
	}

	if (curr == NULL){
		return node;
	}

	while (curr != NULL){
		if (curr->key > key){
			if (curr->left == NULL){
				curr->left = node;
				// printf("left\n");
				return tree;
			}
			curr = curr->left;
		} else if (curr->key < key){
			if (curr->right == NULL){
				curr->right = node;
				// printf("right\n");
				return tree;
			}
			curr = curr->right;
		} else {
			// printf("already exists\n");
			return tree;
		}
	} 
		
	return tree; // You may want to edit this
}

/* Task 2. find_min, find_max
*/
int find_min(Tree* tree){
/*
	Input:  A BST 
	Output: Minimum key in the BST if it is non-empty.
			INT_MAX if the BST is empty.
*/
	while(tree != NULL){
		if (tree->left == NULL){
			return tree->key;
		}
		tree = tree->left;
	}

	return INT_MAX; // You may want to edit this
}

int find_max(Tree* tree){
/*
	Input:  A BST 
	Output: Maximum key in the BST if it is non-empty.
			INT_MAX if the BST is empty.
*/
	while(tree != NULL){
		if (tree->right == NULL){
			return tree->key;
		}
		tree = tree->right;
	}

	return INT_MIN; // You may want to edit this
}

/* Helper function to check if a binary tree is a BST
*/
int is_bst(Tree* t) {
	if (t == NULL)
		return 1;
	if (
		is_bst(t->left) 
		&& is_bst(t->right)
		&& (find_max(t->left) < t->key) 
		&& (find_min(t->right) > t->key)
	)
		return 1;
	return 0;
}

/* Task 3. Search
	Implement a function to search for a key in a BST
*/
Tree* search(int key, Tree* tree) {
/*
	Inputs: A search key and a BST 
	Actions:
		1.	If the key is present in the tree, return the pointer to the node
			with this key
		2.	Else return NULL
*/
	if (tree == NULL){
		return NULL;
	}

	if (tree->key == key){
		return tree;
	} else if (key < tree->key){
		return search(key, tree->left);
	} else if (key > tree->key){
		return search(key, tree->right);
	}

	return NULL; // You may want to edit this
}

/* Task 4. Inoroder, Preorder and Postorder Traversal
Implement three different functions for printing the keys of a
binary tree traversed in the above orders
*/
void inorder(Tree* t) {
/*
	Input: 	A binary tree
	Action: Print the keys as visited in an inorder traversal.
*/
	if (t == NULL) return;
	inorder(t->left);
	printf("%d ", t->key);
	inorder(t->right);
}

void preorder(Tree* t) {
/*
	Input: 	A binary tree
	Action: Print the keys as visited in a preorder traversal.
*/
	// Task 4b Solution
	if (t == NULL) return;
	printf("%d ", t->key);
	preorder(t->left);
	preorder(t->right);
}

void postorder(Tree* t) {
/*
	Input: 	A binary tree
	Action: Print the keys as visited in a postorder traversal.
*/
	// Task 4c Solution
	if (t == NULL) return;
	postorder(t->left);
	postorder(t->right);
	printf("%d ", t->key);
	
}


/* Task 5. Delete
*/
int assign(Tree* a, Tree* b){
	if (b == NULL) return 1;
	a->key = b->key;
	a->left = b->left;
	a->right = b->right;
	return 0;
}

int transplant(Tree* root, Tree* u, Tree* v, Tree* uparent, Tree* vparent){
	int error = 0;
	if (u->key == root->key){
		error += assign(root, v);
	} else if (uparent->left == u){
		uparent->left = v;
	} else if (uparent->right == u){
		uparent->right = v;
	}
	if (v != NULL) error += 2 * assign(vparent, uparent);
	return error;
}

Tree* delete2(int key, Tree* tree) {
/*
	Inputs: A key and a BST
	Actions:
		1.	If the key is present in the tree, delete that from the tree
			and readjust so that the resulting tree is a BST.
		2.	Else return the original tree.
*/
	// Task 5 Solution
	Tree* curr = tree;
	Tree* prev = NULL;
	while (curr != NULL){
		if (curr->key == key){
			break;
		} else if (key > curr->key){
			prev = curr;
			curr = curr->right;
		} else if (key < curr->key){
			prev = curr;
			curr = curr->left;
		}
	}
	if (curr == NULL){
		return NULL;
	}

	if (curr->right == NULL && curr->left == NULL){
		if (prev == NULL){
			tree = NULL;
		} else if (curr = prev->left){
			prev->left = NULL;
		} else if (curr = prev->right){
			prev->right = NULL;
		}
	} else if (curr->left == NULL){
		if (prev == NULL){
			tree = curr->right;
		} else if (curr = prev->left){
			prev->left = curr->right;
		} else if (curr = prev->right){
			prev->right = curr->right;
		}
		if (curr->right != NULL) curr = prev;
	} else if (curr->right == NULL){
		if (prev == NULL){
			tree = curr->left;
		} else if (curr = prev->left){
			prev->left = curr->left;
		} else if (curr = prev->right){
			prev->right = curr->left;
		}
		if (curr->left != NULL) curr = prev;
	} else {
		if (tree->key > curr->right->key){
			if (prev == NULL){
				tree = curr->right;
			} else if (curr = prev->left){
				prev->left = curr->right;
			} else if (curr = prev->right){
				prev->right = curr->right;
			}
			if (curr->right != NULL) curr = prev;
			curr->right->left = curr->left;
		}
		if (tree->key < curr->right->key){
			Tree* left = tree->left;
			tree = tree;
		}
	}
	return tree;
}

// Tree* delete3(int key, Tree* tree) {
// /*
// 	Inputs: A key and a BST
// 	Actions:
// 		1.	If the key is present in the tree, delete that from the tree
// 			and readjust so that the resulting tree is a BST.
// 		2.	Else return the original tree.
// */
// 	// Task 5 Solution
// 	Tree* curr = tree;
// 	Tree* prev = NULL;
// 	while (curr != NULL){
// 		if (curr->key == key){
// 			break;
// 		} else if (key > curr->key){
// 			prev = curr;
// 			curr = curr->right;
// 		} else if (key < curr->key){
// 			prev = curr;
// 			curr = curr->left;
// 		}
// 	}
// 	if (curr == NULL){
// 		return NULL;
// 	}

// 	if (curr->left == NULL && curr->right == NULL){
// 		if (prev && prev->left == curr){
// 			prev->left = NULL;
// 		} else if (prev && prev->right == curr){
// 			prev->right = NULL;
// 		} else if (tree == curr){
// 			tree = NULL;
// 		}
// 		// free_tree(curr);
// 	} else if (curr->left == NULL){
// 		if (prev && prev->left == curr){
// 			prev->left = curr->right;
// 		} else if (prev && prev->right == curr){
// 			prev->right = curr->right;
// 		} else if (tree == curr){
// 			tree = curr->right;
// 		}
// 		// free_tree(curr);
// 	} else if (curr->right == NULL){
// 		if (prev && prev->left == curr){
// 			prev->left = curr->left;
// 		} else if (prev && prev->right == curr){
// 			prev->right = curr->left;
// 		} else if (tree == curr){
// 			tree = curr->left;
// 		}
// 		// free_tree(curr);
// 	} else {
// 		Tree* nc = curr->right;
// 		Tree* np = curr;
// 		while(nc->left != NULL){
// 			np = nc;
// 			nc = nc->left;
// 		}
// 		curr->key = nc->key;
// 		if (np == curr) np->right = delete(key, nc);
// 		else np->left = delete(key, nc);
// 	}
// 	return tree;
// }

Tree* delete(int key, Tree* tree){
    Tree* curr = tree;
	Tree* prev = NULL;
	while (curr != NULL){
		if (curr->key == key){
			break;
		} else if (key > curr->key){
			prev = curr;
			curr = curr->right;
		} else if (key < curr->key){
			prev = curr;
			curr = curr->left;
		}
	}
	if (curr == NULL){
		return NULL;
	}
    if (curr->left == NULL && curr->right == NULL){
        // printf("Branch 1\n");
        if (tree == curr){
            tree = NULL;
        } else if (prev->left == curr){
            prev->left = NULL;
        } else if (prev->right == curr){
            prev->right = NULL;
        }
        free(curr);
    } else if (curr->left == NULL){
        // printf("Branch 2\n");
        if (tree == curr){
			tree = curr->right;
		} else if (prev->left == curr){
            prev->left = curr->right;
        } else if (prev->right == curr){
            prev->right = curr->right;
        }
        free(curr);
    } else if (curr->right == NULL){
        // printf("Branch 3\n");
        if (tree == curr){
			tree = curr->left;
		} else if (prev->left == curr){
            prev->left = curr->left;
        } else if (prev->right == curr){
            prev->right = curr->left;
        }
        free(curr);
    } else {
        // printf("Branch 4\n");
        Tree* nc = curr->right;
        Tree* n_prev = curr;
        while (nc->left != NULL){
            n_prev = nc;
            nc = nc->left;
        }
        int temp = curr->key;
        curr->key = nc->key;
        nc->key = temp;
        if (curr = n_prev) curr->right = delete(key, nc);
        else n_prev->left = delete(key, nc);

        if (prev == NULL){
            tree = curr;
        }
    }

    return tree;
}

/* Task 6. Tree Sort 
*/
int g_index = 0;
void write_inorder(Tree* t, int a[]) {
/*
	Inputs: 
		1.	A tree t
		2.	The starting pointer of an array of size at least that of the tree
	Actions:
		Populates the array following an in-order traversal of the tree t.
		Uses a global variable g_index to keep track of the array location
		to be next used.
*/
	if(t != NULL) {
		write_inorder(t->left, a);
		a[g_index] = t->key;
		g_index++;
		write_inorder(t->right, a);
	}
}

int sort_tree(int a[], int size) {
/*
	Inputs: An array a and its size
	Action: Sorts a using tree sort after removing duplicates
	Returns: The new size of the array (after removing duplicates)
*/
	// Task 6 Solution
	Tree* tree = NULL;
	for(int i = 0; i < size; i++){
		tree = insert(a[i], tree);
	}
	write_inorder(tree, a);
	return g_index;
}


/* 	All the testing for the tasks are included in the main. 
	Uncomment them one by one after you code the corresponding tasks in order.
*/
int main() {
	srand(time(0));		// Seed the random number generator

	Tree *t = NULL;
	int key;
	//Test Task 1. Insert
	printf("\nTesting Task 1. Insert\n");
	printf("========================\n");

	printf("Inserting 16 numbers in the best possible order\n");
	int nice_order[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};

	for (int i = 0; i < 15; i++) {
		key = nice_order[i];
		printf("Inserting %d\n", key);
		t = insert(key, t);
		print_tree(t);
	}

	print_tree(t);
	if(is_bst(t))
		printf("Satisfies BST property\n");
	else
		printf("DOES NOT Satisfies BST property\n");
	free_tree(t);
	
	// Test a tree created by inserting random keys
	printf("\n\nTree emptied. Inserting 8 new random numbers.\n");
	t = NULL;

	for (int i = 0; i < 8; i++) {
		key = 10 + rand() % 90;
		printf("Inserting %d\n", key);
		t = insert(key, t);
		print_tree(t);
	}

	print_tree(t);
	if(is_bst(t))
		printf("Satisfies BST property\n");
	else
		printf("DOES NOT Satisfies BST property\n");

	// Test Task 2. Find Min and Max
	printf("\nTesting Task 2. Find Min and Find Max\n");
	printf("======================================\n");
	Tree* temp = t;
	while(temp != NULL) {
		printf("Min Value in temp = %d\n", find_min(temp));
		printf("Max Value in temp = %d\n", find_max(temp));
		temp = temp->right;
	}

	// Test Task 3. Search
	printf("\nTesting Task 3. Search\n");
	printf("========================\n");

	printf("Keys Found :");
	for(int i = 0; i < 100; i++) {
		if(search(i, t) != NULL)
			printf(" %d", i);
	}
	printf("\n");


	// Test Task 4. Traversals
	printf("\nTesting Task 4. Traversals\n");
	printf("============================\n");

	printf("Inorder: \t");
	inorder(t);
	printf("\n");

	printf("Preorder: \t");
	preorder(t);
	printf("\n");

	printf("Postorder: \t");
	postorder(t);
	printf("\n");

	// Test Task 5. Delete
	printf("\nTesting Task 5. Delete\n");
	printf("========================\n");

	print_tree(t);
	for(int i = 0; i < 3; i++) {
		key = find_min(t);
		printf("Deleting %d\n", key);
		t = delete(key, t);
		print_tree(t);
		if(is_bst(t))
			printf("Satisfies BST property\n");
	}
	for(int i = 0; i < 3; i++) {
		key = t->key;
		printf("Deleting %d\n", key);
		t = delete(key, t);
		print_tree(t);
		if(is_bst(t))
			printf("Satisfies BST property\n");
	}

	free_tree(t);
	
	// Task 6. Timing Tree Sort
	clock_t start, end;
	int size = 1000000;
	printf("\nTiming different sorting algorithms on an array of size %d.\n", size);
	printf("=============================================================\n");

	// Populates four arrays with the same unsorted data 
	int *data1 = (int*) malloc(size * sizeof(int));
	int *data2 = (int*) malloc(size * sizeof(int));
	if (data1 == NULL || data2 == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}
	else {
		printf("Memory for an array of size %d allotted successfully.\n", size);
	}
	for (int i = 0; i < size; i++) {
		data1[i] = rand();
		data2[i] = data1[i];
	}

	// Tree Sort data1
	start = clock();
	int size1 = sort_tree(data1, size);
	end = clock();

	if (is_sorted(data1, size1)) 
		printf("Tree Sort: \t %9d clock cycles, %d unique elements\n", end-start, size1);
	else {
		printf("Tree Sort: \t Failed\n");
		for(int i = 0; i < 100; i++)
			printf("%d\n", data1[i]);
	}

	// Quick Sort data2
	start = clock();
	sort_quick(data2, size);
	end = clock();

	if (is_sorted(data2, size)) 
		printf("Quick Sort: \t %9d clock cycles\n", end-start);
	else
		printf("Quick Sort: \t Failed\n");

/*
*/
	return 0;
}


