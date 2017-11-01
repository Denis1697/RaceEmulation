#include "Includes.h"

void 
ConsoleNotifier::showStatistics(const int& distance, 
	                            const string& time, 
	                            const double& speed) const {
	int windowWidth  = 26;
	int windowHeight = 4;
	int firstColumn  = EnumHelper::START_X_OFFSET + 1;

	Coordinate leftTop  = { EnumHelper::START_X_OFFSET, EnumHelper::START_Y_OFFSET };
	Coordinate rightBot = { EnumHelper::START_X_OFFSET + windowWidth,
		                    EnumHelper::START_Y_OFFSET + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, 
		                               EnumHelper::START_Y_OFFSET + 1 });
	cout <<  "Time: " << setw(8) << time;

	ConsoleHelper::setCursorPosition({ firstColumn, 
		                               EnumHelper::START_Y_OFFSET + 2 });
	cout << "Traveled distance: " << distance << " m";

	ConsoleHelper::setCursorPosition({ firstColumn, 
		                               EnumHelper::START_Y_OFFSET + 3 });
	cout << "Car speed: " << setw(5) << speed << " m/s";
}

bool 
ConsoleNotifier::leaveTheGame() const {

	const int YES_ANSWER = 1;
	const int NO_ANSWER  = 2;

	int leftTopY     = EnumHelper::START_Y_OFFSET + 5;
	int windowWidth  = 16;
	int windowHeight = 5;
	int firstColumn  = EnumHelper::START_X_OFFSET + 1;

	Coordinate answerPosition = { EnumHelper::START_X_OFFSET + 9, leftTopY + 4 };
	Coordinate leftTop        = { EnumHelper::START_X_OFFSET, leftTopY };
	Coordinate rightBot       = { EnumHelper::START_X_OFFSET + windowWidth,
		                          leftTopY + windowHeight };

	string leaveTheGameText[4] = {
		"To menu?",
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

	return false;
}

void 
ConsoleNotifier::setPause() const {
	int leftTopY     = EnumHelper::START_Y_OFFSET + 5;
	int windowWidth  = 6;
	int windowHeight = 2;
	int firstColumn  = EnumHelper::START_X_OFFSET + 1;

	Coordinate leftTop  = { EnumHelper::START_X_OFFSET, leftTopY };
	Coordinate rightBot = { EnumHelper::START_X_OFFSET + windowWidth,
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, leftTopY + 1 });
	cout << "Pause";
	system("pause > NULL");

	ConsoleHelper::clearWindow(leftTop, rightBot);
}

void 
ConsoleNotifier::gameOver() {

	int leftTopY     = EnumHelper::START_Y_OFFSET + 5;
	int windowWidth  = 31;
	int windowHeight = 2;

	Coordinate leftTop  = { EnumHelper::START_X_OFFSET, 
		                    leftTopY };
	Coordinate rightBot = { EnumHelper::START_X_OFFSET + windowWidth,
		                    leftTopY + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ EnumHelper::START_X_OFFSET + 1, leftTopY + 1 });
	cout << "Sorry, your car has crushed...";
}

int
ConsoleNotifier::startingMode() const {

	int windowWidth  = 16;
	int windowHeight = 5;
	int firstColumn  = EnumHelper::START_X_OFFSET + 1;

	Coordinate answerPosition = { EnumHelper::START_X_OFFSET + 9, 
		                          EnumHelper::START_Y_OFFSET + 4 };
	Coordinate leftTop        = { EnumHelper::START_X_OFFSET, 
		                          EnumHelper::START_Y_OFFSET };
	Coordinate rightBot       = { EnumHelper::START_X_OFFSET + windowWidth,
		                          EnumHelper::START_Y_OFFSET + windowHeight };

	string startingModeText[4] = {
		"Select the mode",
		"1. Obstacles",
		"2. Cars",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn, 
			                               EnumHelper::START_Y_OFFSET + i });
		cout << startingModeText[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != EnumHelper::OBSTACLE_ANSWER;
	     isAnswerIncorrect &= answer != EnumHelper::CAR_ANSWER;

	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect  = answer != EnumHelper::OBSTACLE_ANSWER;
		isAnswerIncorrect &= answer != EnumHelper::CAR_ANSWER;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);

	return answer;
}

int 
ConsoleNotifier::menu() const {
	int windowWidth = 17;
	int windowHeight = 7;
	int firstColumn = EnumHelper::START_X_OFFSET + 1;

	Coordinate answerPosition = { EnumHelper::START_X_OFFSET + 9,
		                          EnumHelper::START_Y_OFFSET + windowHeight - 1 };
	Coordinate leftTop        = { EnumHelper::START_X_OFFSET,
		                          EnumHelper::START_Y_OFFSET };
	Coordinate rightBot       = { EnumHelper::START_X_OFFSET + windowWidth,
		                          EnumHelper::START_Y_OFFSET + windowHeight };

	string menuPoints[6] = {
		"1. New game",
		"2. Records table",
		"3. Information",
		"4. Difficulty",
		"5. Exit",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn,
			                               EnumHelper::START_Y_OFFSET + i });
		cout << menuPoints[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != 1;
	     isAnswerIncorrect &= answer != 2;
		 isAnswerIncorrect &= answer != 3;
		 isAnswerIncorrect &= answer != 4;
		 isAnswerIncorrect &= answer != 5;


	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cout << "  ";
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect  = answer != 1;
		isAnswerIncorrect &= answer != 2;
		isAnswerIncorrect &= answer != 3;
		isAnswerIncorrect &= answer != 4;
		isAnswerIncorrect &= answer != 5;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);

	return answer;
}

