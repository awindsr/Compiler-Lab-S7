%{
    #include <stdio.h>
    #include <stdlib.h>  // Include this for exit()
    #include <ctype.h>   // Optionally, to handle character-related operations in lexers
    #define YYSTYPE double
    extern int yyerror(char *msg);
    extern int yylex(void);  // Declare yylex() to avoid implicit declaration
%}

%token DIGIT ID NL
%left '-' '+'
%left '*' '/'
%token '='

%%
stmt : ID '=' exp NL {
    printf("Valid expression\n");
    exit(0);  // Now it's safe to use exit()
}
| exp NL {
    printf("Valid expression\n");
    exit(0);  // Safe exit here as well
};

exp : exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | '(' exp ')'
    | ID
    | DIGIT;

%%

int yyerror(char *msg) {
    printf("Invalid string\n");
    return 0;
}

int main() {
    printf("Enter the expression: ");
    yyparse();
    return 0; 
}
