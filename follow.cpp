// Online C++ compiler to run C++ program online
#include <iostream>
#include<map>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

map<char,vector<string> > grammar;
map<char , set<char> > firstSet;
map<char , set<char> > followSet;
char startSymbol;

bool nonTerminal(char ch){
    return ch>='A' && ch<='Z';
}

set<char> getFirst(string str, int pos){
    bool epsilon=true;
    set<char>result;
    
    while(pos<str.size() && epsilon){
        epsilon=false;
        char sym=str[pos];
        if(!nonTerminal(sym)){
            result.insert(sym);
            break;
        }
        else{
            for(char ch: firstSet[sym]){
                if (ch=='e') epsilon=true;
                else result.insert(ch);
            }
        }
        pos++;
    }
    
    if(epsilon) result.insert('e');
    return result;
}


void computeFollow(){
    bool changed;
    followSet[startSymbol].insert('$');
    do{
         changed=false;
        for(auto entry: grammar){
        char lhs=entry.first;
        for(auto prod: entry.second){
            for(int i=0;i<prod.size();i++){
                char B=prod[i];
                if(nonTerminal(B)){
                    
                    set<char>followAdd;
                    
                    if(i+1<prod.size()){
                        
                        set<char> firstBeta=getFirst(prod,i+1);
                        
                        for(char f: firstBeta){
                            if (f!='e') {
                                followAdd.insert(f);
                            }
                        }
                        
                        if(firstBeta.count('e')){
                            followAdd.insert(followSet[lhs].begin(),
                        followSet[lhs].end());
                        }
                        
                        
                    }else{
                        followAdd.insert(followSet[lhs].begin(),
                        followSet[lhs].end());
                    }
                    
                    int before =followSet[B].size();
                    followSet[B].insert(followAdd.begin(),followAdd.end());
                    if(followSet[B].size() > before){
                        changed=true;
                    }
                }
            }
        }
    }
    }while(changed);
    
    
    
}


int main() {
    int n;
    cout<<"Enter number of productions: "<<endl;
    cin>>n;
    cin.ignore();
    
    for(int i=0;i<n;i++){
        string line;
        cout<<"Enter grammar like (S->AB): "<<endl;
        getline(cin,line);
        char non_terminal=line[0];
        string right=line.substr(3);
        string prod;
        stringstream ss(right);
        while(getline(ss,prod,'|')){
            grammar[non_terminal].push_back(prod);
        }
    }
    
    startSymbol='E';
    firstSet['R']={'+','e'};
    
    computeFollow();
    
    
    for(auto[non_terminal,prod]: followSet){
        cout<<"Follow("<<non_terminal<<") = {";
        for(char f: prod){
            cout<<f<<" ";
        }
        cout<<"} "<<endl;
    }
    
    return 0;
}
