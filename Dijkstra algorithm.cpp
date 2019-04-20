#include <iostream>

/*Re-edition of my Dijkstra Algorithm representation.

IN stream instruction:

FIRST LINE: number of vertex
SECOND LINE: k-value (number of edges)
In the next k-lines  "vertex1<space>vertex2<space>edge length" should be entered in each line
k+1 LINE:  n-value (number of paths)
In the next n-lines  "start vertex<space>final vertex" should be entered in each line 
*/

struct Graph {
	
	int **e;
	int max;

	Graph(int max, int *arr, int n)
	{
		this->max = max;
		//Alocate memmory:
		e = new int *[max+2];
		for (int i = 0; i <= max; i++) {
			e[i] = new int[i+2];
		}

		//Fill the graph with zero edges:
		for (int i = 0; i <= max; i++ ) {
			for (int j = 0; j <= i; j++) {
				e[i][j] = 0; //czy zero?
			}
		}

		//Fill the graph with the edge values:
		for (int i = 0; i < n*3; i+=3) { 
			if(arr[i]>arr[i+1])
				e[arr[i]][arr[i + 1]] = arr[i + 2];
			else
				e[arr[i+1]][arr[i]] = arr[i + 2];
		}
	}

	int dijkstra(int start, int finish);

	~Graph()
	{
		for (int i = 0; i <= max; i++) {
			delete[] e[i];	
		}
		delete[] e;
	}
};

int Graph::dijkstra(int start, int destination) //n - number of verticles
{
	int counter = 0;
	if (start == destination)
		return 0;
	
	int *E = new int[max+2];
	bool *closed = new bool[max+2];
	for (int i = 0; i <= max; i++) {
		E[i] = INT_MAX;
		closed[i] = false;
	}

	E[start] = 0;
	int minV = start; int prev_minV = INT_MAX;
	if (destination>max) {
		delete[] closed;
		delete[] E;
		return 0;
	}
		
	while (!closed[destination]) { 
		closed[minV] = true;

		if (prev_minV == minV) {
			delete[] closed;
			delete[] E;
			return 0;
		}
			
		for (int i = 0; i <= max; i++) {
			if (i <= minV) {
				if (e[minV][i] == 0 || closed[i])
					continue;
				else if (E[minV] + e[minV][i] < E[i])
					E[i] = E[minV] + e[minV][i];
			}
			else {
				if (e[i][minV] == 0 || closed[i])
					continue;
				else if (E[minV] + e[i][minV] < E[i])
					E[i] = E[minV] + e[i][minV];
			}
		}

		prev_minV = minV;

		//find minV:
		if(minV!=destination)
			E[minV] = INT_MAX;

		for (int j = 0; j <= max; j++) { 
			if (E[j] < E[minV] && !closed[j])
				minV = j;
		}
				
	}

	delete[] closed;
	int result = E[destination];
	delete[] E;
	return result;
}

int main()
{
	int vertN; int max = -1; int n; int *arrIN;
	
	std::cin >> vertN; 
	std::cin >> n;
	arrIN = new int[3 * n];

	//put the verticles and edge values to arrIN array:
	for (int i = 0; i < n*3; i++) {
		std::cin >> arrIN[i];
		if (max < arrIN[i] && (i+1)%3)
			max = arrIN[i];
	}
	if (max == -1) {
		std::cin >> n;
		for (int i = 0; i < n; i++)
			std::cout << "nie ma" << '\n';
		
		delete[] arrIN;
		return 0;
	}

	Graph G(max, arrIN, n); 

	int *path; int distance[2];
	
	std::cin >> n;

	path = new int[n];
	
	//Find the shortest path:
	for (int i = 0; i < n; i++) {
		std::cin >> distance[0];
		std::cin >> distance[1];
		path[i] = G.dijkstra(distance[0], distance[1]);
	}

	//View the results:
	for (int i = 0; i < n; i++) {
		if (!path[i])
			std::cout << "nie ma" << '\n';
		else
			std::cout << path[i] << '\n';
	}

	delete[] path;
	delete[] arrIN;
	return 0;
}
