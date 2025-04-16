#include<bits/stdc++.h>


using namespace std;


int isOperator(char ch){
	if (ch=='+' || ch=='-' || ch=='*' || ch=='/')
		return 1;
	return 0;
}

int priority(char ch){
	if (ch=='*' || ch=='/') return 3;
	else if (ch=='+' || ch=='-') return 2;
	return 1;
}

string convertToPostfix(string expression){
	
	string postfix;
	stack<char>st;
	int n=expression.size();
	for(int i=0; i<n; i++){
		char x=expression[i];
		if(isalnum(x)){
			postfix+=x;
		}
		else if (x=='('){
			st.push(x);
		}
		else if(isOperator(x)){
			while(!st.empty()&& priority(x) <= priority(st.top())){
				
				char ele=st.top();
				st.pop();
				postfix+=ele;
			}
			st.push(x);
		}
		else{
			while(st.top()!='('){
				char ele=st.top();
				st.pop();
				postfix+=ele;
			}
			st.pop();			
		}
	}
	
	while(!st.empty()){
		char ele=st.top();
		st.pop();
		postfix+=ele;
		
	}
	return postfix;
}

void generateTAC(string postfix){
	stack<string>st;
	int tempCount=1;
	
	for(char ch: postfix){
		if(isalnum(ch)){
			string operand(1,ch);
			st.push(operand);
		}
		else if(isOperator(ch)){
			string op2=st.top();
			st.pop();
			string op1=st.top();
			st.pop();
			string temp= "t" + to_string(tempCount++);
			cout<< temp <<" = "<<op1<< " "<<ch <<" "<< op2 << endl;
			st.push(temp); 
		}
			
	}
	cout<<"Result = " << st.top();
	
}



int main(){
	string expression;
	cout<<"Enter arithmetic expression (a+b*c) : "<<endl;
	getline(cin,expression);
	
	string postfix = convertToPostfix(expression);
	cout<<"Postfix Expression: "<<postfix;
	cout<<"Three Adress Code Generation " <<endl;
	generateTAC(postfix);
	
	return 0;
}
