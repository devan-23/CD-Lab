%{
    #include<stdio.h>
    int word=0, line=0, lower=0,upper=0,digit=0,special=0;
%}
%%
[\t ] word++;
[a-z]         { lower++;  }                 
[A-Z]         { upper++;  }            
[0-9]         { digit++; }                 
\n           { line++; word++; }
.             { special++; }                            
%%

int main()
{
     yyout =fopen("output.txt","w");
     yyin=fopen("input.txt","r");;
     yylex();
     
     fprintf(yyout,"File contains \n\t %d digits",digit);
     fprintf(yyout,"\n\t %d words",word+1);
     fprintf(yyout,"\n\t %d Lowercase Letters",lower);
     fprintf(yyout,"\n\t %d Uppercase Letters",upper);
     fprintf(yyout,"\n\t %d Lines",line+1);
     fprintf(yyout,"\n\t %d special characters",special);
     
     return 0;
}

int yywrap()
{
    return 1;
}
     
