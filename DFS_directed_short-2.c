/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 12 | 04/Apr/2024
	Tasks:		1,2,3
	
	Aim:  To perform the following tasks by running DFS on a directed graph.
		Taks 1: Given the adjacency list and a vertex of a directed graph, list all the vertices reachable from the given vertex.
		Task 2: Given the adjacency list of a directed graph, check whether the graph is strongly connected.
		Task 3: Given the adjacency list of a directed graph, find a topological ordering of it.		
	
*/

#include<stdio.h>
#include<stdlib.h>

/*Node data structure for the DFS tree/ forest.*/
typedef struct list_node {
	int node_index;                             // Index of the node as given by the adjacency matrix
	struct list_node* ptr_sibling;                   // Pointer to its next sibling in the adjacency list
	
} list_node;

/* Create a new adjacency list node and returns a pointer to it.
Input: Index of the node.
Output: Pointer to the newly created adjacency list node or NULL if the node creation fails.*/

list_node* create_node (int node_index){
	list_node* ptr_new_node = (list_node*) malloc (sizeof (list_node));
	if (ptr_new_node != NULL){
		ptr_new_node-> node_index = node_index;
		ptr_new_node->ptr_sibling = NULL;
	}
	return ptr_new_node;
}

/* Print List: Helper function to print the elements of a given list. */
int print_list (list_node* ptr_list_node){

	while (ptr_list_node != NULL){
		printf ("%d ", ptr_list_node-> node_index);
		ptr_list_node = ptr_list_node -> ptr_sibling;
	}
	
	return 0;
}

/* create_adjacency_list: Helper function to create adjacency list of a digraph from its adjacency matrix.*/
								

list_node** create_adjacency_list (char* file_name, int * order){


	FILE * graph_data;
	int i, j, temp;
	char* row;

	graph_data = fopen ( file_name,"r"); // Open the file in read-only mode
			
	list_node* ptr_new;
	list_node** adjacency_list;

	printf("Opening file.\n");

	if (graph_data != NULL){

		fscanf(graph_data,"%d", &temp);
		(*order) = temp;

		adjacency_list = (list_node**)malloc(temp* sizeof(list_node*));
		row = malloc((temp+2) * sizeof(char));
		fgets(row,(temp+2), graph_data);
		
		for (i = 0; i < temp; i++){
			fgets(row,(temp+2), graph_data);
			
			for (j=0; j < temp; j++){
				if((row[j] - '0') == 1) {
					ptr_new = create_node(j);
					ptr_new -> ptr_sibling = adjacency_list[i];
					adjacency_list[i] = ptr_new;
				}

				
			} 
		} 

		fclose(graph_data);
	}
	
	return adjacency_list;
}









/****************************************************************************************************************************/
/*Task 1: Goal of this task is to return a list of vertices reachable from a given vertex (the set includes the vertex itself). 
It is divided into the following two subtasks.
*/

/* Task 1(a): dfs_explore. Run a DFS from a given node and return a list of all the nodes reachable from it. 
				Input: i) order: Order of the graph.
				       ii) adjacency_list: Pointer to the adjacency list of the graph.
				       iii) node_index: Index of the node from which DFS will start.
				       iv) visited: Pointer to an array (indexed by node indices) indicating the list of nodes already visited by the DFS. A node is visited when the DFS reaches the 						   node for the first time.  visited[i] = 1 if the node i has been visited, otherwise visited[i] = 0.
				        
				 Output: i) reachable_set: A list of nodes reachable by the DFS from the starting node. Assume/ note that a node is reachable from itself. 
				 	   visited array should be updated accordingly.
 */
list_node* dfs_explore(int order, list_node** adjacency_list, int node_index, int * visited){
	
	if (visited[node_index]) return NULL;
	
	list_node* reachable_set = NULL;
	visited[node_index] = 1;
	reachable_set = create_node(node_index);

	list_node* children = adjacency_list[node_index];
	list_node* rc_curr = reachable_set;
	while (children !=  NULL){
		rc_curr->ptr_sibling = dfs_explore(order, adjacency_list, children->node_index, visited);
		children = children->ptr_sibling;
		while (rc_curr->ptr_sibling != NULL)
			rc_curr = rc_curr->ptr_sibling;
	}
	
	return reachable_set;
}

/* Task 1(b): list_reachable. Return a list of nodes reachable from a given node.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
				iii) node_index: Index of the given node.
			Output:
				i) reachable_set: A list of nodes reachable from the given node. Assume/note that a node is reachable from itself.
			       	
*/
list_node* list_reachable(int order, list_node** adjacency_list, int node_index ){

	int* visited = (int*) calloc(order, sizeof(int));
	list_node* reachable_set = dfs_explore(order, adjacency_list, node_index, visited);
	// printf("reached here\n");
	return reachable_set;
}

/********************************************************************************************************************************
Task 2: Goal of this task is to check whether a given directed graph is strongly connected. It is divided into the following 
two subtasks.*/

