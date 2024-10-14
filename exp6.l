%{
    #include <stdio.h>
%}

%%
abc     { printf("ABC"); }  
.|\n    { putchar(yytext[0]); }  
%%

int main() {
    printf("Enter some text: ");
    yylex();  
    return 0;
}
int yywrap()
{
    return 0;
}
/*-----------------OUTPUT----------------------
Enter some text: hello abc
hello ABC
*/
