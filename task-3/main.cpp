#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Turing Machine simulator for unary strings with prime length
bool turingMachinePrime(const string& input) {
    // Check if input contains only '1's (unary alphabet)
    for (char c : input) {
        if (c != '1') return false;
    }

    int length = input.size();
    return isPrime(length);
}

int main() {
    cout << "Enter unary string (only '1's): ";
    string input;
    cin >> input;

    if (turingMachinePrime(input)) {
        cout << "Accepted: Length is prime." << endl;
    } else {
        cout << "Rejected: Length is NOT prime." << endl;
    }

    return 0;
}
