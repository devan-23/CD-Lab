%{
#include <stdio.h>
#include <string.h>
%}
%option noyywrap
%%
"if" {
fprintf(yyout,"Keyword:IF\n");
}
"else" {
fprintf(yyout,"Keyword:ELSE\n");
}
"while" {
fprintf(yyout,"Keyword:WHILE\n");
}
"return" {
fprintf(yyout,"Keyword:RETURN\n");
}
"int" {
fprintf(yyout,"Keyword:INT\n");
}
"main" {
fprintf(yyout,"Keyword:MAIN\n");
}
[a-zA-Z][a-zA-Z0-9_]* {
fprintf(yyout,"Identifier:%s\n",yytext);
}
"=" {
fprintf(yyout,"operator:=\n");
}
"+" {
fprintf(yyout,"operator:+\n");
}
"-" {
fprintf(yyout,"operator:-\n");
}
"*" {
fprintf(yyout,"operator:*\n");
}
"/" {fprintf(yyout,"operator:/\n");}
[0-9]+ {fprintf(yyout,"Number:%s\n",yytext);}
"(" {fprintf(yyout,"Left Paranthesis:(\n");}
")" {fprintf(yyout,"Right Paranthesis:)\n");}
"{" {fprintf(yyout,"Left Brace:{\n");}
"}" {fprintf(yyout,"Right Brace:}\n");}
";" {fprintf(yyout,"Semicolon:;\n");}
[\t\n]+ { }
. { }
%%
int main(void)
{
FILE *fp=fopen("inp2.txt","r");
yyin=fp;
FILE *fp1=fopen("out2.txt","w");
yyout=fp1;
yylex();
return 0;
}
