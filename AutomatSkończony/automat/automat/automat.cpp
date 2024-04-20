#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 3;

std::vector<std::vector<int>> createTable(std::string pattern) {
    int n = pattern.size();
    std::vector<std::vector<int>> table(n + 1, std::vector<int>(ALPHABET_SIZE, 0));

    for (int currState = 0; currState <= n; currState++) {
        for (int currLetter = 0; currLetter < ALPHABET_SIZE; currLetter++) {
            std::string pat = pattern.substr(0, currState) + (char)('a' + currLetter);
            for (int i = std::min(currState + 1, n); i > 0; i--){
                if (pattern.substr(0, i) == pat.substr(pat.size() - i)) {
                    table[currState][currLetter] = i;
                    break;
                }
            }
        }
    }
    return table;
}


void search(std::string text, std::string pattern) {
    int N = text.size();
    int M = pattern.size();
    std::vector<std::vector<int>> FA = createTable(pattern);
    int state = 0;

    for (int i = 0; i < N; i++) {
        state = FA[state][text[i] - 'a'];
        if (state == M) {
            std::cout << "Pattern found at position: " << i - M + 1 << std::endl;
        }
    }
}

int main() {
    std::string text = "abababacaba";
    std::string pattern = "ababaca";
    search(text, pattern);

    return 0;
}