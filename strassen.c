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

void strassen(int** m1, int** m2, int d);

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
	int **m1 = calloc(d, sizeof(int *));
	int **m2 = calloc(d, sizeof(int *));

	// result matrix
	int **res = calloc(d, sizeof(int *));

	for (int i = 0; i < d; i++) {
		m1[i] = calloc(d, sizeof(int));
		m2[i] = calloc(d, sizeof(int));
		res[i] = calloc(d, sizeof(int));
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

	// return pointer to certain size matrix function 

	// strassen function 

	// initial reading in matrices (padded or not)


	strassen(m1, m2, d); 

	for(int i = 0; i < d; i++) {
	        free(m1[i]);
	        free(m2[i]);
	}

	free(m1);
	free(m2);
	free(str);
    
    fclose(fp);
	return 0;

}

// m1, m2 original matrices, result is the result matrix, r, c are the top left corner
void strassen(int** m1, int r1, int c1, int** m2, int r2, int c2, int** result, int r, int c, int d) {

	if (d == 1)
		result[r][c] = m1[r1][c1] * m2[r2][c2];
	// allocate memory for x, y (temporary storage)
	int **x = calloc(d/2, sizeof(int *));
	int **y = calloc(d/2, sizeof(int *));

	for (int i = 0; i < d/2; i++) {
		x[i] = calloc(d, sizeof(int));
		y[i] = calloc(d, sizeof(int));
	}

	// operation 1 and 2 
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			x[i][j] = m1[i][j] - m1[i+d/2][j];
			y[i][j] = m2[i+d/2][j+d/2] - m2[i][j+d/2];
		}
	}

	// op 3: 
	strassen(x, 0, 0, y, 0, 0, result, r + d/2, c, d/2); 

	// op 4, 5: 
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			x[i][j] = m1[r1+i+d/2][c1+j] + m1[r1+i+d/2][c1+j+d/2];
			y[i][j] = m2[r2+i][c2+j+d/2] - m2[r2+i][c2+j];
		}
	}

	// op 6: 
	strassen(x, 0, 0, y, 0, 0, result, r + d/2, c + d/2, d/2);

	// op 7,8: 
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			x[i][j] = x[i][j] - m1[r1+i][c1+j];
			y[i][j] = m2[r2+i+d/2][c2+j+d/2] - y[i][j];
		}
	}

	// op 9
	strassen(x, 0, 0, y, 0, 0, result, r, c+d/2, d/2); 

	// op 10
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			x[i][j] = m1[r1 + i][c1 + j+d/2] - x[i][j];
		}
	}
	
	// op 11
	strassen(x, 0, 0, m2, r2 + d/2, c2 + d/2, result, r, c, d/2); 

	// op 12
	strassen(m1, r1, c1, m2, r2, c2, x, 0, 0, d/2)

	// op 13
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + i][c + d/2 + j] = x[i][j] + result[r + i][c + d/2 + j];
		}
	}

	// op 14
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + d/2 + i][c + i] = result[r + i][c + d/2 + j] 
										+ result[r + d/2 + i][c + j];
		}
	}

	// op 15
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + i][c + d/2 + j] = result[r + i][c + d/2 + j] 
										+ result[r + d/2 + i][c + d/2 + j];
		}
	}

	// op 16
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + d/2 + i][c +  d/2 + i] = result[r + d/2 + i][c + j] +
												+ result[r + d/2 + i][c + d/2 + j];
		}
	}

	// op 17
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + i][c +  d/2 + i] = result[r + i][c +  d/2 + j] 
										+ result[r + i][c + j];
		}
	}

	//op 18
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			y[i][j] = y[i][j] - m2[r2 + d/2 + i][c2 + j];
		}
	}

	// op 19
	strassen(m1, r1 + d/2, c1 + d/2, y, 0, 0, result, r, c, d/2);

	// op 20
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + d/2 + i][c + j] = result[r + d/2 + i][c + j] 
			- result[r + i][c + j];
		}
	}

	// op 21
	strassen(m1, r1, c1 + d/2, m2, r2 + d/2, c2, result, r, c, d/2);

	// op 22
	for (int i = 0; i < d/2; i++) {
		for (int j = 0; j < d/2; j++) {
			result[r + i][c + j] = x[i][j] + result[r + i][c + j];
		}
	}

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