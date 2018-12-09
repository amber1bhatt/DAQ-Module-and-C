#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int count = 0;
	int row;
	int column = 0;

	printf("Give a number");
	scanf("%d", &row);

	row = column;

	for (count = 0; count <= row; count++) {
		printf("*");
	}

	system("PAUSE");
	return 0;

}

