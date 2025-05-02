%{
#include<stdio.h>
int lines=0 , words=0 , characters=0;
%}

%%
\n {lines++; characters++;}
[ \t] {characters+=yyleng;}
[a-zA-Z0-9]+ { words++ ; characters+=yyleng;}
. {characters++;}
%%

int main(){
	printf("Enter text : ");
	yylex();
	
	printf("Total No of lines : %d\n", lines);
	printf("Total No of words : %d\n", words);
	printf("Total No of characters : %d\n", characters);	
	return 0;
}

int yywrap(){
	return 1;
}
