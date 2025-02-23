//Deva narayanan 
//S7 CS2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[25], production[25];
int indexPtr, inputLen;

void replaceSubstring(char target[], char replacement[]) {
    char tempResult[1000];
    int i, j = 0, k;
    int targetLen = strlen(target);
    int replacementLen = strlen(replacement);
    int found = 0;

    for (i = 0; production[i] != '\0'; i++) {
        if (strncmp(&production[i], target, targetLen) == 0) {
            for (k = 0; k < replacementLen; k++) {
                tempResult[j++] = replacement[k];
            }
            i += targetLen - 1;
            found = 1;
        } else {
            tempResult[j++] = production[i];
        }
    }
    tempResult[j] = '\0';
    strcpy(production, tempResult);

    if (found)
        printf("%-25s\t", tempResult);
    else
        printf("Substring not found.\n");
}

void removeSubstring(char target[]) {
    char tempResult[1000];
    int i, j = 0, k;
    int targetLen = strlen(target);
    int found = 0;

    for (i = 0; production[i] != '\0'; i++) {
        if (strncmp(&production[i], target, targetLen) == 0) {
            i += targetLen - 1;
            found = 1;
        } else {
            tempResult[j++] = production[i];
        }
    }
    tempResult[j] = '\0';
    strcpy(production, tempResult);

    if (found)
        printf("%-25s\t", tempResult);
    else
        printf("Substring not found.\n");
}

void parseE() {
    printf("E->TE'\n");
    replaceSubstring("E", "TE'");
    parseT();
    parseE_();
}

void parseE_() {
    if (input[indexPtr] == '+' && indexPtr < inputLen) {
        printf("E'->+TE'\n");
        replaceSubstring("E'", "+TE'");
        indexPtr++;
        parseT();
        parseE_();
    } else {
        printf("E'->e\n");
        removeSubstring("E'");
    }
}

void parseT() {
    printf("T->FT'\n");
    replaceSubstring("T", "FT'");
    parseF();
    parseT_();
}

void parseT_() {
    if (input[indexPtr] == '*' && indexPtr < inputLen) {
        printf("T'->*FT'\n");
        replaceSubstring("T'", "*FT'");
        indexPtr++;
        parseF();
        parseT_();
    } else {
        printf("T'->e\n");
        removeSubstring("T'");
    }
}

void parseF() {
    if (input[indexPtr] >= '0' && input[indexPtr] <= '9' && indexPtr < inputLen) {
        printf("F->i\n");
        char tempStr[3];
        tempStr[0] = input[indexPtr];
        tempStr[1] = '\0';
        replaceSubstring("F", tempStr);
        indexPtr++;
    }
}

int main() {
    printf("\nGrammar Parser");
    printf("\n\t E->TE' \n\t E'->+TE'|e \n\t T->FT' ");
    printf("\n\t T'->*FT'|e \n\t F->i");
    printf("\n Enter the input: ");
    scanf("%s", input);
    
    inputLen = strlen(input);
    strcpy(production, "E");

    printf("E                            \t");
    parseE();

    if (indexPtr == inputLen && input[indexPtr] == '\0') {
        printf("String accepted");
    } else {
        printf("\n String not accepted");
    }

    return 0;
}

/*Output
Grammar Parser
	 E->TE' 
	 E'->+TE'|e 
	 T->FT' 
	 T'->*FT'|e 
	 F->i

Enter the input: 3+6
E                            	E->TE'
TE'                      	T->FT'
FT'E'                    	F->i
3T'E'                    	T'->e
3E'                      	E'->+TE'
3+TE'                    	T->FT'
3+FT'E'                  	F->i
3+6T'E'                  	T'->e
3+6E'                    	E'->e
3+6                      	String accepted 
*/
