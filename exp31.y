%{
	#include <stdio.h>
    extern int yyerror();
    extern int yylex(void);
	int valid=1;
%}

%token digit letter

%%
start : letter s
s : letter s
| digit s
|
;
%%

int yyerror() {
	printf("Input is not an identifier!\n");
	valid=0;
	return 0;
}
int main() {
	printf("Enter a string: ");
	yyparse();
	if(valid)	{
		printf("Input is a identifier!\n");
	}
}