// Online C++ compiler to run C++ program online
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;




map<char,vector<string> > grammar; 
map<char,set<char>> firstSet;
set<char> visited;

bool isNonTerminal(char symbol){
    return symbol>='A' && symbol<='Z';
}
void computeFirst(char non_terminal){
    if(visited.count(non_terminal)) return;
    visited.insert(non_terminal);
    
    for(auto prod: grammar[non_terminal]){
        for(int i=0 ; i<prod.size() ; i++){
            char symbol = prod[i];
            
            if(!isNonTerminal(symbol)){
                firstSet[non_terminal].insert(symbol);
                break;
            }
            
            computeFirst(symbol);
            bool hasEpsilon =false;
            for(auto first: firstSet[symbol]){
                if (first=='e') hasEpsilon=true;
                else firstSet[non_terminal].insert(first);
            }
            
            if(!hasEpsilon) break;
            
            if(i==prod.size()-1){
                firstSet[non_terminal].insert('e');
            }
            
        }
    }
    
}


int main() {
    int n;
    cout<<"Enter number of productions: "<<endl;
    cin>>n;
    cin.ignore();
    
    for(int i=0 ; i<n ; i++){
        cout<<"Enter production rule(like S->AB|e): ";
        string line;
        getline(cin,line);
        char non_terminal=line[0];
        string right=line.substr(3);
        string prod;
        stringstream ss(right);
        while(getline(ss,prod,'|')){
            grammar[non_terminal].push_back(prod);
        }
    }
    
    for(auto [non_terminal , _]: grammar){
        visited.clear();
        computeFirst(non_terminal);
    }
    
    for(auto [non_terminal,first]: firstSet){
        cout<<"First("<<non_terminal<<") = { ";
        for(auto f: first){
            cout<<f <<" ";
        }
        cout<<"} "<<endl;
    }
    return 0;
}
