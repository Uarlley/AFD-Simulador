#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct t_transition{
    int from;
    int to;
    char character;
}transition;

char* alphabet; //alphabet definition
int alphabetSize; //alphabet size
transition *transitions; //transitions between states
int numTransitions; //number of transitions
int *terminalStates; //terminal states
int numTerminalStates; // number of terminal states

bool isTerminal(int state){
    //returns whether the state is terminal or not
    for(int i = 0; i < numTerminalStates; i++){
        if(state == terminalStates[i]) return true;
    }
    return false;
}

bool transitsToTerminal(int state){
    //checks if the state transits to a terminal state through lambda
    for(int i = 0; i < numTransitions; i++){
        if(transitions[i].from == state && transitions[i].character == '-' && isTerminal(transitions[i].to)) 
            return true;
    }
    return false;
}

bool isInAlphabet(char character){
    //checks if the character belongs to the alphabet
    for(int i = 0; i < alphabetSize; i++){
        if(alphabet[i] == character) return true;
    }
    return false;
}

int searchNextState(char character, int state){
    //searches for the next state using the character 
    for(int i = 0; i < numTransitions; i++){
        if(transitions[i].from == state && transitions[i].character == character) return transitions[i].to;
    }
    //returns -1 if theres no next state
    return -1;
}

bool isValid(char *expression, int currentState, int pos, int end){
    //checks if the expression is empty
    if(pos > end || expression[pos] == '-') {
        //returns whether the expression ended in a terminal state or not
         if (isTerminal(currentState) || transitsToTerminal(currentState)) return true;
         else return false;
    }
    //checks if the current character belongs to the alphabet
    if(!isInAlphabet(expression[pos])) return false;

    //changes to the next state
    int newState = searchNextState(expression[pos], currentState);
    //returns false if theres no next state
    if(newState == -1) return false;

    //makes the recursive call with the new state and expression
    return isValid(expression, newState, pos+1, end);
}

int main(){
    int states, initStateSize, i = 0, inputs;
    //reads the input list
    scanf("%d", &states);
    scanf("%d", &alphabetSize);
    alphabet = (char *)malloc((alphabetSize+1)*sizeof(char));//allocates the alphabet array
    getchar();
    
    while(i < alphabetSize){ //reads the alphabet ignoring spaces
        alphabet[i] = getchar();
        if(alphabet[i] != ' ') {
            i++;
        }
    }
    alphabet[alphabetSize] = 0;
    scanf("%d", &initStateSize);
    scanf("%d", &numTerminalStates);

    terminalStates = (int *)malloc(numTerminalStates*sizeof(int)); //allocates the array of terminal states
    for(i = 0; i < numTerminalStates; i++){
        scanf("%d", &terminalStates[i]);
    }
    scanf("%d",&numTransitions);
    getchar();
    transitions = (transition *)malloc(numTransitions*sizeof(transition)); //allocates the array of transitions
    for(i = 0; i < numTransitions; i++){ //reads the transitions ignoring spaces
        scanf("%d",&transitions[i].from);
        getchar();
        scanf("%c",&transitions[i].character);
        getchar();
        scanf("%d",&transitions[i].to);
    }
    //reads, tests and print the correct output
    scanf("%d", &inputs);
    getchar();
    for(i = 0; i < inputs; i++){
        char test[200];
        fgets(test,200,stdin);
        test[strlen(test)-1] = 0;
        if(isValid(test, 0,0,strlen(test)-1)) printf("aceita\n");
        else printf("rejeita\n");
    }
    //frees the allocated memory
    free(alphabet);
    free(transitions);
    free(terminalStates);
    return 0;
}
