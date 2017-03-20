#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LENGTH 11 
// function to find the next power of two
int next_power(int v); 

// function for direct matrix multiplication 
int **mat_mul(int **mat1, int **mat2);

// function to print matrices
void print_mat(int **matrix, int dim);

// function to test if power of two
bool is_power(int x);

int main(int argc, char *argv[]) {

	// four arguments 
	if (argc != 4)
		return 1;

	// given dimension
	int n = atoi(argv[2]);
	printf("Dimension: %d\n",n);

	// dimension to be used 
	int d; 
	if (is_power(n)) 
		d = n; 
	else d = next_power(n); 

	// inputfile 
	char* filename = argv[3];

	// allocate memory (nearest power of 2)
	int **m1 = calloc(d+1, sizeof(int));
	int **m2 = calloc(d+1, sizeof(int));

	for (int i = 0; i < d+1; i++) {
		m1[i] = calloc(d+1, sizeof(int));
		m2[i] = calloc(d+1, sizeof(int));
	}

	// read matrices into allocated memory
	FILE *fp = fopen(filename,"r");

	char *str = malloc(sizeof(char) * 12);


	for (int i= 0; i < d; i++) {
		if (i < n) {
			for (int j = 0; j < d; j++) {
				if (j < n) {
					fgets(str, MAX_LENGTH, fp); 
					m1[i][j] = atoi(str); 
				}
				else m1[i][j] = 0; 	
			}
		}
		else {
			for (int j =0; j < d; j++) {
				m1[i][j] =0;
			}
		}
	}
	printf("Matrix 1: \n");
	print_mat(m1,d);

	for (int i= 0; i < d; i++) {
		if (i < n) {
			for (int j = 0; j < d; j++) {
				if (j < n) {
					fgets(str, MAX_LENGTH, fp); 
					m2[i][j] = atoi(str); 
				}
				else {
					m2[i][j] = 0;
				}
			}
		}
		else {
			for (int j =0; j < d; j++) {
				m2[i][j]=0;
			}
		}
	}
	printf("Matrix 2: \n");
	print_mat(m2,d);
	
	for(int i = 0; i < d+1; i++) {
	        free(m1[i]);
	        free(m2[i]);
	}
	free(m1);
	free(m2);
	free(str);
    
    fclose(fp);
	return 0;

}

bool is_power(int x) {
	while (((x % 2) == 0) && x >1) 
		x /= 2; 
	return (x == 1); 
}

int next_power(int v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
	printf("Next power of two: %d \n", v);
}

void print_mat(int **matrix, int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}