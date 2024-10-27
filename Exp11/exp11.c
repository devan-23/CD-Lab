#include <stdio.h>
#include <stdlib.h>

int nfa[256][256][256];
int dfa[256][256];
int state_set[256][256]; int is_final[256];
int dfa_is_final[256]; int state_count = 1; void reset() {
state_count = 1;
for (int i = 0; i < 256; i++) { // DEAD STATE state_set[0][i] = 0;
dfa[0][i] = 0;
}
}
int find_state(int *state, int n_states) { for (int i = 0; i < state_count; i++) {
int match_all = 1;
for (int j = 0; j < n_states; j++) { if (state[j] != state_set[i][j]) {
match_all = 0; break;
}
}
if (match_all) return i;
}
return -1;
}
void add_new_state(int *state, int n_states) { for (int i = 0; i < n_states; i++) {
state_set[state_count][i] = state[i];
dfa_is_final[state_count] = dfa_is_final[state_count] || (state[i] && is_final[i]);
}
state_count++;
}
void explore_state(int state_index, int n_states, int n_inputs) { int next_state[n_states];
for (int input_index = 0; input_index < n_inputs; input_index++) { for (int i = 0; i < n_states; i++) {
next_state[i] = 0;
}
for (int i = 0; i < n_states; i++) { if (!state_set[state_index][i]) {
continue;
}
 
for (int j = 0; j < n_states; j++) {
next_state[j] = next_state[j] || nfa[i][input_index][j];
}
}
int next_state_index = find_state(next_state, n_states); if (next_state_index == -1) {
add_new_state(next_state, n_states); next_state_index = state_count - 1;
}
dfa[state_index][input_index] = next_state_index;
}
}
int main() { reset();
int n_states, n_inputs; int starting_state;
printf("Number of states: "); scanf("%d", &n_states); printf("Number of inputs: "); scanf("%d", &n_inputs);
for (int i = 0; i < n_states; i++) {
printf("Enter 0 if q%d is not a final state: ", i); scanf("%d", &is_final[i]);
for (int j = 0; j < n_inputs; j++) {
for (int k = 0; k < n_states; k++) {
printf("Enter 0 if (q%d, i%d) => q%d is not present: ", i, j, k); scanf("%d", &nfa[i][j][k]);
}
}
}
int current_state[n_states];
for (int i = 0; i < n_states; i++) { current_state[i] = 0; } printf("Enter starting state: ");
scanf("%d", &starting_state); current_state[starting_state] = 1; add_new_state(current_state, n_states);
for (int curr_state = 1; curr_state < state_count; curr_state++) { printf("Exploring %d\n", curr_state); explore_state(curr_state, n_states, n_inputs);
}
for (int i = 0; i < state_count; i++) { for (int j = 0; j < n_inputs; j++) {
printf("(%cQ%d, I%d) => Q%d\n", dfa_is_final[i] ? '*' : ' ', i, j, dfa[i][j]);
}
}
}
/*Output
Number of states: 3
Number of inputs: 2
Enter 0 if q0 is not a final state: 0
Enter 0 if (q0, i0) => q0 is not present: 0
Enter 0 if (q0, i0) => q1 is not present: 1
Enter 0 if (q0, i0) => q2 is not present: 1
Enter 0 if (q0, i1) => q0 is not present: 0
Enter 0 if (q0, i1) => q1 is not present: 0
Enter 0 if (q0, i1) => q2 is not present: 1
Enter 0 if q1 is not a final state: 0
Enter 0 if (q1, i0) => q0 is not present: 0
Enter 0 if (q1, i0) => q1 is not present: 0
Enter 0 if (q1, i0) => q2 is not present: 1
Enter 0 if (q1, i1) => q0 is not present: 1
Enter 0 if (q1, i1) => q1 is not present: 00
Enter 0 if (q1, i1) => q2 is not present: 0
Enter 0 if q2 is not a final state: 1
Enter 0 if (q2, i0) => q0 is not present: 1
Enter 0 if (q2, i0) => q1 is not present: 0
Enter 0 if (q2, i0) => q2 is not present: 1
Enter 0 if (q2, i1) => q0 is not present: 0
Enter 0 if (q2, i1) => q1 is not present: 0
Enter 0 if (q2, i1) => q2 is not present: 0
Enter starting state: 0
Exploring 1
Exploring 2
Exploring 3
Exploring 4
Exploring 5
( Q0, I0) => Q0
( Q0, I1) => Q0
( Q1, I0) => Q2
( Q1, I1) => Q3
(*Q2, I0) => Q4
(*Q2, I1) => Q1
(*Q3, I0) => Q4
(*Q3, I1) => Q0
(*Q4, I0) => Q5
(*Q4, I1) => Q3
(*Q5, I0) => Q5
(*Q5, I1) => Q4
  */
