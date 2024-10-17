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
/*OUTPUT
Enter a sequence:_shdj234
Valid Sequence
Enter a sequence:ndju@_fjd123
Invalid sequence
Enter a sequence:@chs123
Valid Sequence
Enter a sequence:bvhd@12sa
Invalid sequence*/
