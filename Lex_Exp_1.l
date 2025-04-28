%{
#include<stdio.h>
%}

%%
[0-9]+ {printf("\n%s is a number.",yytext);}
[a-zA-Z]+ {printf("\n%s is a word. ", yytext);}
. {}
%%

int main(){
	printf("Enter the string  to check whether the string is a word or a number: ");
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
