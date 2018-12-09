#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define INPUT "input.txt"
#define OUTPUT "outputTest.txt"

int main(void) {
	FILE* outFile;
	FILE* inFile;
	int nextVal;
	int val;
	inFile = fopen(INPUT, "r");
	
	if (inFile == NULL) {
		printf("ERROR");
	}
	else {
		outFile = fopen(OUTPUT, "w");

		if (outFile == NULL) {
			printf("ERROR");
		}
		else {

			while (fscanf(inFile, "%i %i", &nextVal, &val) == 2) {
				if (nextVal > 0 && val > 0) {
					fprintf(outFile, "%i %i\n", nextVal, val);
				}
			}

		}
		fclose(inFile);
		fclose(outFile);
	}

	system("PAUSE");
	return 0;
}