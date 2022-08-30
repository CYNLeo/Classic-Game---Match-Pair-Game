#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <string.h>
#include <ctime>
#include <cstdlib>
using namespace std;
//global scope of variables
int L = 15, C = 23;
bool isMatch = true;
bool Gameover = true;
bool gameState = false;

//function list
void color(int);
void gotoxy(int, int);


//functions
void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


class Game
{
public:
	// coordinates
	int x1, y1, x2, y2;

	//function list

	//menu
	void main_menu();
	void setting_menu();
	void settingTrials();
	void settingLetters();
	
	//Logic function
	void shuffles();
	void showLetter(); //checking
	void swap(int, int);
	void logic();
	void gameover();
	void inputF();
	void inputS();
	void checkGame();

	//get
	int getNumberOfTrials() { return numberOfTrials; }
	int getrangeOfLetter() { return rangeOfLetter; }
	int getsetSizeNum() { return sizeNum; }
    char getconvertTrials() { return convertTrials; }
	char getrandomLetter();

	//set SETTING
	void setRangeOfLetter(char, char);
	void setConverTrials(int& x) { convertTrials = x + 48; }
	void setConverTrials() { convertTrials = getNumberOfTrials() + 48; }
	void setLetter();

	//set Game
	void setUnrevealed_board();
	void setRevealed_board();
	void setUnreveal_arr(int x, int y) { unrevealed_arr[x][y]; }
	void setReveal_arr(int x, int y) { revealed_arr[x][y]; }

	//get Game
	char getUnreveal_arr(int x, int y) { return unrevealed_arr[x][y]; }
	char getReveal_arr(int x, int y) { return revealed_arr[x][y]; }
	void getunrevealed_board();
	void getrevealed_board();
	
	//Start game
	void startGame()
	{
		while (gameState != Gameover) {
			system("cls");
			getunrevealed_board();
			inputF();
			inputS();
			logic();
			checkGame();
		}
	}


private:
	char unrevealed_arr[15][23];
	char revealed_arr[15][23];
	vector<char> saveLetters;
	char letter = 65;
	char random_Letter;
	char transmitedTrials;
	int numberOfTrials = 5;  // Default 5
	char convertTrials;
	int rangeOfLetter = 6; // Default A-F
	int sizeNum;
	char boardNum = 49;
};

int main() {
	srand(time(0));
	Game start;
	start.setConverTrials();
	start.setUnrevealed_board();
	start.setRevealed_board();
	start.setLetter();
	start.shuffles();
	start.main_menu();
	return 0;
}

//functions
void Game::main_menu() {
	cout << "\n\n\n\n\t  *** Main Menu ***";
	bool mainMenu = true;
	int Set[] = { 12,7,7,7 }; // default colors
	int counter = 1;
	char mainKey;
	int attempt = 1;

	while (mainMenu)
	{
		gotoxy(10, 5);			//position
		color(Set[0]);
		cout << "[1] Start Game";

		gotoxy(10, 6);			//position
		color(Set[1]);
		cout << "[2] Settings";

		gotoxy(10, 7);			//position
		color(Set[2]);
		cout << "[3] Exit" << endl;

		gotoxy(10, 8);			//position
		color(Set[3]);
		cout << "*****************";

		mainKey = _getch();

		if ((mainKey == 'w' || mainKey == 72) && (counter >= 2 && counter <= 3)) // 72 = UP
			counter--;
		if ((mainKey == 's' || mainKey == 80) && (counter >= 1 && counter <= 2)) // 80 = DOWN
			counter++;


		if (mainKey == '\r') // carriage return = enter key
		{
			switch (counter)
			{
			case 1:
				system("cls");
				gameState = false; 
				setUnrevealed_board();
				setRevealed_board();
				setLetter();
				shuffles();
				startGame();
				break;
			case 2:
				system("cls");
				setting_menu();
				break;
			case 3:
				exit(0);
				break;
			}
		}

		Set[0] = 7; //default white color;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;

		if (counter == 1)
			Set[0] = 12;	//12 is color red
		if (counter == 2)
			Set[1] = 12;
		if (counter == 3)
			Set[2] = 12;
	}
}

