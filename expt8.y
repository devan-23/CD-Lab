%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token NUM
%left '+''-'
%left '*''/'
%right UMINUS
%nonassoc '('')'
%%
expr: expr '+' expr {printf("+"); }
| expr '-' expr {printf("-"); }
| expr '*' expr { printf("*");}
| expr '/' expr { printf("/");}
| '(' expr ')' { }
|'-' expr %prec UMINUS {printf("neg");}
|NUM
;
%%
int main(void)
{
printf("Enter an expression:");
if(yyparse()==0)
{
printf("Valid expression\n");
}
else
{
printf("Invalid expression\n");
}
return 0;
}
void yyerror(const char *s)
{
fprintf(stderr,"Error:%s\n",s);}
LEX PROGRAM
%{
#include "y.tab.h"
%}
%%
[0-9] {yylval=atoi(yytext);return NUM ;}
[\t] ;
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"(" {return ')';}
")" {return ')';}
\n {return 0;}
. {printf("Unknown Character:%s\n",yytext);return 0;}
%%
int yywrap()
{
return 1;
}
OUTPUT
Enter a sequenc
