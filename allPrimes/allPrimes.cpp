#include <iostream>
#include <vector>

void printVector(const std::vector<int>& v) {
	unsigned size = v.size();
	for (int i = 0; i < size; ++i) {
		std::cout << v[i] << ' ';
	}

}

void allPrimes(int limit) {
	std::vector<int> numbers;
	for (int i = 1; i <= limit; ++i) {
		numbers.push_back(i);
	}

	numbers.erase(numbers.begin()); //remove one;
	unsigned int counter = 0;

	for (int i = 0; i < numbers.size(); ++i) {
		int x = numbers[counter];

		for (int j = counter + 1; j < numbers.size(); ++j) {
			if ((numbers[j] % x) == 0) {
				numbers.erase(numbers.begin() + j);
			}

		}
		numbers.shrink_to_fit();
		++counter;
	}
	printVector(numbers);
}
int main() {
	std::cout << "This program determines all the prime numbers in the set of natural numbers until the specified N. \n";
	std::cout << "Please enter a natural number: ";

	int choice{};

	std::cin >> choice;

	allPrimes(choice);

	return 0;
}