#include <iostream>
#include <string>

std::string mathFunction(int Number1, int Number2, int Number3) {
	std::string result;
	if (Number1 + Number2 == Number3) {
		result.append("+");
	}
	if (Number1 - Number2 == Number3) {
		result.append("-");
	}
	if (Number1 * Number2 == Number3) {
		result.append("*");
	}
	if (Number1 / Number2 == Number3) {
		result.append("/");
	}
	if (result.length() == 0) {
		result.append("None");
	}
	return result;
}

void ignore() { //cleans the buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getValue() { //loops until user enters a valid input of type int
	while (true) {
		int number{};
		std::cin >> number;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cerr << "Invalid input. Please enter a number of type int: ";
			ignore();
		}
		else {
			return number;
		}
	}
}

bool repeat(char choice) { 
	return ((choice == 'Y' || choice == 'y') ? true : false);
}

int main() {
	char choice{};

	do { //loops until the user wishes to exit
		std::cout << "Please enter the first number: ";
		int first{getValue()};
		std::cout << "Please enter the second number: ";
		int second{getValue()};
		std::cout << "Please enter the resultant number:";
		int result{getValue()};
		std::cout << "Operation(s): " << mathFunction(first, second, result) << '\n';
		std::cout << "Enter Y/y if you want to continue, else enter any key to exit: ";
		std::cin >> choice;
	} while (repeat(choice));

	return 0;
}