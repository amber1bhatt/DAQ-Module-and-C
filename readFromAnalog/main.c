#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1
#define NUM_DISPLAYS 8
#define SPACE_CHAR 0
#define VOLT 2.98
#define TEMP 298
#define SENSOR 0
#define SWITCH 0

#include <DAQlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void readTemp(void);
void writeNumber(int num);
void writeDigit(int digit, int position);
int convertToKelvin(double voltage);


int main(void)
{
	int setupNum = 0;
	printf("Enter 1 for simulation and 0 for real module:  ");
	scanf("%i", &setupNum);
	int setupDAQ(setupNum);


	if (setupDAQ(setupNum) == TRUE) {
		readTemp();
	}

	else {
		printf("ERROR: Unsuccessful Initialization");
		exit(1);
	}
	system("PAUSE");
	return 0;
}

void readTemp(void) {
	printf("DAQ was successfully initialized");
	while (continueSuperLoop()) {
		
		double voltage = analogRead(SENSOR);

		int temperature = convertToKelvin(voltage);
		printf("%d\n", temperature);

		if (digitalRead(SWITCH)) {
			writeNumber(temperature);
		}
		else {
			writeNumber(voltage * 1000);
		}
		Sleep(10);
		
		
	}

}

void writeNumber(int num) {

	int digit = 0;
	int pos = 0;

	do {
		digit = num % 10;
		num = num / 10;

		//printf("%d\n", digit);
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

int convertToKelvin(double voltage) {
	return (voltage*TEMP) / VOLT;
}