/* Task 2(a): get_reverse_adjacency_list. Given the adjacency list of a digraph return the adjacency list of its reverse.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: i) reverse_adjacency_list: Adjacency list of the reverse graph.
*/


list_node** get_reverse_adjacency_list (int order, list_node** adjacency_list){
	
	list_node** reverse_adjacency_list = (list_node**)calloc(order, sizeof(list_node*));
	// list_node** tail_list = (list_node**)malloc(order * sizeof(list_node*));

	for(int i = 0; i < order; i++){
		list_node* children = adjacency_list[i];
		while(children != NULL){
			list_node* new_node = create_node(i);
			if (reverse_adjacency_list[children->node_index] != NULL){
				new_node->ptr_sibling = reverse_adjacency_list[children->node_index];
			}
			reverse_adjacency_list[children->node_index] = new_node;
			children = children->ptr_sibling;
		}
	}

	return reverse_adjacency_list;
}
/* Task 2(b): is_strongly_connected. Checks whether the input directed graph (given by the adjacency list) is strongly connected.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: 1 if the graph is strongly connected; 0 otherwise.
*/
 
int is_strongly_connected(int order, list_node** adjacency_list ){
	list_node* explored = list_reachable(order, adjacency_list, 0);
	int count = 0;
	while (explored != NULL) {
		explored = explored->ptr_sibling;
		count++;
	}
	// printf("count = %d\n", count);
	if (count != order) return 0;

	list_node** reverse_list = get_reverse_adjacency_list(order, adjacency_list);
	// for(int i = 0; i < order; i++) {
	// 	printf("%d: ", i);
	// 	print_list(adjacency_list[i]);
	// 	printf("\n");	
	// }
	// for(int i = 0; i < order; i++) {
	// 	printf("%d: ", i);
	// 	print_list(reverse_list[i]);
	// 	printf("\n");	
	// }
	list_node* r_explored = list_reachable(order, reverse_list, 0);
	int r_count = 0;
	while (r_explored != NULL) {
		r_explored = r_explored->ptr_sibling;
		r_count++;
	}
	// printf("r_count = %d\n", r_count);
	if (r_count != order) return 0;

	return 1;

	
}


/**********************************************************************************************************************************************************/

/* Task 3: Goal of this task is to generate a topological ordering of a given digraph or indicate that it is not possible (i.e., the digraph is cyclic). The task is
divided into the following two subtasks*/

/* Task 3(a): dfs_explore_with_time. Run the DFS. Also, maintain (i) an array indicating already visited nodes  (iii) an array of finish times of the already visited nodes (iv) an array where the already visited nodes are arranged in the reverse order of their visit (finish) times (ii) a clock counter.  

				Input 
				       i) order: Order of the graph.
				      ii) adjacency_list: Pointer to the adjacency list of the graph.
				      iii) node_index: Index of the node from which DFS will start.
				       iv) visited: Pointer to an array (indexed by node indices) indicating the list of nodes already visited by the DFS. A node is visited when the DFS reaches the 						   node for the first time.  visited[i] = 1 if the node i has been visited, otherwise visited[i] = 0.
				       v) clk: Pointer to a clock counter. 
				       vi) finished: Pointer to an array (indexed by node indices) indicating whether DFS has finished at/ returned from the corresponding node. finished[i] = 1, if 						    the DFS has returned from node i, otherwise finish[i] = 0. 
				       vii) topo_order: Pointer to an array containing node indices arranged in the reverse DFS finish time order. If the DFS has finished at node i before node j then 						    in the topo_order array node j appears before node i.
				       
				Output  0 if the subgraphs induced by the unvisited nodes of the DFS tree rooted at the input node can be topologically ordered, otherwise -1 (indicating that the 						induced subgraph is cyclic). Also update visited, clk, finish_time, topo_order.
				      */

int dfs_explore_with_time(int order, list_node** adjacency_list, int node_index, int * visited, int* clk,  int* finished,  int * topo_order, int * index){

	printf("ni = %d, v = %d, f = %d\n", node_index, visited[node_index], finished[node_index]);
	if (visited[node_index] && finished[node_index] == -1) return -1;
	if (visited[node_index]) return 0;
	
	list_node* reachable_set = NULL;
	visited[node_index] = 1;
	reachable_set = create_node(node_index);
	*index += 1;

	list_node* children = adjacency_list[node_index];
	list_node* rc_curr = reachable_set;
	finished[node_index] = -1;
	while (children !=  NULL){
		if (dfs_explore_with_time(order, adjacency_list, children->node_index, visited, clk, finished, topo_order, index) == -1)  return -1;
		children = children->ptr_sibling;
		// while (rc_curr->ptr_sibling != NULL)/
	}
	topo_order[*clk] = node_index;
	finished[node_index] = *clk;
	*clk += 1;
	printf("THEclk = %d\n", *clk);
	return 0;
}

