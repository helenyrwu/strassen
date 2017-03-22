#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char* filename = "test_mat.txt";
	FILE *fp = fopen(filename,"w+");
	int d = atoi(argv[1]);

	// identity matrix 1
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			if (i == j)
				fprintf(fp, "1\n");
			else
				fprintf(fp, "0\n");
		}
	}

	// identity matrix 2
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			if (i == j)
				fprintf(fp, "1\n");
			else
				fprintf(fp, "0\n");
		}
	}

	fclose(fp);
	return 0;
}