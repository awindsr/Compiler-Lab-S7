%{
#include <stdio.h>
#include <ctype.h>

int line_count = 0, word_count = 0, char_count = 0;
FILE *yyin;  
%}

%option noyywrap

WORD    [a-zA-Z_]+        
NEWLINE \n

%%

{NEWLINE}      { line_count++; }
{WORD}         { word_count++; char_count += yyleng;}  
[ \t]          { }  
.              { }

%%

int main() {
    yyin = fopen("input.txt", "r");
    if (yyin == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (yylex()) {}

    fclose(yyin);

    printf("Lines: %d\n", line_count);
    printf("Words: %d\n", word_count);
    printf("Characters: %d\n", char_count);
    
    return 0;
}
