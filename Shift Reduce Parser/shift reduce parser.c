#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Rule {
    char lhs[20];  
    char rhs[20];  
} rules[10];

int main() {
    int ruleCount, stackTop = 0;
    char inputString[30], parseStack[35];
    parseStack[stackTop++] = '$'; 
    parseStack[stackTop] = '\0';   

    printf("Enter the number of productions: ");
    scanf("%d", &ruleCount);
    getchar();  

    printf("Enter the grammar rules:\n");
    for (int i = 0; i < ruleCount; i++) {
        scanf("%[^-]s", rules[i].lhs);  
        getchar();  
        getchar(); 
        scanf("%[^\n]s", rules[i].rhs);  
        getchar(); 
    }

    printf("\nEnter the string to parse: ");
    scanf("%[^\n]s", inputString);
    getchar(); 

    printf("\n%-10s %-10s %-10s\n", "STACK", "INPUT", "ACTION");

    char *currentChar = inputString;

    
    while (*currentChar != '\0') {
        int didReduce;

        
        parseStack[stackTop++] = *currentChar;
        parseStack[stackTop] = '\0';  
        currentChar++;

        printf("%-10s %-10s %-10s\n", parseStack, currentChar, "Shift");

        
        do {
            didReduce = 0;
            for (int i = 0; i < ruleCount; i++) {
                int rhsLength = strlen(rules[i].rhs);
                if (strcmp(&parseStack[1], rules[0].lhs) != 0 && 
                    stackTop >= rhsLength && 
                    strncmp(&parseStack[stackTop - rhsLength], rules[i].rhs, rhsLength) == 0) {

                    
                    char tempMatch[20];
                    strcpy(tempMatch, &parseStack[stackTop - rhsLength]);

                    
                    stackTop -= rhsLength;
                    strcpy(&parseStack[stackTop], rules[i].lhs);
                    stackTop += strlen(rules[i].lhs);
                    parseStack[stackTop] = '\0'; 

                    printf("%-10s %-10s %-10s %s -> %s\n", 
                           parseStack, currentChar, "Reduce", tempMatch, rules[i].lhs);
                    didReduce = 1;
                    break;
                }
            }
        } while (didReduce); 
    }

    
    if (strcmp(&parseStack[1], rules[0].lhs) == 0 && stackTop == 2) {
        printf("%-10s %-10s %-10s\n", parseStack, currentChar, "ACCEPT");
    } else {
        printf("%-10s %-10s %-10s\n", parseStack, currentChar, "REJECT");
    }

    return 0;
}
/*Output

Enter the number of productions: 3
Enter the grammar rules:
E->E+E
E->E*E
E->i

Enter the string to parse: i*i+i

STACK      INPUT      ACTION    
$i         *i+i       Shift     
$E         *i+i       Reduce     i -> E
$E*        i+i        Shift     
$E*i       +i         Shift     
$E*E       +i         Reduce     i -> E
$E         +i         Reduce     E*E -> E
$E+        i          Shift     
$E+i                  Shift     
$E+E                  Reduce     i -> E
$E                    Reduce     E+E -> E
$E                    ACCEPT 
*/
