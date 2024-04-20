#include <iostream>
#include <vector>
#define DIVISOR 101
std::vector<int> RabinKarp(const std::string& text, const std::string& pattern) {
	
	int n = text.size();
	int m = pattern.size();
	std::vector<int> res;
	int textHash = 0;
	int patternHash = 0;
	int p = 1;
	
	for (int i = 0; i < m - 1; i++)
		p = (10 * p) % DIVISOR;

	for (int i = 0; i < m; i++) {
		textHash =  (10 * textHash + text[i]) % DIVISOR;
		patternHash =  (10 * patternHash + pattern[i]) % DIVISOR;
	}

	for (int i = 0; i < n - m + 1; i++) {
		
		if (textHash == patternHash)
			res.push_back(i);

		textHash = (10*(textHash - (p * text[i])) + text[i + m]) % DIVISOR;
		if (textHash < 0) {
			textHash += DIVISOR;
		}

	}
	return res;
}
int main() {
	std::vector<int> indiceis;
	std::string text = "ABCAADACABABACACA"; // 2 7 13 15
	std::string pattern = "CA";
	std::vector<int> indicies = RabinKarp(text,pattern);
	std::cout << "Pattern propably at indidceis:";
	for (int i : indicies)
		std::cout << i << " ";


	return 0;
}