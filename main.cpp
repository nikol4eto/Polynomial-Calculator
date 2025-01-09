#include <iostream>
#include <vector>

using namespace std;
//FIRST STEP DONE
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


// Function to input a polynomial
void inputPolynomial(vector<pair<int, int>>& poly) {
    int degree;
    cout << "Enter the degree of your polynomial >> ";
    cin >> degree;

    poly.resize(degree + 1);
    for (int i = degree; i >= 0; --i) {
        cout << "Enter coefficient before x^" << i;
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

// Function to add two polynomials
vector<pair<int, int>> addPolynomials(const vector<pair<int, int>>& p1, const vector<pair<int, int>>& p2) {
    vector<pair<int, int>> result;

    size_t maxSize = max(p1.size(), p2.size());
    for (size_t i = 0; i < maxSize; ++i) {
        int numerator1 = (i < p1.size()) ? p1[i].first : 0;
        int denominator1 = (i < p1.size()) ? p1[i].second : 1;

        int numerator2 = (i < p2.size()) ? p2[i].first : 0;
        int denominator2 = (i < p2.size()) ? p2[i].second : 1;

        // Rational numbers!
        int numerator = numerator1 * denominator2 + numerator2 * denominator1;
        int denominator = denominator1 * denominator2;

        // the result as a simplified pair
        result.push_back({ numerator, denominator });
    }

    return result;
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

            // Input Polynomial P(x)
            vector<pair<int, int>> polyP;
            cout << "Enter Polynomial P(x)\n";
            inputPolynomial(polyP);
            cout << "P(x) = ";
            displayPolynomial(polyP);

            // Input Polynomial Q(x)
            vector<pair<int, int>> polyQ;
            cout << "Enter Polynomial Q(x)\n";
            inputPolynomial(polyQ);
            cout << "Q(x) = ";
            displayPolynomial(polyQ);

            // Add Polynomials
            vector<pair<int, int>> polyResult = addPolynomials(polyP, polyQ);
            cout << "P(x) + Q(x) = ";
            displayPolynomial(polyResult);
        }
              break;
        case 2: {
        
        }
              break;

        default:
            cout << "Invalid input. Try again!" << endl;
        }
    }

    return 0;
}
