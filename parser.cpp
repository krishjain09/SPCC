#include<bits/stdc++.h>
using namespace std;
map<string,map<string,string> > parsingTable;
void initializeParsingTable(){
	
	parsingTable["E"]["id"]="T E'";
	parsingTable["E"]["("]="T E'";
	
	parsingTable["E'"][")"] = "e";
	parsingTable["E'"]["+"] = "+ T E'";
	parsingTable["E'"]["$"] = "e";
	
	parsingTable["T"]["id"]="F T'";
	parsingTable["T"]["("]="F T'";
	
	parsingTable["T'"][")"]="e";
	parsingTable["T'"]["+"]="e";
	parsingTable["T'"]["*"]="* F T'";
	parsingTable["T'"]["$"]="e";
	
	parsingTable["F"]["id"]="id";
	parsingTable["F"]["("]="( E )";
}

vector<string> tokenization(string input){
	vector<string> tokens;
	stringstream ss(input);
	string token;
	while(ss >> token){
		if(token=="id" || token=="+" || token=="*" || token=="-"){
			tokens.push_back(token);
		}else{
			tokens.push_back("id");
		}
	}
	tokens.push_back("$");
	return tokens;
}

void parser(vector<string>&tokens){
	stack<string>parseStack;
	parseStack.push("$");
	parseStack.push("E");
	int ip=0;
	cout<<"Parsing Process: "<<endl;
	while(!parseStack.empty()){
		string top=parseStack.top();
		parseStack.pop();
		string current = tokens[ip];
		
		cout<<"Top: "<< top <<" , Current Input: "<<current<<endl;
		if(top==current){
			ip++;
			if(top=="$"){
				cout<<"Parsing successfull. "<<endl;
				return;
			}
		}
	else if (parsingTable.count(top) && parsingTable[top].count(current)){
				
			vector<string>symbols;
			string production= parsingTable[top][current];
			cout<<top<<" -> " << production <<endl;
			if(production!="e"){
				string symbol;
				stringstream ss(production);
				while(ss>>symbol){
					symbols.push_back(symbol);
				}
					
				for(int i=symbols.size()-1;i>=0;i--){
					parseStack.push(symbols[i]);
				}
			}
		}
	else{
			cout<<"Error"<<endl;
			break;
		}
	}
	
	cout<<"Parsing Unsuccessful.."<<endl;
}

int main(){
	initializeParsingTable();
	string input;
	
	cout<<"Enter input (like id + id * id)"<<endl;
	getline(cin,input);
	
	vector<string>tokens=tokenization(input);
	cout<<"Tokens: "<<endl;
	for(int i=0;i<tokens.size();i++){
		cout<<tokens[i]<<" ";
	}
	cout<<endl;
	parser(tokens);
	return 0;
}
