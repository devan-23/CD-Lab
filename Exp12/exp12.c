#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
struct Derivation 
{
char derivation[64]; 
struct Derivation * next;
};
struct Derivation * grammar_set[26];
char firsts[26][64], follows[26][64];
int first_len[26], follow_len[26], is_being_searched[26]; 
int parse_grammar(char *);

void find_first(char variable);
void add_first(char first, char variable); void find_follow();
void add_follow(char follow, char variable); void add_derivations(char, struct Derivation *); char next_symbol(char **);
void assert(int, char *); 
void reset();

int main() 
{
char grammar_str[128];
printf("Enter Grammars (start with $ to stop): \n"); scanf("%[^\n]s", grammar_str);
while (parse_grammar(grammar_str)) { scanf(" %[^\n]s", grammar_str);
 }
  for (int i = 0; i < 26; i++) {
if (grammar_set[i] != NULL) { find_first(i + 'A'); }
}
find_follow();
for (int i = 0; i < 26; i++) {
if (grammar_set[i] == NULL) { continue; } printf("\nFirst(%c): ", i + 'A');
for (int j = 0; j < first_len[i]; j++) { printf("%c, ", firsts[i][j]); } printf("\nFollow(%c): ", i + 'A');
for (int j = 0; j < follow_len[i]; j++) { printf("%c, ", follows[i][j]); }
}
}
void find_first(char variable) { int index = variable - 'A';
assert(variable >= 'A' && variable <= 'Z', "Variable must be a capital letter."); assert(grammar_set[index] != NULL, "Variable not in grammar.");
if (is_being_searched[index]) { return; } is_being_searched[index] = 1;
struct Derivation *p = grammar_set[index]; int derivation_index = 0;
while (p != NULL) {
 
if (p -> derivation[derivation_index] > 'Z' || p -> derivation[derivation_index] < 'A') { add_first(p -> derivation[derivation_index], variable);
p = p -> next; continue;
}
find_first(p -> derivation[derivation_index]); int new_index = derivation_index;
for (int i = 0; i < first_len[p -> derivation[derivation_index] - 'A']; i++) { char first = firsts[p -> derivation[derivation_index] - 'A'][i];
if (first == '\0') { new_index = derivation_index + 1; } else { add_first(first, variable); }
}
if (new_index == derivation_index) { p = p -> next;
derivation_index = 0;
} else { derivation_index = new_index; }
}
is_being_searched[index] = 0;
}
void find_follow() {
for (int i = 0; i < 26; i++) {
for (struct Derivation *p = grammar_set[i]; p != NULL; p = p -> next) { char *s = p -> derivation;
int deviation = 1; while (*s != '\0') {
int new_deviation = deviation; if (*s > 'Z' || *s < 'A') {
s++;
continue;
}
if (*(s + deviation) > 'Z' || *(s + deviation) > 'A') {
if (*s + deviation != '\0') { add_follow(*(s + deviation), *s); } s++;
continue;
}
for (int j = 0; j < first_len[*(s + deviation) - 'A']; j++) { char follow = firsts[*(s + deviation) - 'A'][j];
if (follow == '\0') { new_deviation++; } else { add_follow(follow, *s); }
}
if (new_deviation == deviation) { deviation = 1;
s++;
} else { deviation = new_deviation; }
}
}
}
}
void add_first(char first, char variable) {
for (int i = 0; i < first_len[variable - 'A']; i++) {
 
if (firsts[variable - 'A'][i] == first) { return; }
}
firsts[variable - 'A'][first_len[variable - 'A']++] = first;
}
void add_follow(char follow, char variable) {
for (int i = 0; i < follow_len[variable - 'A']; i++) {
if (follows[variable - 'A'][i] == follow) { return; }
}
follows[variable - 'A'][follow_len[variable - 'A']++] = follow;
}
int parse_grammar(char *s) {
char variable = next_symbol(&s); if (variable == '$') { return 0; }
assert(variable >= 'A' && variable <= 'Z', "Variable must be a capital letter."); assert(next_symbol(&s) == '-' && next_symbol(&s) == '>', "Variable must be followed by '->'"); struct Derivation * derivation = (struct Derivation *)malloc(sizeof(struct Derivation));
struct Derivation * starting_derivation = derivation; int len = 0;
char c = next_symbol(&s); while (c != '\0') {
if (c == '|') {
derivation -> derivation[len] = '\0';
derivation -> next = (struct Derivation *)malloc(sizeof(struct Derivation)); derivation = derivation -> next;
derivation -> next = NULL; len = 0;
} else {
derivation -> derivation[len++] = c;
}
c = next_symbol(&s);
}
derivation -> derivation[len] = '\0'; add_derivations(variable, starting_derivation); return 1;
}
void add_derivations(char variable, struct Derivation * derivation) { assert(variable >= 'A' && variable <= 'Z', "Variable must be a capital letter."); if (grammar_set[variable - 'A'] == NULL) {
grammar_set[variable - 'A'] = derivation; return;
}
struct Derivation *p = grammar_set[variable - 'A']; while (p -> next != NULL) {
p = p -> next;
}
p -> next = derivation;
}
char next_symbol(char **s) {
 
while (isspace(**s)) { (*s)++; };
if (**s == '\0') { return '\0'; } return *(*s)++;
}
void reset() {
for (int i = 0; i < 26; i++) { grammar_set[i] = NULL; first_len[i] = 0;
follow_len[i] = 0;
is_being_searched[i] = 0;
}
}
void assert(int expr, char * message)
 { 
    if (expr) { return; }
if (message != NULL) { printf("%s\n", message); 
} 
exit(1);
}
/*
Enter Grammars (start with $ to stop): S -> Ab | Bb
A -> Cd B -> bC
C -> c |
$

First(A): c, d,
Follow(A): b,
First(B): b,
Follow(B): b,
First(C): c, ,
Follow(C): d, First(S): c, d, b, Follow(S):
*/
