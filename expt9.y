%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror();
int valid=1;
%}
%token digit letter
%%
start: letter s
s: letter s
|digit s
|
;
%%
int main()
{
printf("Enter a sequence:");
yyparse();
if(valid)
{
printf("Valid Sequence\n");
}
return 0;
}
void yyerror()
{
printf("Invalid sequence\n");
valid=0;
exit(0);
}
