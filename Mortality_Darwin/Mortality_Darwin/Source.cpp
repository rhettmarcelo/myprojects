#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <limits>
#include <sstream>

void cleanBuffer() { //cleans the cin buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void accumulate(std::vector<std::pair<std::string, int>>& v) { //sums the value of the common strings in the vector pair
	for (std::size_t i = 0; i < v.size(); ++i) {
		for (std::size_t j = i + 1; j < v.size(); ++j) {
			if (v[i].first == v[j].first) {
				v[i].second += v[j].second;
				v.erase(v.begin() + j);
				j -= 1;
			}
		}
	}
}

void mySort(std::vector<std::pair<std::string, int>>& v) { //sorts the vector pair based on the integer value in descending order
	std::sort(v.begin(), v.end(), [](auto & lhs, auto& rhs) {
		return lhs.second > rhs.second;
		});
}

unsigned int getRecord(std::vector<std::pair<std::string,int>>& v, unsigned int& size) {
	unsigned int record{};
	while (true) { //loops until user enters a valid integer of records displayed 
		std::cout << "\nHow many top records would you like to find?: ";
		std::cin >> record;
		if (std::cin.fail()) {
			std::cin.clear();
			cleanBuffer();
			std::cerr << "Invalid input. Input a valid integer.\n";
		}
		else if (record <= size) {
			cleanBuffer();
			return record;
		}
		else {
			cleanBuffer();
			std::cerr << "The file does not contain enough records.\n";
			std::cerr << size << " unique record(s) exist in the file.\n";
		}
	}
}

void displayRecords(std::vector<std::pair<std::string, int>>& v, unsigned int size) {
	std::cout << "Code: " << '\t' << "Value:\t" << "Rank:\n";
	for (unsigned int i = 0; i < size; ++i) {
		std::cout << v[i].first << '\t' << v[i].second << '\t' << '(' << i + 1 << ')' << '\n';
	}
	std::cout << "Press ENTER to exit.";
}

int main() {
	std::string filename{};
	std::fstream myFile;
	std::string line{};
	std::vector<std::pair<std::string, int>> list_2;
	bool isFileNotValid{ true };
	std::vector<std::string> initial;

	std::cout << "Written by @rhettarded. ";
	do { //loops until a valid filename is entered.
		std::cout << "Please enter the filename in .csv format. e.g.: file.csv: ";
		std::getline(std::cin, filename);
		myFile.open(filename);
		if (!myFile) {
			std::cerr << "Invalid file name. Please try again. \n";
		}
		else {
			isFileNotValid = false;
		}
	} while (isFileNotValid);

	std::string ignore{};
	std::getline(myFile, ignore); //ignores the first two lines of the file
	std::getline(myFile, ignore);
	
	while (std::getline(myFile, line)) { //.csv file parsing
		std::stringstream inputstring(line);
		std::string parse;
		while (std::getline(inputstring, parse, ',')) {
			if (parse != "") {
				initial.push_back(parse);
			}
		}

		for (int i = 0; i < initial.size(); i += 2) {
			list_2.emplace_back(initial[i], std::stoi(initial[i + 1]));
		}
		initial.clear();
	}

	myFile.close();

	accumulate(list_2);
	mySort(list_2);

	unsigned int size{ static_cast<unsigned int>(list_2.size()) };
	std::cout << "There are currently " << size << " unique records.\n";
	unsigned int record{ getRecord(list_2,size) };

	displayRecords(list_2, record);
	std::cin.get();
	return 0;
}