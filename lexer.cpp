#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

enum class TokenType{
	KEYWORD , IDENTIFIER , PUNCTUATOR , STRING_LITERAL , UNKNOWN , NUMBER , OPERATOR
};

struct Token{
	TokenType type;
	string value;
};

string keywords[]={"int","float","if","while","else","return"};

bool isKeyword(string word){
	for(auto k: keywords){
		if(word==k){
			return true;
		}
	}
	return false;
}


vector<Token> tokenization(const string &code){
	vector<Token>tokens;
	string word;
	int m=code.size();
	for(int i=0;i<m;i++){
		char ch=code[i];
		if(isspace(ch)) continue;
		if(isalpha(ch)){
			word="";
			while(isalnum(code[i])) word+=code[i++];
			i--;
			if(isKeyword(word)){
				tokens.push_back({TokenType::KEYWORD , word});
			}else{
				tokens.push_back({TokenType::IDENTIFIER , word});
			}
		}
		else if(isdigit(ch)){
			word="";
			while(isdigit(code[i]) || code[i]=='.') word+=code[i++];
			i--;
			tokens.push_back({TokenType::NUMBER , word});
		}
		else if(ch=='<' || code[i+1]=='<'){
			i++;
			tokens.push_back({TokenType::OPERATOR,"<<"});
		}
		
		else if(ch=='+' || ch=='*' || ch=='-' || ch=='/' ||  ch=='<' || ch=='>'|| ch=='='){
			tokens.push_back({TokenType::OPERATOR,string(1,ch)});
		}
		
		else if(ch=='(' || ch==')' || ch=='{' || ch=='}' || ch=='[' || ch==']' || ch==';'){
			tokens.push_back({TokenType::PUNCTUATOR,string(1,ch)});
		}
		
		
		else if(ch=='"'){
			word="\"";
			i++;
			while(i<m && code[i]!='"'){
				word+=code[i++];
			}
			word+="\"";
			tokens.push_back({TokenType::STRING_LITERAL,word});
		}else{
			tokens.push_back({TokenType::UNKNOWN,string(1,ch)});
		}
	}
	return tokens;
}

void printTokens(vector<Token>&tokens, ostream &out){
	
	for(auto token: tokens){
		string typeName;
		switch(token.type){
			case TokenType::KEYWORD: typeName="KEYWORD"; break;
			case TokenType::IDENTIFIER: typeName="IDENTIFIER"; break;
			case TokenType::OPERATOR: typeName="OPERATOR"; break;
			case TokenType::STRING_LITERAL: typeName="STRING_LITERAL"; break;
			case TokenType::NUMBER: typeName="NUMBER"; break; 
			case TokenType::PUNCTUATOR: typeName="PUNCTUATOR" ; break;
			default : typeName="UNKNOWN";
		}
		out<< token.value << " " << typeName <<endl;
	}
}

int main(){
	ifstream file("input.txt");
	
	if(!file){
		cout<<"Unable to open file!"<<endl;
		return 1;
	}
	
	string code ((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
	
	cout<<"Code: " << code <<endl;
	
	vector<Token>tokens=tokenization(code);
	
	ofstream outfile("output.txt");
	
	printTokens(tokens,outfile);
}




