#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <DAQlib.h>
#include <time.h>

//Basic initializers
#define SETUPNUM 6
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

//Green, Red, Yellow, and Blue LEDs
#define gLED0 0
#define rLED1 1
#define yLED2 2
#define bLED3 3
#define numLEDS 4

//Buttons that correspond to each LED
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3

//Delay Constants
#define onDelay 500
#define offDelay 300
#define flashingDelay 250
#define roundDelay 2000
#define numFlashes 4

//Number of rounds
#define maxRounds 5

//function prototypes
void runSimon(void);
int rngLED(void);
void gameOrder(int simonInput[]);
void flashOrder(int size, int simonInput[]);
void readInput(int userInput[], int size);
int checkInput(int size, int simonInput[], int userInput[]);
void flashStatus(int status);
void offLEDs(void);
void setLEDs(int LED0, int LED1, int LED2, int LED3);

int main(void) {

	//seed random number generator
	srand((unsigned)time(NULL));

	//initialize DAQ simulator
	if (setupDAQ(SETUPNUM) == TRUE) {
		runSimon();
	}
	else {
		printf("Error: Cannot initialize simulator");
	}
	system("PAUSE");
	return 0;
}

//Main function of Simon program
//Increments the number of LEDs that are flashed until the user loses (gets the simonInput wrong)
//or wins (repeats the simonInput till maxRounds)
//Finally, flashes either green (win) or red (lose) 4 times 
void runSimon(void) {
	int len;

	int isCorrect = TRUE;
	int simonInput[maxRounds] = { 0 };
	int input[maxRounds] = { 0 };

	while (continueSuperLoop()) {
		gameOrder(simonInput);
		isCorrect = TRUE;


		for (len = 1; len <= maxRounds && isCorrect; len++) {
			Sleep(roundDelay);
			if (!(continueSuperLoop())) {
				exit(0);
			}
			flashOrder(len, simonInput);
			readInput(input, len);
			isCorrect = checkInput(len, simonInput, input);
		}

		Sleep(flashingDelay);
		flashStatus(isCorrect);

	}


}

//Randomly chooses the LED that will be later flashed (creates the values to be placed into the simonInput sequence)
int rngLED(void) {
	return ((rand() % numLEDS));
}

//Creates a sequence for the game (new each game)
void gameOrder(int simonInput[]) {

	for (int i = 0; i < maxRounds; i++) {
		simonInput[i] = rngLED();
	}
}

//Flashes the LEDs based on simonInput
void flashOrder(int size, int simonInput[]) {

	offLEDs();

	for (int i = 0; i < size; i++) {
		Sleep(onDelay);
		digitalWrite(simonInput[i], ON);
		Sleep(offDelay);
		digitalWrite(simonInput[i], OFF);
	}
}

//Constantly checks to see if the user has pressed the number of buttons expected (i.e the same as the game flashes)
//Checks for button activation and displays the LEDs that correspond to the buttons pressed
//It then waits until all buttons turn off, as there is a sleep time between presses
//Finally, it stores the user inputted data into an array

void readInput(int userInput[], int size) {

	int B0Off = OFF, B1Off = OFF, B2Off = OFF, B3Off = OFF;
	int B0ON = ON, B1ON = ON, B2ON = ON, B3ON = ON;

	for (int i = 0; i < size; i++) {
		B0Off = B1Off = B2Off = B3Off = OFF;
		B0ON = B1ON = B2ON = B3ON = ON;

		do {
			B0Off = digitalRead(BUTTON0);

			B1Off = digitalRead(BUTTON1);

			B2Off = digitalRead(BUTTON2);

			B3Off = digitalRead(BUTTON3);

			if (continueSuperLoop() == FALSE) {
				exit(0);
			}
		} while (B0Off == OFF && B1Off == OFF && B2Off == OFF && B3Off == OFF);

		setLEDs(B0Off, B1Off, B2Off, B3Off);

		while (B0ON == ON || B1ON == ON || B2ON == ON || B3ON == ON) {
			B0ON = digitalRead(BUTTON0);
			B1ON = digitalRead(BUTTON1);
			B2ON = digitalRead(BUTTON2);
			B3ON = digitalRead(BUTTON3);

		}

		offLEDs();

		if (B0Off) {
			userInput[i] = BUTTON0;
		}
		else if (B1Off) {
			userInput[i] = BUTTON1;
		}
		else if (B2Off) {
			userInput[i] = BUTTON2;
		}
		else if (B3Off) {
			userInput[i] = BUTTON3;
		}
	}

}

//Compares users input to the generated input to see if they are the same, resulting in TRUE or incorrect resulting in FALSE returns
int checkInput(int size, int simonInput[], int userInput[]) {

	for (int i = 0; i < size; i++) {

		if (userInput[i] != simonInput[i]) {
			return FALSE;
		}
	}
	return TRUE;
}

//Flashes LED that corresponds to red or green numFlashes times to indicate if user has won or lost
void flashStatus(int status) {

	for (int i = 0; i < numFlashes; i++) {
		if (status == FALSE) {
			digitalWrite(rLED1, ON);
			Sleep(flashingDelay);
			digitalWrite(rLED1, OFF);
			Sleep(flashingDelay);

		}
		else {
			digitalWrite(gLED0, ON);
			Sleep(flashingDelay);
			digitalWrite(gLED0, OFF);
			Sleep(flashingDelay);

		}
	}
}

//Turns off all LEDs
void offLEDs(void) {

	for (int i = 0; i < numLEDS; i++) {
		digitalWrite(i, OFF);
	}
}

//Sets LEDs, individually, as on or off based on parameters passed
void setLEDs(int LED0, int LED1, int LED2, int LED3) {

	digitalWrite(gLED0, LED0);
	digitalWrite(rLED1, LED1);
	digitalWrite(yLED2, LED2);
	digitalWrite(bLED3, LED3);
}