/* Task 3(b): topo_order. Given a digraph return a topological ordering of it or indicate that it is not possible.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: A pointer to a sequence of nodes representing a topological order: If there is an u->v edge
				 then u preceedes v in the order. Return NULL if there is no such order (i.e., the digraph is cyclic).*/
				 
int* topo_order (int order, list_node** adjacency_list){
	
	int* visited = calloc(order, sizeof(int));
	int* finished = calloc(order, sizeof(int));
	int* topo_order = calloc(order, sizeof(int));
	int c = 0;
	for(int i = 0; i < order; i++){
		int clk = 0;
		int* to = calloc(order, sizeof(int));
		if (visited[i]) continue;
		int awd = 0;
		int status = dfs_explore_with_time(order, adjacency_list, i, visited, &clk, finished, to, &awd);
		c += clk;
		printf("%d AA: ", c);
		for (int i = 0; i < clk; i++){
			printf("%d ", to[i]);
		}
		printf("\n");
		printf("clk = %d\n", clk);
		for (int i = 0; i < clk; i++){
			topo_order[order - c + i] = to[clk - i - 1];
		}
		
		if (status == -1) return NULL;
	}
	
	return topo_order;
}


int main(){

	list_node** adjacency_list;
	list_node* list;
	list_node** scc;
	int order, i, j;
	int * ptr_topo_order;

	char graph1[] = "dfs_dir_1";
	char graph2[] = "dfs_dir_2";
	char graph3[] = "dfs_dir_3";
	

	



/* Task 1*/
	printf("********************** Task 1 ********************\n");
	
	// adjacency_list = create_adjacency_list(graph1,&order);
	// list = list_reachable(order, adjacency_list, 4);
	// // printf("AdjL 1: \n");
	// // for(int i = 0; i < order; i++) {
	// // 	printf("%d: ", i);
	// // 	print_list(adjacency_list[i]);
	// // 	printf("\n");	
	// // }
	// print_list(list);
	
	// adjacency_list = create_adjacency_list(graph2,&order);
	// // printf("AdjL 2: \n");
	// // for(int i = 0; i < order; i++) {
	// // 	printf("%d: ", i);
	// // 	print_list(adjacency_list[i]);
	// // 	printf("\n");	
	// // }
	// list = list_reachable(order, adjacency_list, 0);
	// print_list(list);
	
	// adjacency_list = create_adjacency_list(graph3,&order);
	// // printf("AdjL 3: \n");
	// // for(int i = 0; i < order; i++) {
	// // 	printf("%d: ", i);
	// // 	print_list(adjacency_list[i]);
	// // 	printf("\n");	
	// // }
	// list = list_reachable(order, adjacency_list, 0);
	// print_list(list);


/*  Task 2*/
	printf("********************** Task 2 ********************\n");
	
	// adjacency_list = create_adjacency_list(graph1,&order);
	// if (is_strongly_connected(order, adjacency_list) == 1){
	// 	printf ("Strongly connected \n");
	// } else {
	// 	printf ("Not strongly connected\n");
	// }
	
	// adjacency_list = create_adjacency_list(graph2,&order);
	// if (is_strongly_connected(order, adjacency_list) == 1){
	// 	printf ("Strongly connected \n");
	// } else {
	// 	printf ("Not strongly connected\n");
	// }
	
	// adjacency_list = create_adjacency_list(graph3,&order);
	// if (is_strongly_connected(order, adjacency_list) == 1){
	// 	printf ("Strongly connected \n");
	// } else {
	// 	printf ("Not strongly connected\n");
	// }




/* Task 3*/

	printf("********************** Task 3 ********************\n");
	// adjacency_list = create_adjacency_list(graph1,&order);
	
	// ptr_topo_order = topo_order(order, adjacency_list);
	// if (ptr_topo_order != NULL){
	// 	printf("Topological order \n");
	// 	for (i =0; i < order; i++){
	// 		printf("%d ", ptr_topo_order[i]);
	// 	}
	// }else{
	// 	printf("Digraph is cyclic\n");
	// }
	
	
	adjacency_list = create_adjacency_list(graph2,&order);
	
	ptr_topo_order = topo_order(order, adjacency_list);
	if (ptr_topo_order != NULL){
		printf("Topological order \n");
		for (i =0; i < order; i++){
			printf("%d ", ptr_topo_order[i]);
		}
	}else{
		printf("Digraph is cyclic\n");
	}
	
	
	// adjacency_list = create_adjacency_list(graph3,&order);
	
	// ptr_topo_order = topo_order(order, adjacency_list);
	// if (ptr_topo_order != NULL){
	// 	printf("Topological order \n");
	// 	for (i =0; i < order; i++){
	// 		printf("%d ", ptr_topo_order[i]);
	// 	}
	// }else{
	// 	printf("Digraph is cyclic\n");
	// }

	return 0;
}
