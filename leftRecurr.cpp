#include<bits/stdc++.h>
using namespace std;

map<char,vector<string> > grammar;

void leftRecurr(char non_terminal, vector<string>productions){
	vector <string> alpha;
	vector <string> beta;
	
	for(string prod: productions){
	    if(prod[0]==non_terminal){
	        alpha.push_back(prod.substr(1));
	    }else{
	        beta.push_back(prod);
	    }
	}
	
	if(alpha.empty()){
		cout<<non_terminal<<" - > ";
		for(size_t i=0 ; i<productions.size() ; i++){
			cout<<productions[i];
			if(i!=productions.size()-1){
				cout<<" | ";
			}
		}
		cout<<endl;
		return;
	}
	
	string newNon_terminal = string(1,non_terminal) + "'";
	//A->A alpha | Beta
	//A->Beta Alpha'
	//Alpha'-> alpha Alpha' | Episilon
	cout<<non_terminal<<" -> ";
	for(size_t i=0; i<beta.size();i++){
		cout<<beta[i]<<newNon_terminal;
		if(i!=beta.size()-1){
			cout<<" | " <<endl;
		}
	}
	cout<<endl;
	
	cout<<newNon_terminal<<" -> ";
	for(size_t i=0; i<alpha.size();i++){
		cout<<alpha[i]<<newNon_terminal;
		cout<<" | ";
	}
	cout << "e" << endl;
	
}




int main(){
	int n;
	cout<<"Enter number of productions: "<<endl;
	cin>>n;
	cin.ignore();
	
	for(int i=0;i<n;i++){
		string line;
		getline(cin,line);
		char non_terminal= line[0];
		string right=line.substr(3);
		stringstream ss(right);
		string prod;
		while((getline(ss,prod,'|'))){
			grammar[non_terminal].push_back(prod);
		}
	}
	
	cout << "\nModified Grammar (after removing left recursion):\n";
    for (auto rule : grammar) {
        leftRecurr(rule.first, rule.second);
    }
	return 0;
}
