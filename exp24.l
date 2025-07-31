%{
#include <stdio.h>
#include <ctype.h>

int vowel_count = 0;
int consonant_count = 0;
%}

%option noyywrap

VOWEL       [aeiouAEIOU]
CONSONANT   [bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]

%%

{VOWEL}      { vowel_count++; }
{CONSONANT}  { consonant_count++; }
[ \t\n]      { } 

%%

int main() {
    printf("Enter a string (Ctrl+D to end input): \n");
    
    yylex();  
    
    printf("Total vowels: %d\n", vowel_count);
    printf("Total consonants: %d\n", consonant_count);
    
    return 0;
}
