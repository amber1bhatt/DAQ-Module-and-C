#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1
#define NUM_DISPLAYS 8
#define SPACE_CHAR 0
#define SWITCH0 0
#define ON 1
#define OFF 0
//#define SWITCH1 1


#include <DAQlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void workFunction(int start, int end);
void writeNumber(int num);
void writeDigit(int digit, int position);


int main(void)
{
	int setupNum = 0;
	int start = 0;
	int end = 0;
	printf("Enter 1 for simulation and 0 for real module:  ");
	scanf("%i", &setupNum);
	printf("Enter a start point:   ");
	scanf("%d", &start);

	printf("Enter an end point:   ");
	scanf("%d", &end);

	int setupDAQ(setupNum);


	if (setupDAQ(setupNum) == TRUE) {
		workFunction(start, end);
	}

	else {
		printf("ERROR: Unsuccessful Initialization");
		exit(1);
	}
	system("PAUSE");
	return 0;
}

void workFunction(int start, int end) {
	printf("DAQ was successfully initialized");
	int num = 1;
	writeNumber(start);


	while (continueSuperLoop()) {

		while (digitalRead(SWITCH0 == ON) && num <= (end - start)) {
			Sleep(10);
			writeNumber(start + num);
			num++;




			if (num < 0) {
				break;
			}
		}
		if (digitalRead(SWITCH0 == OFF)) {
			num = 1;
			writeNumber(start);
		}
	}
}
	void writeNumber(int num) {

		int digit = 0;
		int pos = 0;

		do {
			digit = num % 10;
			num = num / 10;

			printf("%d\n", digit);
			writeDigit(digit, pos);
			pos++;
		} while (num != 0 && pos < NUM_DISPLAYS);

		while (pos < NUM_DISPLAYS) {
			displayWrite(SPACE_CHAR, pos);
			pos++;
		}

	}

	void writeDigit(int digit, int position) {

		static const int digits_data[10] = { 252,96,218,242,102,182,190,224,254,246 };
		if (digit >= 0 && digit <= 9) {
			displayWrite(digits_data[digit], position);
		}
	}