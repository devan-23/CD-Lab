%{
#include "y.tab.h"
%}
%%
[a-z_A-z][a-zA-Z_0-9] {return letter;}
[0-9] {return digit;}
. {return yytext[0];}
\n {return 0;}
%%
int yywrap()
{
return 1;
}
/*OUTPUT
Enter an expression:3+2*4/1
*/+Valid expression
Enter an expression:3+2*
Error:syntax error
Invalid expression*/
