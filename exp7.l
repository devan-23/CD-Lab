%{
    #include <stdio.h>
    int vowel_count = 0;
    int consonant_count = 0;
%}

%%

[aeiouAEIOU]      { vowel_count++; }                   /* Increment for vowels */
[a-zA-Z]          { consonant_count++; } /* Increment for consonants, excluding vowels */
[ \t]+            { ; }                                /* Ignore spaces and tabs */
.|\n              { return 0; }                        /* End of input on newline or other characters */

%%

int main() {
    printf("Enter a string: ");
    yylex();   /* Call the lexical analyzer */
    printf("\nTotal number of vowels: %d\n", vowel_count);
    printf("Total number of consonants: %d\n", consonant_count);
    return 0;
}

int yywrap() {
    return 1;   /* End of input */
}
/*___________________OUTPUT_______________________
Enter a string: Hello Hi ByE

Total number of vowels: 4
Total number of consonants: 6
*/
