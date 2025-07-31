%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

if         { printf("Keyword: if\n"); }
else       { printf("Keyword: else\n"); }
int        { printf("Keyword: int\n"); }
switch     { printf("Keyword: switch\n"); }
char       { printf("Keyword: char\n"); }

[a-zA-Z_][a-zA-Z_0-9]*  { printf("Identifier: %s\n", yytext); }

[0-9]+    { printf("Number: %s\n", yytext); }

"="       { printf("Operator: =\n"); }
"+"       { printf("Operator: +\n"); }
"-"       { printf("Operator: -\n"); }
"*"       { printf("Operator: *\n"); }
"/"       { printf("Operator: /\n"); }
"<"       { printf("Operator: <\n"); }
">"       { printf("Operator: >\n"); }

[ \t\n]   { /* Ignore spaces, tabs, and newlines */ }

.         { /* Ignore other characters */ }

%%

int main(int argc, char **argv) {
    printf("Enter a string: ");
    yylex();  /* Invoke Lex-generated scanner */
    return 0;
}
