#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

// DFA
struct DFA {
    int numStates;
    int startState;
    set<int> acceptStates;
    map<pair<int, char>, int> transitions; // key: (state, input) => value: next state

   
    int move(int state, char symbol) const {
        auto it = transitions.find({state, symbol});
        if (it != transitions.end()) return it->second;
        return -1; // invalid transition
    }

    bool isAccept(int state) const {
        return acceptStates.count(state) > 0;
    }
};


bool areEquivalent(const DFA& dfa1, const DFA& dfa2, const set<char>& alphabet) {
    queue<pair<int, int>> q;
    set<pair<int, int>> visited;

    q.push({dfa1.startState, dfa2.startState});
    visited.insert({dfa1.startState, dfa2.startState});

    while (!q.empty()) {
        auto [state1, state2] = q.front(); q.pop();

        // Check if accepting status mismatches
        bool accept1 = dfa1.isAccept(state1);
        bool accept2 = dfa2.isAccept(state2);
        if (accept1 != accept2) {
            return false; // They are distinguishable
        }

        for (char symbol : alphabet) {
            int next1 = dfa1.move(state1, symbol);
            int next2 = dfa2.move(state2, symbol);
            if (next1 == -1 || next2 == -1) continue; // skip invalid transitions

            if (visited.count({next1, next2}) == 0) {
                visited.insert({next1, next2});
                q.push({next1, next2});
            }
        }
    }

    return true; 
}

// Function to input a DFA from user
void inputDFA(DFA& dfa, set<char>& alphabet) {
    cout << "Enter number of states: ";
    cin >> dfa.numStates;

    cout << "Enter start state: ";
    cin >> dfa.startState;

    int numAccept;
    cout << "Enter number of accepting states: ";
    cin >> numAccept;
    cout << "Enter accepting states: ";
    for (int i = 0; i < numAccept; ++i) {
        int state;
        cin >> state;
        dfa.acceptStates.insert(state);
    }

    int numTransitions;
    cout << "Enter number of transitions: ";
    cin >> numTransitions;
    cout << "Enter transitions in format: from_state input_symbol to_state\n";
    for (int i = 0; i < numTransitions; ++i) {
        int from, to;
        char symbol;
        cin >> from >> symbol >> to;
        dfa.transitions[{from, symbol}] = to;
        alphabet.insert(symbol);
    }
}

int main() {
    DFA dfa1, dfa2;
    set<char> alphabet;

    cout << "Enter DFA 1:" << endl;
    inputDFA(dfa1, alphabet);

    cout << "\nEnter DFA 2:" << endl;
    inputDFA(dfa2, alphabet);

    if (areEquivalent(dfa1, dfa2, alphabet)) {
        cout << "\nThe DFAs are equivalent." << endl;
    } else {
        cout << "\nThe DFAs are NOT equivalent." << endl;
    }

    return 0;
}
