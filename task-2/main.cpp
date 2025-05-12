#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;

// Grammar Rule in CNF
struct CNFGrammar {
    set<string> nonTerminals;
    set<char> terminals;
    string startSymbol;
    map<string, vector<pair<string, string>>> binaryRules; // A -> BC
    map<string, vector<char>> terminalRules; // A -> a

    // Function to add binary rule A -> BC
    void addBinaryRule(const string& A, const string& B, const string& C) {
        nonTerminals.insert(A);
        nonTerminals.insert(B);
        nonTerminals.insert(C);
        binaryRules[A].push_back({B, C});
    }

    // Function to add terminal rule A -> a
    void addTerminalRule(const string& A, char a) {
        nonTerminals.insert(A);
        terminals.insert(a);
        terminalRules[A].push_back(a);
    }
};

// CYK Algorithm to check string membership
bool cyk(const CNFGrammar& grammar, const string& w) {
    int n = w.size();
    vector<vector<set<string>>> table(n, vector<set<string>>(n));

    // Fill in the table for substrings of length 1
    for (int i = 0; i < n; ++i) {
        for (const auto& [A, chars] : grammar.terminalRules) {
            for (char a : chars) {
                if (a == w[i]) {
                    table[i][i].insert(A);
                }
            }
        }
    }

    // Fill in the table for substrings of length 2 to n
    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            int j = i + l - 1;
            for (int k = i; k < j; ++k) {
                for (const auto& [A, rules] : grammar.binaryRules) {
                    for (const auto& [B, C] : rules) {
                        if (table[i][k].count(B) && table[k + 1][j].count(C)) {
                            table[i][j].insert(A);
                        }
                    }
                }
            }
        }
    }

    // Check if start symbol can derive the string
    return table[0][n - 1].count(grammar.startSymbol);
}

int main() {
    CNFGrammar grammar;
    grammar.startSymbol = "S";

    cout << "Enter number of terminal rules (A -> a): ";
    int t;
    cin >> t;
    cout << "Enter rules in format A a:\n";
    for (int i = 0; i < t; ++i) {
        string A;
        char a;
        cin >> A >> a;
        grammar.addTerminalRule(A, a);
    }

    cout << "Enter number of binary rules (A -> BC): ";
    int b;
    cin >> b;
    cout << "Enter rules in format A B C:\n";
    for (int i = 0; i < b; ++i) {
        string A, B, C;
        cin >> A >> B >> C;
        grammar.addBinaryRule(A, B, C);
    }

    cout << "Enter string to test: ";
    string w;
    cin >> w;

    if (cyk(grammar, w)) {
        cout << "String belongs to the language." << endl;
    } else {
        cout << "String does NOT belong to the language." << endl;
    }

    return 0;
}
