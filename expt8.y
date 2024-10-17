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
}
