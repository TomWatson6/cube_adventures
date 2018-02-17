#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Input {

public:
	vector<string> readInFromFile(string path) {

		vector<string> input = vector<string>();

		try {
			ifstream cubeFile(path);
			string line;

			while (getline(cubeFile, line)) {
				input.push_back(line);
			}
			cubeFile.close();
		}
		catch (exception e) {
			cout << "There is an exception thrown for the file io" << endl;
		}

		return input;

	}

	int getItemAmount() { return itemAmount; }

	void setItemAmount(int itemAmount) { this->itemAmount = itemAmount; }

private:
	int itemAmount = 0;

};