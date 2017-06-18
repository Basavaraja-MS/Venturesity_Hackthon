/*
 * Algorighm.c 
 * 
 * Indvidual algorithms for "Shortest path serch" and "Minimum Spannning Tree"
 *
 * **/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define DEBUG_SPS
#define SPS
#define MST

#ifdef SPS
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int vert)
{
// Initialize min value
int min = INT_MAX, min_index;

for (int v = 0; v < vert; v++)
	if (sptSet[v] == false && dist[v] <= min)
		min = dist[v], min_index = v;

return min_index;
}

#ifdef DEBUG_SPS
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
printf("Vertex Distance from Source\n");
for (int i = 0; i < n; i++)
	printf("%d \t\t %d\n", i, dist[i]);
}
#endif


// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int vert, int src, int **graph)
{
	int *dist = (int *)malloc(sizeof (int ) * vert);	 // The output array. dist[i] will hold the shortest
					// distance from src to i
	if (*dist == NULL) {
		printf("Unable to alocate for dist \n");
		return -1;
	}

	bool *sptSet = (int *)malloc(sizeof (bool ) * vert);; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized

	if (*sptSet == NULL) {
                printf("Unable to alocate for sptSet \n");
                return -1;
        }


	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < vert; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < vert-1; count++)
	{
	// Pick the minimum distance vertex from the set of vertices not
	// yet processed. u is always equal to src in first iteration.
	int u = minDistance(dist, sptSet, vert);

	// Mark the picked vertex as processed
	sptSet[u] = true;

	// Update dist value of the adjacent vertices of the picked vertex.
	for (int v = 0; v < vert; v++)

		// Update dist[v] only if is not in sptSet, there is an edge from 
		// u to v, and total weight of path from src to v through u is 
		// smaller than current value of dist[v]
		if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
									&& dist[u]+graph[u][v] < dist[v])
			dist[v] = dist[u] + graph[u][v];
	}
#ifdef DEBUG_SPS
	// print the constructed distance array
	printSolution(dist, vert);
#endif

}
#endif

#ifdef MST
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[], int vert)
{
// Initialize min value
int min = INT_MAX, min_index;

for (int v = 0; v < vert; v++)
	if (mstSet[v] == false && key[v] < min)
		min = key[v], min_index = v;

return min_index;
}

// A utility function to print the constructed MST stored in parent[]
int printMST(int parent[], int n, int **graph)
{
printf("Edge Weight\n");
for (int i = 1; i < n; i++)
	printf("%d - %d %d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int **graph, int vert)
{
	int *parent = (int *) malloc (sizeof (int) * vert); // Array to store constructed MST
	int *key = (int *) malloc (sizeof(int) * vert); // Key values used to pick minimum weight edge in cut
	bool *mstSet = (bool *) malloc (sizeof (bool) * vert); // To represent set of vertices not yet included in MST

	// Initialize all keys as INFINITE
	for (int i = 0; i < vert; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST.
	key[0] = 0;	 // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST 

	// The MST will have V vertices
	for (int count = 0; count < vert-1; count++)
	{
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		int u = minKey(key, mstSet, vert);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (int v = 0; v < vert; v++)

		// graph[u][v] is non zero only for adjacent vertices of m
		// mstSet[v] is false for vertices not yet included in MST
		// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// print the constructed MST
	printMST(parent, vert, graph);
}

#endif

#ifdef DEBUG_SPS
// driver program to test shortest path serch using dijikestra 
int main(void)
{
/* Let us create the example graph discussed above */
	int vert = 9, indx;
	int **graph;
	graph = (int **)malloc (vert * sizeof (int *));
	for (indx = 0; indx < vert; indx++) {
		graph[indx] = (int *) malloc (vert * sizeof (int));
	} 
	//TODO: Initialise the graph values while testing  used BiolerPlate
/*
	int graph[vert][vert] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
					{4, 0, 8, 0, 0, 0, 0, 11, 0},
					{0, 8, 0, 7, 0, 4, 0, 0, 2},
					{0, 0, 7, 0, 9, 14, 0, 0, 0},
					{0, 0, 0, 9, 0, 10, 0, 0, 0},
					{0, 0, 4, 14, 10, 0, 2, 0, 0},
					{0, 0, 0, 0, 0, 2, 0, 1, 6},
					{8, 11, 0, 0, 0, 0, 1, 0, 7},
					{0, 0, 2, 0, 0, 0, 6, 7, 0}
					};
*/

	dijkstra(graph, 0, vert);

	return 0;
}
#endif
