#include <bits/stdc++.h>
using namespace std;


int maxTests = 50;
int minExpressionSize = 40;
int maxExpressionSize = 199;
int minStates = 3;
int maxStates = 10;
int minTransitions = 50;
int maxTransitions = 70;
int maxTerminalStates = 10;
string output = "Teste.txt";
string alphabet = "abcdef";
vector<int> terminalStates;

struct transition{
    int from;
    int to;
    char character;

    friend bool operator== (transition E1, transition E2){
        if(E1.from == E2.from && E1.character == E2.character) return true;
        return false;
    }
    friend ostream &operator<<( ostream &output, const transition &E ) {
         output << E.from << " " << E.character << " " << E.to;
         return output;
    }
};

vector<transition> transitions;
transition emptyTransition = {-1,-1,'0'};

bool isInVector(vector<auto> array, auto var){

    for( auto element : array){
        if(var == element) return true;
    }
    return false;
}

transition generateTransition(int states){
    transition T;
    T.from = rand()%states;
    T.character = alphabet[rand()%alphabet.size()];
    T.to = rand()%states;
    while(isInVector(transitions, T)){
        T.from = rand()%states;
        T.character = alphabet[rand()%alphabet.size()];
        T.to = rand()%states;
    }
    return T;
}

transition searchTerminalState(int currentState){
    transition validTransition = emptyTransition;
    for( transition T: transitions){
        if(T.from == currentState){
            if(isInVector(terminalStates, T.to)) return T;
            validTransition = T;
        }
    }
    return validTransition;
}

string searchNextCharacter(string expression, int *currentState, int expressionSize){

    for(int i = 0; i < expressionSize; i++){
        for( transition T: transitions){
            if(T.from == *currentState){
                *currentState = T.to;
                expression += T.character;
                return expression;
            }
        }
    }
    while(!isInVector(terminalStates, *currentState) && expression.size() < maxExpressionSize){
        transition newTransition = searchTerminalState(*currentState);
        if(newTransition == emptyTransition) return expression;
        *currentState = newTransition.to;
        expression += newTransition.character;
    }
    return expression;
}


string generateExpression(int currentState){

    string expression = "";
    string newExp = "";
    int expressionSize = minExpressionSize + rand()%(maxExpressionSize - minExpressionSize);
    for(int i = 0; i < expressionSize; i++){
        newExp = searchNextCharacter(expression, &currentState, expressionSize);
        if(newExp == expression) return expression;
        expression = newExp;
        random_shuffle(transitions.begin(), transitions.end());
    }
    return expression;
}

void generateTest(){
    srand(clock());
    int states = (minStates + rand()%(maxStates - minStates + 1));
    fstream file;
    file.open(output,ios::out);
    file << states << endl;
    file << alphabet.size() << " ";

    for (char character : alphabet) file << character << " ";
    file << endl;
    file << '1' << endl;

    int terminalStatesSize = 1 + rand()%(maxTerminalStates);
    file << terminalStatesSize << " ";

    for(int i = 0; i < terminalStatesSize; i++){
        int aux = rand()%(states);
        if(isInVector(terminalStates,aux)){
            i--;
        }
        else{
            terminalStates.push_back(aux);
            file << aux << " ";
        }
    }
    file << endl;
    int size = 0;
    int qntTransitions = states*alphabet.size();
    file << qntTransitions << endl;
    for(int i = 0; i < states; i++){
        for(int j = 0; j < alphabet.size(); j++){
            transitions.push_back({i, rand()%states, alphabet[j]});
            file << transitions[size] << endl;
            size++;
        }
    }


    file << maxTests << endl;
    for(int i = 0 ; i < maxTests; i++){
        file << generateExpression(0) << endl;
    }

    file.close();
}

int main(){
    generateTest();
}