void Game::setting_menu() {
	cout << "\n\n\n\n\t  *** Setting Menu ***";
	bool settingMenu = true;
	int Set[] = { 12,7,7,7 }; // default colors
	int counter = 1;
	char settingKey;
	while (settingMenu)
	{
		gotoxy(10, 5);			//position
		color(Set[0]); 
		cout << "[1] Range of Letters";

		gotoxy(10, 6);			//position
		color(Set[1]);
		cout << "[2] Number of Trials";
		gotoxy(10, 7);			//position
		color(Set[2]);
		cout << "[3] Return to Main Menu\n";
		gotoxy(10, 8);			//position
		color(Set[3]);
		cout << "*****************";

		settingKey = _getch();

		if ((settingKey == 'w' || settingKey == 72) && (counter >= 2 && counter <= 4)) // 72 = UP
			counter--;
		if ((settingKey == 's' || settingKey == 80) && (counter >= 1 && counter < 4)) // 80 = DOWN
			counter++;

		if (settingKey == '\r') // carriage return = enter key
		{
			switch (counter)
			{
			case 1:
				//startGame();
				system("cls");
				settingLetters();
				break;
			case 2:
				system("cls");
				settingTrials();
				break;
			case 3:
				system("cls");
				main_menu();
				break;
			}
		}

		Set[0] = 7; //default white color;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;


		if (counter == 1)
			Set[0] = 12;	//12 is color red
		if (counter == 2)
			Set[1] = 12;
		if (counter == 3)
			Set[2] = 12;

	}
}

void Game::settingTrials()
{
	char choice;
	char key;
	system("cls");
	cout << "The number of trials is " << getNumberOfTrials() << endl;
	cout << "Do you want to change? (Y/N)";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		do {
			system("cls");
			cout << "Number change(range:2-9): ";
			cin >> numberOfTrials;
		} while (numberOfTrials < 2 || numberOfTrials > 9);
		setConverTrials(numberOfTrials);
		cout << endl;
		cout << "The new trial number is: " << getconvertTrials() << endl;
		cout << "Enter any key back to the main menu:";
		cin >> key;
		system("cls");
		setting_menu();
	}
	else if (choice == 'N' || choice == 'n') {
		system("cls");
		setting_menu();
	}
	else
	{
		cout << "Wrong command";
		system("cls");
		setting_menu();
	}

}

void Game::settingLetters() {
	char choice;
	char key;
	char a, b;
	system("cls");
	cout << "The range of letter is " << letter << " - " << (char)(letter + getrangeOfLetter() - 1) << "( " << getrangeOfLetter() << " )" << endl;
	cout << "Do you want to change? (Y/N)";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		do {
			system("cls");
			cout << "Reminder: 1. must be capital letter 2. input space in the middle with two letters" << endl;
			cout << "Range change (range:A-Z): ";
			cin >> a >> b;
		} while ((int)(b - a) == 0|| a < 65 || a > 90 || b < 65 || b > 90);

		setRangeOfLetter(a, b);
		cout << "The NEW range of letter is " << letter << " - " << (char)(letter + getrangeOfLetter() - 1)<< "( "<< getrangeOfLetter() <<" )" << endl;

		cout << "Enter any key back to the main menu:";
		cin >> key;
		system("cls");
		setting_menu();
	}
	else if (choice == 'N' || choice == 'n') {
		system("cls");
		setting_menu();
	}
	else
	{
		cout << "Wrong command";
		system("cls");
		setting_menu();
	}
}

void Game::showLetter() {					//Test for checking the letters
	for (int i = 0; i < saveLetters.size(); i++)
		cout << saveLetters[i] << " ";

	cout << saveLetters.size() << endl << saveLetters.capacity();
}

void Game::setRangeOfLetter(char a, char b) {
	letter = a;
	int tempNum = (int)(b - a) + 1;
	rangeOfLetter = tempNum;
}

char Game::getrandomLetter() {
	int tempNum;
	tempNum = 0 + rand() % saveLetters.size();
	random_Letter = saveLetters[tempNum];
	return random_Letter;
}

void Game::shuffles() {
	for (int row = 0; row < 15; row++) {
		for (int col = 0; col < 23; col++) {
			if ((row % 2 == 0) && (col > 2 && col < 20) && (col % 2 == 0)) {
				revealed_arr[row][col] = getrandomLetter();
			}
		}
	}
}

void Game::setLetter() {
	for (int i = 0; i < getrangeOfLetter(); i++)
		for (int t = 0; t < 2; t++) {
			saveLetters.push_back(letter + i);
		}
}

void Game::setUnrevealed_board() {
	char n = boardNum;
	for (int row = 0; row < L; row++) {
		for (int col = 0; col < C; col++)
		{
			if ((row % 2 == 0) && (col == 0 || col == 22)) {
				unrevealed_arr[row][col] = n;
			}
			else if ((row % 2 == 0) && (col > 2 && col < 20) && (col % 2 == 0)) {

				unrevealed_arr[row][col] = getconvertTrials();
			}
			else if (col == 2 || col == 20)
				unrevealed_arr[row][col] = '|';
			else
				unrevealed_arr[row][col] = ' ';
		}
		if (row % 2 == 0)
			n++;
	}
}

