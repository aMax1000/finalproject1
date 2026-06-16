#pragma once
#include <fstream>
#include <iostream>
using namespace std;

//commands.txt




//OPTIONS FOR MENU
enum SaveFilesAndTemplates {
	ONE,
	TWO,
	THREE,
};

Pixel*** chooseSave()
{
	int col, row;
	Pixel*** arr = nullptr;
	unsigned int fileChoice;
	cout << "--- Choose a save file from the following: ---" << endl;
	cout << ONE << endl;
	cout << TWO << endl;
	cout << THREE << endl;
	cin >> fileChoice;
	string filePath;
	switch (fileChoice)
	{
	case ONE:
		filePath = "saves/s1.bin";
		break;
	case TWO:
		filePath = "saves/s2.bin";
		break;
	case THREE:
		filePath = "saves/s3.bin";
		break;
	default:
		cout << "That is not an option.\n\n";
		return nullptr;
	}
	ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&col), sizeof(col));
		file.read(reinterpret_cast<char*>(&row), sizeof(row));
		arr = new Pixel * *[col];
		for (int i = 0; i < col; i++) {
			arr[i] = new Pixel * [row];
			for (int j = 0; j < row; j++) {
				file.read(reinterpret_cast<char*>(arr[i][j]), sizeof(Pixel));
			}
		}
		file.close();
		return arr;
	}
	else cout << "Unable to open file\n";
}
Pixel*** chooseTemplate()
{
	int col, row;
	Pixel*** arr = nullptr;
	unsigned int fileChoice;
	cout << "--- Choose a template from the following: ---" << endl;
	cout << ONE << endl;
	cout << TWO << endl;
	cout << THREE << endl;
	cin >> fileChoice;
	string filePath;
	switch (fileChoice)
	{
	case ONE:
		filePath = "templates/t1.bpm";
		break;
	case TWO:
		filePath = "templates/t1.bpm";
		break;
	case THREE:
		filePath = "templates/t1.bpm";
		break;
	default:
		cout << "That is not an option.\n\n";
		return nullptr;
	}
	ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&col), sizeof(col));
		file.read(reinterpret_cast<char*>(&row), sizeof(row));
		arr = new Pixel * *[col];
		for (int i = 0; i < col; i++) {
			arr[i] = new Pixel * [row];
			for (int j = 0; j < row; j++) {
				file.read(reinterpret_cast<char*>(arr[i][j]), sizeof(Pixel));
			}
		}
		file.close();
		return arr;
	}
	else cout << "Unable to open file\n";
}

//MENU INTERFACE
enum Menu {
	/*NEW_SAVE_FILE,*/
	CHOOSE_SAVE_FILE,
	CHOOSE_TEMPLATE,
	EXIT
};

void showMenu()
{
	cout << "=============== SANDFALL ===============" << endl;
	/*cout << NEW_SAVE_FILE << " - to make a new save file" << endl;*/
	cout << CHOOSE_SAVE_FILE << " - to choose a save file" << endl;
	cout << CHOOSE_TEMPLATE << " - to choose a template" << endl;
	cout << EXIT << " - to exit the program" << endl;
	cout << endl;
}

void runSandfall()
{
	bool isRunning = true;
	unsigned int choice;
	do
	{
		showMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case CHOOSE_SAVE_FILE:
			chooseSave();
			break;
		case CHOOSE_TEMPLATE:
			//
			break;
		case EXIT:
			isRunning = false;
			break;
		default:
			cout << "That is not an option.\n\n";
			return;
		}
	} while (isRunning == true);
}
