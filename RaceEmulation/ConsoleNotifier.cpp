#include "Includes.h"

void 
ConsoleNotifier::showStatistics(const int& distance, 
	                            const string& time, 
	                            const double& speed) const {
	int windowWidth  = 26;
	int windowHeight = 4;
	int firstColumn  = START_X_OFFSET + 1;

	Coordinate leftTop  = { START_X_OFFSET, START_Y_OFFSET };
	Coordinate rightBot = { START_X_OFFSET + windowWidth,
		                    START_Y_OFFSET + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, START_Y_OFFSET + 1 });
	cout <<  "Time: " << setw(8) << time;

	ConsoleHelper::setCursorPosition({ firstColumn, START_Y_OFFSET + 2 });
	cout << "Traveled distance: " << distance << " m";

	ConsoleHelper::setCursorPosition({ firstColumn, START_Y_OFFSET + 3 });
	cout << "Car speed: " << setw(5) << speed << " m/s";
}

bool 
ConsoleNotifier::leaveTheGame() const {

	const int YES_ANSWER = 1;
	const int NO_ANSWER  = 2;

	int leftTopY     = START_Y_OFFSET + 5;
	int windowWidth  = 16;
	int windowHeight = 5;
	int firstColumn  = START_X_OFFSET + 1;

	Coordinate answerPosition = { START_X_OFFSET + 9, leftTopY + 4 };
	Coordinate leftTop        = { START_X_OFFSET, leftTopY };
	Coordinate rightBot       = { START_X_OFFSET + windowWidth,
		                          leftTopY + windowHeight };

	string leaveTheGameText[4] = {
		"Quit?",
		"1. Yes",
		"2. No",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + i });
		cout << leaveTheGameText[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != YES_ANSWER;
	     isAnswerIncorrect &= answer != NO_ANSWER;

	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cout << "  ";
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect  = answer != YES_ANSWER;
		isAnswerIncorrect &= answer != NO_ANSWER;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);

	if (answer == YES_ANSWER) {
		return true;
	}
	else {
		return false;
	}
}

void 
ConsoleNotifier::setPause() const {
	int leftTopY     = START_Y_OFFSET + 5;
	int windowWidth  = 6;
	int windowHeight = 2;
	int firstColumn  = START_X_OFFSET + 1;

	Coordinate leftTop  = { START_X_OFFSET, leftTopY };
	Coordinate rightBot = { START_X_OFFSET + windowWidth,
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 1 });
	cout << "Pause";
	system("pause > NULL");

	ConsoleHelper::clearWindow(leftTop, rightBot);
}

void 
ConsoleNotifier::gameOver() {
	const int START_X_OFFSET = 44;
	const int START_Y_OFFSET = 4;

	int leftTopY     = START_Y_OFFSET + 5;
	int windowWidth  = 31;
	int windowHeight = 2;

	Coordinate leftTop  = { START_X_OFFSET, leftTopY };
	Coordinate rightBot = { START_X_OFFSET + windowWidth,
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ START_X_OFFSET + 1, leftTopY + 1 });
	cout << "Sorry, your car has crushed...";

	system("pause > NULL");
	exit(0);
}

int
ConsoleNotifier::startingMode() const {
	const int OBSTACLE_ANSWER = 1;
	const int CAR_ANSWER = 2;

	int windowWidth  = 16;
	int windowHeight = 5;
	int firstColumn  = START_X_OFFSET + 1;

	Coordinate answerPosition = { START_X_OFFSET + 9, START_Y_OFFSET + 4 };
	Coordinate leftTop        = { START_X_OFFSET, START_Y_OFFSET };
	Coordinate rightBot       = { START_X_OFFSET + windowWidth,
		                          START_Y_OFFSET + windowHeight };

	string startingModeText[4] = {
		"Select the mode",
		"1. Obstacles",
		"2. Cars",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn, START_Y_OFFSET + i });
		cout << startingModeText[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != OBSTACLE_ANSWER;
	     isAnswerIncorrect &= answer != CAR_ANSWER;

	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect = answer != OBSTACLE_ANSWER;
		isAnswerIncorrect &= answer != CAR_ANSWER;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);

	return answer;
}
