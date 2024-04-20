#include<iostream>
#include<vector>

std::vector<int> naiveSearch(std::string text, std::string pattern) {
	int n = text.size();
	int m = pattern.size();
	std::vector<int> res;
	for (int i = 0; i < n - m + 1; i++) {
		int j = 0;
		for (j = 0; j < m; j++) {
			if (text[i + j] != pattern[j]) {
				break;
			}
		}
		if (j == m) {
			res.push_back(i);
		}
	}
	return res;
}

int main() {
	std::string text = "ABACADAGABAGWDB";
	std::string pattern = "AB";
	std::vector<int> result = naiveSearch(text, pattern);
	std::cout << "Pattern at ";
	for (int i : result) {
		std::cout  << i << " ";
	}
}