void 
ConsoleNotifier::recordsTable(const vector<string>& records) const {
	int windowWidth  = 27;
	int windowHeight = records.size() / 3 + 2;
	int firstColumn  = EnumHelper::START_X_OFFSET + 1;
	int firstRow     = EnumHelper::START_Y_OFFSET + 1;

	Coordinate leftTop  = { EnumHelper::START_X_OFFSET,
		                    EnumHelper::START_Y_OFFSET };
	Coordinate rightBot = { EnumHelper::START_X_OFFSET + windowWidth,
		                    EnumHelper::START_Y_OFFSET + windowHeight };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	bool isNewRecord;
	int  recordOffsetY = firstRow + 1;


	ConsoleHelper::setCursorPosition({ firstColumn, firstRow });
	cout << "Nick" << setw(12) << "Distance" << setw(10) << "Time";

	for (int i = 0; i < records.size(); i++) {
		int offsetMultiplier = (i % 3 * 10);
		int recordOffsetX = firstColumn + offsetMultiplier;

		ConsoleHelper::setCursorPosition({ recordOffsetX, recordOffsetY }); 

		isNewRecord = (((i + 1) % 3) == 0);
		if (isNewRecord) {
			recordOffsetY++;
		}

		cout << records[i];		
	}

	system("pause > NULL");
	ConsoleHelper::clearWindow(leftTop, rightBot);
}

string
ConsoleNotifier::inputNickname() const {
	int windowWidth  = 15;
	int windowHeight = 3;
	int firstColumn  = EnumHelper::START_X_OFFSET + 1;
	int firstRow     = EnumHelper::START_Y_OFFSET + 1;

	Coordinate leftTop        = { EnumHelper::START_X_OFFSET,
		                          EnumHelper::START_Y_OFFSET };
	Coordinate rightBot       = { EnumHelper::START_X_OFFSET + windowWidth,
		                          EnumHelper::START_Y_OFFSET + windowHeight };
	Coordinate answerPosition = { firstColumn,
								  firstRow + 1 };

	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ firstColumn, firstRow });
	cout << "Input nickname";

	ConsoleHelper::setCursorPosition(answerPosition);
	string nickname;
	cin >> nickname;

	while (nickname.size() > EnumHelper::NICKNAME_CONSTRAINT) {
		ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 5 });
		cout << "Nickname should be less than " << 
			    EnumHelper::NICKNAME_CONSTRAINT << " symbols!";

		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> nickname;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);
	return nickname;
}

int
ConsoleNotifier::difficultyChoose() const {
	int windowWidth = 18;
	int windowHeight = 5;
	int firstColumn = EnumHelper::START_X_OFFSET + 1;
	int firstRow = EnumHelper::START_Y_OFFSET + 1;

	Coordinate leftTop        = { EnumHelper::START_X_OFFSET,
		                          EnumHelper::START_Y_OFFSET };
	Coordinate rightBot       = { EnumHelper::START_X_OFFSET + windowWidth,
		                          EnumHelper::START_Y_OFFSET + windowHeight };
	Coordinate answerPosition = { EnumHelper::START_X_OFFSET + 9,
		                          EnumHelper::START_Y_OFFSET + 4 };

	string difficulties[4] = {
		"1. Easy",
		"2. Medium",
		"3. Hard",
		"Answer: "
	};

	ConsoleHelper::drawWindow(leftTop, rightBot);

	for (int i = 1; i < windowHeight; i++) {
		ConsoleHelper::setCursorPosition({ firstColumn,
			                               EnumHelper::START_Y_OFFSET + i });
		cout << difficulties[i - 1];
	}

	int answer;
	cin >> answer;

	bool isAnswerIncorrect  = answer != EnumHelper::eDifficulty::EASY;
	     isAnswerIncorrect &= answer != EnumHelper::eDifficulty::MEDIUM;
	     isAnswerIncorrect &= answer != EnumHelper::eDifficulty::HARD;


	while (isAnswerIncorrect) {
		ConsoleHelper::setCursorPosition(answerPosition);
		cout << "  ";
		ConsoleHelper::setCursorPosition(answerPosition);
		cin >> answer;

		isAnswerIncorrect  = answer != EnumHelper::eDifficulty::EASY;
		isAnswerIncorrect &= answer != EnumHelper::eDifficulty::MEDIUM;
		isAnswerIncorrect &= answer != EnumHelper::eDifficulty::HARD;
	}

	ConsoleHelper::clearWindow(leftTop, rightBot);

	return answer;
}

void
ConsoleNotifier::information() const {
	int windowWidth = 24;
	int windowHeight = 12;
	int firstColumn = EnumHelper::START_X_OFFSET + 1;
	int center = EnumHelper::START_X_OFFSET + windowWidth / 2  - 5;
	int firstRow = EnumHelper::START_Y_OFFSET + 1;

	Coordinate leftTop  = { EnumHelper::START_X_OFFSET,
		                    EnumHelper::START_Y_OFFSET };
	Coordinate rightBot = { EnumHelper::START_X_OFFSET + windowWidth,
		                    EnumHelper::START_Y_OFFSET + windowHeight };
	
	ConsoleHelper::drawWindow(leftTop, rightBot);

	ConsoleHelper::setCursorPosition({ center, firstRow });
	cout << "Race game";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 1 });
	cout << "Created by Denis Baghin";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 3 });
	cout << "Car control: arrows";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 4 });
	cout << "Target of the game:";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 6 });
	cout << "Drive as far as you can";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 7 });
	cout << "with a least time!";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 9 });
	cout << "Enter - pause";
	ConsoleHelper::setCursorPosition({ firstColumn, firstRow + 10 });
	cout << "Escape - quit to menu";

	system("pause > NULL");
	ConsoleHelper::clearWindow(leftTop, rightBot);
}
