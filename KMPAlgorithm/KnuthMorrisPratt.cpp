#include <iostream>
#include <vector>

std::vector<int> createLPS(const std::string&pattern) {
	int size = pattern.size();
	std::vector<int> lps(size, 0);
	int len = 0;
	int i = 1;
	while (i < size) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if (len > 0)
				len = lps[len - 1];

			else
				i++;
		}
	}
	return lps;
}

std::vector<int> KMP(const std::string&text, const std::string&pattern, const std::vector<int>&LPS) {
	int n = text.size();
	int m = pattern.size();
	std::vector<int> result;
	int i = 0;
	int j = 0;

	while (i < n) {
		if (text[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			if (j > 0)
				j = LPS[j - 1];
			else
				i++;
		}
		if (j == m) {
			result.push_back(i - j);
			j = LPS[j - 1];
		}
	}

	return result;
}

int main() {
	std::string text = "ABABAABCDCABABABAABC";
	std::string pattern = "ABABAABC";
	std::vector<int> LPS = createLPS(pattern);
	std::cout << "LPS table: ";
	for (int i : LPS) {
		std::cout << i << " ";
	}
	std::vector<int> indicies = KMP(text, pattern, LPS);
	std::cout << "\nPattetn indicies: ";
	for (int j : indicies) {
		std::cout << j << " ";
	}
}
