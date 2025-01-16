#include <iostream>
#include <vector>

using namespace std;

// Function to compute the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to simplify a fraction
void simplify(pair<int, int>& fraction) {
    int commonDivisor = gcd(fraction.first, fraction.second);
    fraction.first /= commonDivisor;
    fraction.second /= commonDivisor;

    if (fraction.second < 0) {  // Ensure denominator is positive
        fraction.first = -fraction.first;
        fraction.second = -fraction.second;
    }
}

// Function to add two rational numbers
pair<int, int> addRational(const pair<int, int>& r1, const pair<int, int>& r2) {
    int numerator = r1.first * r2.second + r2.first * r1.second;
    int denominator = r1.second * r2.second;
    pair<int, int> result = { numerator, denominator };
    simplify(result);
    return result;
}

// Subtract two rational numbers
pair<int, int> subtractRational(const pair<int, int>& r1, const pair<int, int>& r2) {
    int numerator = r1.first * r2.second - r2.first * r1.second;
    int denominator = r1.second * r2.second;
    pair<int, int> result = { numerator, denominator };
    simplify(result);
    return result;
}

// Function to input a polynomial
void inputPolynomial(vector<pair<int, int>>& poly) {
    int degree;
    cout << "Enter the degree of your polynomial >>  ";
    cin >> degree;

    poly.resize(degree + 1);
    for (int i = degree; i >= 0; --i) {
        cout << "Enter coefficient before x^" << i << ">> ";
        int numerator, denominator = 1;
        char slash;

        cin >> numerator;  // Always read numerator
        if (cin.peek() == '/') {
            cin >> slash >> denominator;  // Read '/' and denominator if present
        }

        poly[i] = { numerator, denominator };
        simplify(poly[i]);
    }
}

// Function to display a polynomial
void displayPolynomial(const vector<pair<int, int>>& poly) {
    bool firstTerm = true;

    for (int i = poly.size() - 1; i >= 0; --i) {
        if (poly[i].first == 0) continue;

        if (!firstTerm && poly[i].first > 0) {
            cout << "+";
        }

        if (poly[i].second == 1) {
            cout << poly[i].first;
        }
        else {
            cout << poly[i].first << "/" << poly[i].second;
        }

        if (i > 0) cout << "x";
        if (i > 1) cout << "^" << i;

        firstTerm = false;
    }

    if (firstTerm) {
        cout << "0";  // if no things were printed, polynomial is 0
    }

    cout << endl;
}
// Perform addition or subtraction on two polynomials
vector<pair<int, int>> performPolynomialOperation(
    const vector<pair<int, int>>& p1,
    const vector<pair<int, int>>& p2,
    pair<int, int>(*operation)(const pair<int, int>&, const pair<int, int>&)) {

    vector<pair<int, int>> result;
    size_t maxSize = max(p1.size(), p2.size());

    for (size_t i = 0; i < maxSize; ++i) {
        int numerator1 = (i < p1.size()) ? p1[i].first : 0;
        int denominator1 = (i < p1.size()) ? p1[i].second : 1;

        int numerator2 = (i < p2.size()) ? p2[i].first : 0;
        int denominator2 = (i < p2.size()) ? p2[i].second : 1;

        pair<int, int> term1 = { numerator1, denominator1 };
        pair<int, int> term2 = { numerator2, denominator2 };
        result.push_back(operation(term1, term2));
    }

    return result;
}

// Add two polynomials
vector<pair<int, int>> addPolynomials(const vector<pair<int, int>>& p1, const vector<pair<int, int>>& p2) {
    return performPolynomialOperation(p1, p2, addRational);
}

// Subtract two polynomials
vector<pair<int, int>> subtractPolynomials(const vector<pair<int, int>>& p1, const vector<pair<int, int>>& p2) {
    return performPolynomialOperation(p1, p2, subtractRational);
}

// Input and display a polynomial
vector<pair<int, int>> inputAndDisplayPolynomial(const string& polyName) {
    vector<pair<int, int>> poly;
    cout << "Enter Polynomial " << polyName << "\n";
    inputPolynomial(poly);
    cout << polyName << " = ";
    displayPolynomial(poly);
    return poly;
}

// Perform and display a polynomial operation
void performAndDisplayOperation(const string& operationName,
    const vector<pair<int, int>>& poly1,
    const vector<pair<int, int>>& poly2,
    vector<pair<int, int>>(*operation)(const vector<pair<int, int>>&, const vector<pair<int, int>>&)) {
    cout << "P(x) " << operationName << " Q(x) = ";
    vector<pair<int, int>> result = operation(poly1, poly2);
    displayPolynomial(result);
}

int main() {
    int numberOfChoice;
    cout << "Welcome to Polynomial Calculator - ";
    cout << "a mini project intended to work with polynomials with rational coefficients." << endl;

    while (true) {
        cout << "Choose one of the following functionalities:" << endl;
        cout << "1) Add polynomials" << endl;
        cout << "2) Subtract polynomials" << endl;
        cout << "3) Multiply polynomials" << endl;
        cout << "4) Divide polynomials" << endl;
        cout << "5) Multiply polynomial by scalar" << endl;
        cout << "6) Find value of polynomial at a given number" << endl;
        cout << "7) Find GCD of two polynomials" << endl;
        cout << "8) Display Vieta's formulas for a given polynomial" << endl;
        cout << "9) Represent a polynomial in powers of (x+a)" << endl;
        cout << "10) Factor polynomial and find its rational roots" << endl;
        cout << "11) Quit program" << endl;
        cout << "Enter your option: " << endl;

        cin >> numberOfChoice;
        if (numberOfChoice == 11) {
            cout << "I hope i helped, have a nice day!" << endl;
            break;
        }
        switch (numberOfChoice) {
        case 1: {
            // Input Polynomials
            vector<pair<int, int>> polyP = inputAndDisplayPolynomial("P(x) ");
            vector<pair<int, int>> polyQ = inputAndDisplayPolynomial("Q(x) ");

            // Perform and display addition
            performAndDisplayOperation("+", polyP, polyQ, addPolynomials);
        }
              break;
        case 2: {
            vector<pair<int, int>> polyP = inputAndDisplayPolynomial("P(x) ");
            vector<pair<int, int>> polyQ = inputAndDisplayPolynomial("Q(x) ");

            performAndDisplayOperation("-", polyP, polyQ, subtractPolynomials); 
           

        }
              break;

        default:
            cout << "Invalid input. Try again!" << endl;
        }
    }

    return 0;
}
