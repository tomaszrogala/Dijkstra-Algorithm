#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Vertex 
{
	int data;
	bool open;

	Vertex(){
		open = true;
	}
};

struct Graph
{
	Vertex *Dijkstr;
	int **M;
		
	void search_path(int vert_numb, int begin_index, int end_index);

	Graph(int vert_numb) {
		Dijkstr = new Vertex[vert_numb];

		//TWO-DIMENSIONAL TRIANGULAR ARRAY:
		M = new int*[vert_numb]; 

		for (int i = 0; i < vert_numb; i++) {
			M[i] = new int[i+1];
		}

		for (int i = 0; i < vert_numb; i++) {
			for (int j = 0; j <= i; j++) {
				if (i == j) {
					M[i][j] = 0;
				}
				else {
					M[i][j] = INT_MAX;
				}
			}
		}
	}
};

void Graph::search_path(int vert_numb, int begin_index, int end_index)
{
	bool flag = false;
	int min = INT_MAX;

	for (int i = 0; i < vert_numb; i++) {
		Dijkstr[i].data = INT_MAX;
		Dijkstr[i].open = true;
	}

	while (end_index != begin_index) {
		for (int i = 0; i < vert_numb; i++) {
			if (Dijkstr[i].open == true )
			{
				if (begin_index > i) {
					if (M[begin_index][i] != INT_MAX) {
						if (Dijkstr[begin_index].data == INT_MAX) {
							Dijkstr[i].data = M[begin_index][i];
						}
						else {
							if (Dijkstr[i].data > M[begin_index][i] + Dijkstr[begin_index].data) {
								Dijkstr[i].data = M[begin_index][i] + Dijkstr[begin_index].data;
							}
						}
					}
				}
				else {
					if (M[i][begin_index] != INT_MAX) {
						if (Dijkstr[begin_index].data == INT_MAX) {
							Dijkstr[i].data = M[i][begin_index];
						}
						else {
							if (Dijkstr[i].data > M[i][begin_index] + Dijkstr[begin_index].data) {
								Dijkstr[i].data = M[i][begin_index] + Dijkstr[begin_index].data;
							}
						}
					}
				}
			}
		}
		
		Dijkstr[begin_index].open = false;
		//SEARCHING FOR THE SHORTEST PATH
		for (int i = 0; i < vert_numb; i++) {
			if (Dijkstr[i].data < min && Dijkstr[i].open == true) {
				min = Dijkstr[i].data;
				begin_index = i;
			}
		}
		if (min == INT_MAX) {
			std::cout << "no path" << '\n';
			flag = true;
			break;
		}
		min = INT_MAX;
	}
	if(flag == false)
		std::cout << Dijkstr[end_index].data << '\n';
}


//INPUT FUNCTIONS:
int exp(int base, int index) {
	int x = 1;

	for (int i = 0; i < index; i++) {
		x *= base;
	}

	return x;
}

int input_int(char *&pointer) {
	int x = 0;
	int k = 0;

	while (*pointer != ' ' && *pointer != '\n') {
		k++;
		pointer++;
	}
	for (int i = 0; i < k; i++) {
		pointer--;
		x = x + ((*pointer - 48) * exp(10, i));
	}
	pointer = pointer + k;

	return x;
}

//COUNTING FUNCTION:
int count_array(int array[], int n, int count) {
	if (array[n] != -858993460) {
		return count_array(array, n + 1, count + 1);
	}

	return count;
}

bool correct(int tab_out[], int vert_numb, bool flag) {
	for (int i = 0; i < count_array(tab_out, 0, 0); i++) {
		if (flag == false) {
			if ((tab_out[i] >= vert_numb || tab_out[i] < 0) && (i + 1) % 3 != 0) {
				return false;
			}
		}
		else {
			if (tab_out[i] >= vert_numb || tab_out[i] < 0) {
				return false;
			}
		}	
	}

	return true;
}

void in(char tab_in[],int line_numb, char *&pointer, int tab_out[], FILE *file, int vert_numb, bool flag)
{
	int k;
	do {
		k = 0;
		for (int i = 0; i < line_numb; i++) {
			fgets(tab_in, 100, file);
			pointer = &tab_in[0];

			for (int j = 0; *pointer != '\0'; j++) {
				tab_out[k] = input_int(pointer);
				pointer++;
				k++;
			}
		}
		if (correct(tab_out, vert_numb, flag) == false) {
			std::cout << "WORKS ONLY FOR FIGURES <0, VERT_NUMB)\nPlease enter the connections again:\n";
		}
	} while (correct(tab_out, vert_numb, flag) == false);
}

//MAIN:
int main()
//WORKS ONLY FOR FIGURES <0, VERT_NUMB)
{
	int vert_numb; int line_numb; char rout[100]; char vert[100]; int rout_out[100]; int vert_out[100]; char *pointer; bool flag = false;
	
	std::cout << "Please enter the number of vertex:" << '\n';
	std::cin >> vert_numb;
	std::cin.ignore();
	Graph g(vert_numb);

	std::cout << "Please enter the number of connections:" << '\n';
	std::cin >> line_numb;
	std::cin.ignore();

	//INPUT DATA:
	std::cout << "Enter the connections:" << '\n';
	in(vert, line_numb, pointer, vert_out, stdin, vert_numb, flag);

	//GRAPH CREATING:
	for (int i = 0; i < line_numb*3; i = i+3) {
		if (vert_out[i] > vert_out[i + 1]) {
			g.M[vert_out[i]][vert_out[i+1]] = vert_out[i + 2];
		}
		else {		
			g.M[vert_out[i+1]][vert_out[i]] = vert_out[i + 2];
		}
	}

	//ENTER THE START VERTEX AND THE FINAL VERTEX:
	std::cout << "Please enter the number of paths:" << '\n';
	std::cin >> line_numb;
	std::cin.ignore();
	std::cout << "Please enter the start vertex and the final vertex:" << '\n';

	flag = true;
	in(rout, line_numb, pointer, rout_out, stdin, vert_numb, flag);

	std::cout << "SOLUTION:\n";
	//Dijkstra:
	for (int i = 0; i < line_numb*2; i=i+2) {
		g.search_path(vert_numb, rout_out[i+0], rout_out[i+1]);
	}

	return 0;
}
