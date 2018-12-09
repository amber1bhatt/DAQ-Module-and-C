#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <DAQlib.h>

#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define MAX 4


void runSimon(void);
void setLEDs(int led0, int led1, int led2, int led3);
void controlLEDs();
void repeatLights();
void checkSimonUser();

int dataSimon[5] = { 0 };
int dataUser[5] = { 0, 1};


int main(void) {
	int setupNum;

	printf("Enter 6 for simulator or 1 for real module:  ");
	scanf("%d", &setupNum);
	int setupDAQ(setupNum);

	if (setupDAQ(setupNum) == TRUE) {
		runSimon();
		
	}
	else {
		printf("ERROR: Cannot initialize module");
		exit(1);
	}
	system("PAUSE");
	return 0;
}

void runSimon(void) {
	repeatLights();
	while (continueSuperLoop()) {

		checkSimonUser(dataSimon, dataUser);
		controlLEDs();
		
	}
}

void setLEDs(int led0, int led1, int led2, int led3) {
	digitalWrite(LED0, led0);
	digitalWrite(LED1, led1);
	digitalWrite(LED2, led2);
	digitalWrite(LED3, led3);
}

void controlLEDs(void) {

		int dataUser[5] = { 0 };
		int gButton = digitalRead(BUTTON0);
		int rButton = digitalRead(BUTTON1);
		int yButton = digitalRead(BUTTON2);
		int bButton = digitalRead(BUTTON3);

		for (int count = 0; count < 5; count++) {

			if (gButton == ON) {
				setLEDs(ON, OFF, OFF, OFF);
				dataUser[count] = 0;
			}
			else if (rButton == ON) {
				setLEDs(OFF, ON, OFF, OFF);
				dataUser[count] = 1;
			}
			else if (yButton == ON) {
				setLEDs(OFF, OFF, ON, OFF);
				dataUser[count] = 2;
			}
			else if (bButton == ON) {
				setLEDs(OFF, OFF, OFF, ON);
				dataUser[count] = 3;
			}
			else {
				setLEDs(OFF, OFF, OFF, OFF);
			}
		}
}

void repeatLights() {

	int dataSimon[5] = { 0 };

	for (int i = 0; i < 5; i++) {

		int channelNum = rand() % MAX;
		dataSimon[i] = channelNum;

		digitalWrite(channelNum, TRUE);
		Sleep(1000);
		digitalWrite(channelNum, FALSE);
		Sleep(1000);
	}

}

void checkSimonUser() {

	for (int i = 0; i < 5; i++) {
		if (dataSimon[i] == dataUser[i]) {
			printf("Correct");
		}
		else {
			printf("Incorrect");
		}
	}

}