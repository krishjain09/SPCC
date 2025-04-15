#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Token Types
enum class TokenType {
    KEYWORD, IDENTIFIER, NUMBER, OPERATOR, PUNCTUATOR, UNKNOWN
};

// Token Structure
struct Token {
    TokenType type;
    string value;
};

// Keywords List
string keywords[] = {"int", "float", "if", "else", "while", "return"};

// Function to check if a word is a keyword
bool isKeyword(const string& word) {
    for (const string& kw : keywords) {
        if (word == kw) return true;
    }
    return false;
}

// Tokenize Function
vector<Token> tokenize(const string& code) {
    vector<Token> tokens;
    string word;

    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];

        // Skip whitespaces
        if (isspace(c)) continue;

        // If letter — identifier or keyword
        if (isalpha(c)) {
            word = "";
            while (isalnum(code[i])) word += code[i++];
            i--; // step back
            if (isKeyword(word))
                tokens.push_back({TokenType::KEYWORD, word});
            else
                tokens.push_back({TokenType::IDENTIFIER, word});
        }
        // If digit — number
        else if (isdigit(c)) {
            word = "";
            while (isdigit(code[i]) || code[i] == '.') word += code[i++];
            i--;
            tokens.push_back({TokenType::NUMBER, word});
        }
        // If operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            tokens.push_back({TokenType::OPERATOR, string(1, c)});
        }
        // If punctuator
        else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
            tokens.push_back({TokenType::PUNCTUATOR, string(1, c)});
        }
        // Unknown character
        else {
            tokens.push_back({TokenType::UNKNOWN, string(1, c)});
        }
    }
    return tokens;
}

// Function to display tokens
void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        string typeName;
        switch (token.type) {
            case TokenType::KEYWORD: typeName = "KEYWORD"; break;
            case TokenType::IDENTIFIER: typeName = "IDENTIFIER"; break;
            case TokenType::NUMBER: typeName = "NUMBER"; break;
            case TokenType::OPERATOR: typeName = "OPERATOR"; break;
            case TokenType::PUNCTUATOR: typeName = "PUNCTUATOR"; break;
            default: typeName = "UNKNOWN";
        }
        cout << typeName << " : " << token.value << endl;
    }
}

// Main Function
int main() {
    ifstream file("input.txt");
    if (!file) {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    cout << "Source Code:\n" << code << endl << endl;

    vector<Token> tokens = tokenize(code);

    cout << "Tokens:\n";
    printTokens(tokens);

    return 0;
}