void Game::setRevealed_board() {
	char n = boardNum;
	for (int row = 0; row < L; row++) {
		for (int col = 0; col < C; col++)
		{
			if ((row % 2 == 0) && (col == 0 || col == 22)) {
				revealed_arr[row][col] = n;
			}
			//else if ((row % 2 == 0) && (col > 2 && col < 20) && (col % 2 == 0)) {
				//revealed_arr[row][col] = 53;
			//}
			else if (col == 2 || col == 20) {
				revealed_arr[row][col] = '|';
			}
			else
			{
				revealed_arr[row][col] = ' ';
			}
		}
		if (row % 2 == 0)
			n++;
	}
}

void Game::getunrevealed_board() {
	cout << "    1 2 3 4 5 6 7 8" << endl;
	cout << "  +-----------------+ " << endl;
	cout << "  |		    | " << endl;

	for (int row = 0; row < L; row++) {
		for (int col = 0; col < C; col++)
		{
			cout << unrevealed_arr[row][col];
		}
		cout << endl;
	}

	cout << "  |		    | " << endl;
	cout << "  +-----------------+ " << endl;
	cout << "    1 2 3 4 5 6 7 8" << endl;
}

void Game::getrevealed_board() {
	cout << "    1 2 3 4 5 6 7 8" << endl;
	cout << "  +-----------------+ " << endl;
	cout << "  |		    | " << endl;

	for (int row = 0; row < L; row++) {
		for (int col = 0; col < C; col++)
		{
			cout << revealed_arr[row][col];
		}
		cout << endl;
	}

	cout << "  |		    | " << endl;
	cout << "  +-----------------+ " << endl;
	cout << "    1 2 3 4 5 6 7 8" << endl;
}

void Game::logic() {
	if (x1 == x2 && y1 == y2) {
		system("cls");
		gameover();
	}

	(unrevealed_arr[x1][y1] == unrevealed_arr[x2][y2]) ? isMatch = true : isMatch = false;

	if (isMatch) {
		unrevealed_arr[x1][y1] = ' ';
		unrevealed_arr[x2][y2] = ' ';
		revealed_arr[x1][y1] = ' ';
		unrevealed_arr[x2][y2] = ' ';
	}
	else
	{
		char tempArr1, tempArr2;

		tempArr1 = revealed_arr[x1][y1];
		revealed_arr[x1][y1] = unrevealed_arr[x1][y1];
		unrevealed_arr[x1][y1] = tempArr1;

		tempArr2 = revealed_arr[x2][y2];
		revealed_arr[x2][y2] = unrevealed_arr[x2][y2];
		unrevealed_arr[x2][y2] = tempArr2;

		if (unrevealed_arr[x1][y1] == 48|| unrevealed_arr[x2][y2] == 48)
			gameover();

	}
}

void Game::gameover() {
	char key;
	system("cls");
	gameState = true;

	cout << "Game Over" << endl;
	getrevealed_board();
	cout << "Press any key back to the main menu: ";
	cin >> key;
	system("cls");
	main_menu();
}

void Game::swap(int x, int y) {
	char tempArr;
	tempArr = revealed_arr[x][y];
	unrevealed_arr[x][y] -= 1;

	system("cls");
	revealed_arr[x][y] = unrevealed_arr[x][y];
	unrevealed_arr[x][y] = tempArr;
	getunrevealed_board();

}

void Game::inputF() {
	cout << "Please input the first coordinate(row and column) of piece: (press 9 9= left game) ";
	cin >> x1 >> y1;
	
	if (x1 == 9 || y1 == 9) {
		system("cls");
		gameover();
	}
		
	x1 = x1 + (x1 - 2);
	y1 = y1 * 2 + 2;
	swap(x1, y1);
}

void Game::inputS() {
	cout << "Please input the second coordinate(row and column) of piece: ";
	cin >> x2 >> y2;

	if (x2 == 9 || y2 == 9) {
		system("cls");
		gameover();
	}

	x2 = x2 + (x2 - 2);
	y2 = y2 * 2 + 2;
	swap(x2, y2);
}

void Game::checkGame() {
	int count = 0;
	for (int row = 0; row < L; row++) {
		for (int col = 0; col < C; col++)
		{
			if ((row % 2 == 0) && (col > 2 && col < 20) && (col % 2 == 0))
			{
				if(revealed_arr[row][col] == ' ')
					count++;
			}
		}
	}
	if (count == 64)
	{
		system("cls");
		gameover();
	}
}