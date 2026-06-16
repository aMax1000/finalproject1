#pragma once
#include <fstream>
#include <iostream>
#include "BMPreader.h"
#include "safepixel1,2,5.h"
#include <vector>
using namespace std;

//commands.txt




//OPTIONS FOR MENU
enum SaveFilesAndTemplates {
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
};




Pixel*** chooseSave(int& col, int& row)
{
	Pixel*** arr = nullptr;
	unsigned int fileChoice;
	cout << "--- Choose a save from the following: ---" << endl;
	cout << ONE << endl;
	cout << TWO << endl;
	cout << THREE << endl;
	choose:
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
		goto choose;
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


Pixel*** chooseTemplate(int& col,int& row)
{
	Pixel*** arr = nullptr;
	vector<vector<Pixelbmp>> pixelarr;
	BmpReader reader;
	unsigned int fileChoice;
	choose:
	cout << "--- Choose a template file from the following: ---" << endl;
	cout << ONE << endl;
	cout << TWO << endl;
	cout << THREE << endl;
	cout << FOUR << endl;
	cout << FIVE << endl;
	cin >> fileChoice;
	string filePath;
	switch (fileChoice)
	{
	case ONE:
		filePath = "templates/t1.bmp";
		break;
	case TWO:
		filePath = "templates/t2.bmp";
		break;
	case THREE:
		filePath =  "templates/t3.bmp";
		break;
	case FOUR:
		filePath = "templates/t4.bmp";
		break;
	case FIVE:
		filePath = "templates/t5.bmp";
		break;
	default:
		cout << "That is not an option.\n\n";
		goto choose;
	}
	reader.readHeader(filePath,col,row);
	if (
		ceil(log(col)) == log(col) or floor(log(col)) == log(col) and
		ceil(log(row)) == log(row) or floor(log(row)) == log(row)
		) {
		cout << "CAN`T USE TEMPLATE: ROW OR COL ISN`T MULTIPLE OF 2";
		goto choose;
	}
	arr = new Pixel * *[col];
	for (int i = 0; i < col; i++) {
		arr[i] = new Pixel*[row];
		for (int j = 0; j < row; j++) {
			arr[i][j] = new Void;
		}
	}
	//print(reader.arr);
	pictoarr(reader.arr,arr,row,col);
	return arr;
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

Pixel*** runSandfall(int& col,int& row)
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
			return chooseSave(col,row);
			break;
		case CHOOSE_TEMPLATE:
			return chooseTemplate(col,row);
			break;
		case EXIT:
			isRunning = false;
			break;
		default:
			cout << "That is not an option.\n\n";
		}
	} while (isRunning == true);
}
