#include <stdio.h>
#include <stdlib.h>

struct fileData {
	int node;
	int adj_node;
	int cost;
};


void init_graph(int **graph, int node_count){
	int i, j;

	for ( i = 0; i < node_count; i++)
		for (j = 0; j < node_count; j++)
			graph[i][j] = 0;
}

int file_io_main(void) {

	FILE *fp;
	struct fileData *fdata;
	char temp[100];
	int node_count, edges_count;

//please bear with these variables, There are used while file phrasing only 
	int c;
	int i = 0;
	int indx = 0; // Index for struct value
	int count = 0; //Used to differ node and adj node


	fp = fopen("input.txt", "w+");
	if (fp == NULL) {
		printf("Problem in file opening\n");
		return -1;
	}
	
	//Very stict order of input file format 
	fscanf(fp,"%[^\n]", temp);
	node_count = atoi(temp);
	fscanf(fp,"%[^\n]", temp);
	edges_count = atoi(temp);

	fdata = (struct fileData *) malloc (sizeof (struct fileData ) * edges_count);
	while (c = fgetc(fp) && c != EOF) {
		if (c == ' ' ) {
			temp[i] = '\0'; i = 0;
			if (count % 2 )
				fdata[indx].node = atoi(temp);
			else
				fdata[indx].adj_node = atoi (temp);
			count++;
		}else if (c == '\n'){
			temp[i] = '\0'; i = 0;
			fdata[indx].cost = atoi(temp);
		}else{
			temp[i++] = c;
		}
	}


	int **graph;
	graph = (int **)malloc(sizeof(int *) * node_count);
	for (i =0; i < node_count; i++){
		graph[i] = (int *)malloc (sizeof (int) * node_count);
	}

	init_graph(graph, node_count);

	for (i = 0;  i < edges_count; i++){
		graph[fdata[i].node][fdata[i].adj_node] = fdata[i].cost;
	}


}


int main (){


} 
