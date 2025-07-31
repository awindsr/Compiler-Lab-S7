%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

%}

%option noyywrap

ABC  abc

%%

{ABC}    { 
                
            for (int i = 0; i < strlen(yytext); i++) {
                yytext[i] = toupper(yytext[i]);
            }
           
            printf("%s", yytext);
        }

.|\n      { printf("%s", yytext); }

%%

int main() {
    printf("Enter a string (Ctrl+D to end input): \n");
    yylex();
    return 0;
}
