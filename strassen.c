#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 11

int **mat_mul(int **mat1, int **mat2);
void print_mat(int **matrix, int dim);

int main(int argc, char *argv[]) {
	printf("HELLLOOOOO\n");
	if (argc != 4)
		return 1;
	int n = atoi(argv[2]);
	printf("%d\n",n);
	char* filename = argv[3];

	int **m1 = calloc(n, sizeof(int));
	int **m2 = calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		m1[i] = calloc(n, sizeof(int));
		m2[i] = calloc(n, sizeof(int));
	}

	FILE *fp = fopen(filename,"r");

	char *str = malloc(sizeof(char) * 11);
	int counter = 0;
	while (counter < n * n) {
		fgets(str, MAX_LENGTH, fp);
		m1[counter / n][counter % n] = atoi(str);
		// printf("%d %d: ",counter / n,counter % n);
		// printf("%d\n",atoi(str));
		counter++;
	}
	print_mat(m1,n);

	counter = 0;
	while (!feof(fp)) {
		fgets(str, MAX_LENGTH, fp);
		m2[counter / n][counter % n] = atoi(str);
		counter++;
	}
	print_mat(m2,n);

	int **result = mat_mul(m1, m2);
	print_mat(result, n);
	return 0;
}

int **mat_mul(int **mat1, int **mat2) {
	int n = sizeof(mat1[0])/sizeof(mat1[0][0]);

	int **result = calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		result[i] = calloc(n, sizeof(int));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	return result;
}

void print_mat(int **matrix, int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}