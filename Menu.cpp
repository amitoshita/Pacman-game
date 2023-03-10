#include "Menu.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;


void Menu::printMenu() const {
	system("cls");
	gotoxy(25, 7);
	cout << "################################################" << endl;
	gotoxy(25, 8);
	cout << "#                                              #" << endl;
	gotoxy(25, 9);
	cout << "#        Please insert your choice:            #" << endl;
	gotoxy(25, 10);
	cout << "#   1. Start a new game                        #" << endl;
	gotoxy(25, 11);
	cout << "#   2. Present instructions and keys           #" << endl;
	gotoxy(25, 12);
	cout << "#   3. Exit                                    #" << endl;
	gotoxy(25, 13);
	cout << "#                                              #" << endl;
	gotoxy(25, 14);
	cout << "#                                              #" << endl;
	gotoxy(25, 15);
	cout << "#                                              #" << endl;
	gotoxy(25, 16);
	cout << "################################################" << endl;
	gotoxy(27, 14);
}

void Menu::CheckUserChoice(char& choice) {
	while (choice != '1' && choice != '2' && choice != '3') {
		printMenu();
		cout << "Invalid choice, please enter a valid number." << endl;
		gotoxy(27, 15);
		cin >> choice;
	}
}

void Menu::ghostLevelMenu() {
	system("cls");
	gotoxy(25, 7);
	cout << "################################################" << endl;
	gotoxy(25, 8);
	cout << "#                                              #" << endl;
	gotoxy(25, 9);
	cout << "#    Please choose the level of the Ghosts:    #" << endl;
	gotoxy(25, 10);
	cout << "#   1. Best                                    #" << endl;
	gotoxy(25, 11);
	cout << "#   2. Good                                    #" << endl;
	gotoxy(25, 12);
	cout << "#   3. Novice                                  #" << endl;
	gotoxy(25, 13);
	cout << "#                                              #" << endl;
	gotoxy(25, 14);
	cout << "#                                              #" << endl;
	gotoxy(25, 15);
	cout << "#                                              #" << endl;
	gotoxy(25, 16);
	cout << "################################################" << endl;
	gotoxy(27, 14);
}

int Menu::checkGhostLevelMenu() {
	int choice;
	cin >> choice;
	while (choice != 1 && choice != 2 && choice != 3) {
		ghostLevelMenu();
		cout << "Invalid choice, please enter a valid number." << endl;
		gotoxy(27, 14);
		cin >> choice;
	}
	return choice;
}

void Menu::printColoredMenu() const {
	system("cls");
	gotoxy(25, 7);
	cout << "################################################" << endl;
	gotoxy(25, 8);
	cout << "#                                              #" << endl;
	gotoxy(25, 9);
	cout << "#     Run the game with or without colors?     #" << endl;
	gotoxy(25, 10);
	cout << "#   1. With colors                             #" << endl;
	gotoxy(25, 11);
	cout << "#   2. Withous colors                          #" << endl;
	gotoxy(25, 12);
	cout << "#                                              #" << endl;
	gotoxy(25, 13);
	cout << "#                                              #" << endl;
	gotoxy(25, 14);
	cout << "#                                              #" << endl;
	gotoxy(25, 15);
	cout << "################################################" << endl;
	gotoxy(27, 13);
}

void Menu::CheckUserChoiceColoredMenu(char& choice) {
	while (choice != '1' && choice != '2') {
		printColoredMenu();
		cout << "Invalid choice, please enter a valid number." << endl;
		gotoxy(27, 14);
		cin >> choice;
	}
}

void Menu::instructions(char& choice) {
	system("cls");
	gotoxy(15, 5);
	cout << "###########################################################################################" << endl;
	gotoxy(15, 6);
	cout << "#                              WELCOME TO PACMAN GAME!                                    #" << endl;
	gotoxy(15, 7);
	cout << "# As a pacman player, you have to eat all the bread crumbs all over the board.            #" << endl;
	gotoxy(15, 8);
	cout << "# But it not that easy! you have to run away from the ghosts that can eat you easly.      #" << endl;
	gotoxy(15, 9);
	cout << "# If you succeed, An appropriate message will appear on the board.                        #" << endl;
	gotoxy(15, 10);
	cout << "# If not, you can try again and again.                                                    #" << endl;
	gotoxy(15, 11);
	cout << "# These are the keyboard keys you can use:                                                #" << endl;
	gotoxy(15, 12);
	cout << "# A or a - for going left                                                                 #" << endl;
	gotoxy(15, 13);
	cout << "# W or w - for going up                                                                   #" << endl;
	gotoxy(15, 14);
	cout << "# X or x - for going down                                                                 #" << endl;
	gotoxy(15, 15);
	cout << "# S or s - for stop the pacman only                                                       #" << endl;
	gotoxy(15, 16);
	cout << "# ESC - for stop the all game                                                             #" << endl;
	gotoxy(15, 17);
	cout << "#                                                                                         #" << endl;
	gotoxy(15, 18);
	cout << "#                                   Good luck!                                            #" << endl;
	gotoxy(15, 19);
	cout << "#                          Press any key to return to menu                                #" << endl;
	gotoxy(15, 20);
	cout << "#                                                                                         #" << endl;
	gotoxy(15, 21);
	cout << "###########################################################################################" << endl;
	gotoxy(17, 20);
	cin >> choice;
}

void Menu::printLossMenu() {
	char temp;
	system("cls");
	gotoxy(25, 7);
	cout << "################################################" << endl;
	gotoxy(25, 8);
	cout << "#             GAME OVER - YOU LOSE!            #" << endl;
	gotoxy(25, 9);
	cout << "#   press any key to return to the main menu   #" << endl;
	gotoxy(25, 10);
	cout << "#                                              #" << endl;
	gotoxy(25, 11);
	cout << "################################################" << endl;
	gotoxy(27, 10);
	cin >> temp;
}

void Menu::printVictoryMenu() {
	char temp;
	system("cls");
	gotoxy(25, 7);
	cout << "################################################" << endl;
	gotoxy(25, 8);
	cout << "#                  YOU WON!                    #" << endl;
	gotoxy(25, 9);
	cout << "#   press any key to return to the main menu   #" << endl;
	gotoxy(25, 10);
	cout << "#                                              #" << endl;
	gotoxy(25, 11);
	cout << "################################################" << endl;
	gotoxy(27, 10);
	cin >> temp;
}

void Menu::printNoFile() {
	char temp;
	system("cls");
	gotoxy(25, 7);
	cout << "################################################" << endl;
	gotoxy(25, 8);
	cout << "#   There are no correct files in this folder  #" << endl;
	gotoxy(25, 9);
	cout << "#   press any key to return to the main menu   #" << endl;
	gotoxy(25, 10);
	cout << "#                                              #" << endl;
	gotoxy(25, 11);
	cout << "################################################" << endl;
	gotoxy(27, 10);
	cin >> temp;
}

