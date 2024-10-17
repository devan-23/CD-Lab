#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_EXPRE_LEN 100
#define MAX_TEMP_VARS 50

char expr[MAX_EXPRE_LEN];
char temp_vars[MAX_TEMP_VARS][4];
char res[30][3],arg1[30][3],arg2[30][3],ops[30];

int temp_var_count=0,count=0;
FILE *fp;

char *new_temp_var()
{
    if(temp_var_count>=MAX_TEMP_VARS)
    {
        printf("Error:Too many temporary variables\n");
        exit(1);
    }
    sprintf(temp_vars[temp_var_count],"T%d",temp_var_count+1);
    return temp_vars[temp_var_count++];
}
int precedence(char op)
{
    switch(op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
char *generate_code(char* expr)
{
    int len=strlen(expr);
    int paren_count=0;
    int op_pos=-1;
    int min_precedence=3;
    for(int i=len-1;i>=0;i--)
    {
        if(expr[i]==')')
        {
            paren_count++;
        }
        else if(expr[i]=='(')
        {
            paren_count--;
        }
        else if(paren_count==0)
        {
            int prec=precedence(expr[i]);
            if(prec>0 && prec<min_precedence)
            {
                min_precedence=prec;
                op_pos=i;
            }
        }
    }
    if(op_pos==-1)
    {
        if(expr[0]=='(' && expr[len-1]==')')
        {
            expr[len-1]='\0';
            return generate_code(expr+1);
        }
        return expr;
    }
    char op=expr[op_pos];
    expr[op_pos]='\0';
    char *left=generate_code(expr);
    char *right=generate_code(expr+op_pos+1);
    char *temp=new_temp_var();
    printf("%s:=%s%c%s\n",temp,left,op,right);
    fprintf(fp,"%s:=%s%c%s\n",temp,left,op,right);
    sprintf(res[count],"%s",temp);
    sprintf(arg1[count],"%s",left);
    sprintf(arg2[count],"%s",right);
    ops[count++]=op;
    

    return temp;
}
int main()
{
    fp=fopen("output.txt","w");
    printf("Intermediate Code Generation\n");
    printf("Enter the expression:\t ");
    if(scanf("%99s",expr)!=1)
    {
        printf("Error Reading input\n");
        return 1;
    }
    printf("Intermediate code:\n");
    printf("3Address code\n");
    char* assignment=strchr(expr,'=');
    if(assignment)
    {
        *assignment='\0';
        char *lhs=expr;
        char *rhs=assignment+1;
        char *result=generate_code(rhs);
        printf("%s:=%s\n",lhs,result);
        fprintf(fp,"%s:=%s\n",lhs,result);
    }
    else
    {
        generate_code(expr);
    }
    printf("\nQuadruple\n");
    printf("op\targ1\targ2\tresult\n");
    for(int i=0;i<count;i++)
    {
        printf("%c\t%s\t%s\t%s\n",ops[i],arg1[i],arg2[i],res[i]);
    }
    printf("\nTriple\n");
    printf("op\targ1\targ2\tresult\n");
    for(int i=0;i<count;i++)
    {
        if(arg1[i][0]=='T'&& arg2[i][0]=='T')
        {
            printf("%c\t%c\t%c\t%c\n",ops[i],arg1[i][1],arg2[i][1],res[i][1]);
        }
        else if(arg1[i][0]=='T')
        {
            printf("%c\t%c\t%s\t%c\n",ops[i],arg1[i][1],arg2[i],res[i][1]);
        }
        else if(arg2[i][0]=='T')
        {
            printf("%c\t%s\t%c\t%c\n",ops[i],arg1[i],arg2[i][1],res[i][1]);
        }
        else
        {
            printf("%c\t%s\t%s\t%c\n",ops[i],arg1[i],arg2[i],res[i][1]);
        }
    }
    return 0;
}

/*OUTPUT

Intermediate Code Generation
Enter the expression:    id+id*id/id
Intermediate code:
3Address code
T1:=id*id
T2:=T1/id
T3:=id+T2

Quadruple
op  arg1    arg2    result
*   id  id  T1
/   T1  id  T2
+   id  T2  T3

Triple
op  arg1    arg2    result
*   id  id  1
/   1   id  2
+   id  2   3
  */

