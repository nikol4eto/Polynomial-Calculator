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

// Function to compute the least common divisor
// LCM formula: (a * b) / GCD(a, b)
int lcm(int a, int b) {
    return abs(a * b) / gcd(a, b);
}

// Function to simplify a fraction
void simplify(pair < int, int >& fraction) {
    int commonDivisor = gcd(fraction.first, fraction.second);
    fraction.first /= commonDivisor;
    fraction.second /= commonDivisor;

    if (fraction.second < 0) { // Ensure denominator is positive
        fraction.first = -fraction.first;
        fraction.second = -fraction.second;
    }
}

// Function to add two rational numbers
pair < int, int > addRational(const pair < int, int >& r1,
    const pair < int, int >& r2) {
    int numerator = r1.first * r2.second + r2.first * r1.second;
    int denominator = r1.second * r2.second;
    pair < int, int > result = {
        numerator,
        denominator
    };
    simplify(result);
    return result;
}

// Subtract two rational numbers
pair < int, int > subtractRational(const pair < int, int >& r1,
    const pair < int, int >& r2) {
    int numerator = r1.first * r2.second - r2.first * r1.second;
    int denominator = r1.second * r2.second;
    pair < int, int > result = {
        numerator,
        denominator
    };
    simplify(result);
    return result;
}

// Function to add two fractions represented as pairs
pair < int, int > addFractions(pair < int, int > a, pair < int, int > b) {
    int lcm_denom = lcm(a.second, b.second);
    int new_num = a.first * (lcm_denom / a.second) + b.first * (lcm_denom / b.second);
    return {
        new_num,
        lcm_denom
    };
}

// Function to subtract two fractions represented as pairs
pair < int, int > subtractFractions(pair < int, int > a, pair < int, int > b) {
    int lcm_denom = lcm(a.second, b.second);
    int new_num = a.first * (lcm_denom / a.second) - b.first * (lcm_denom / b.second);
    return {
        new_num,
        lcm_denom
    };
}

// Function to multiply two fractions
pair < int, int > multiplyFractions(pair < int, int > a, pair < int, int > b) {
    return {
        a.first * b.first,
        a.second * b.second
    };
}

// Function to divide two fractions
pair < int, int > divideFractions(pair < int, int > a, pair < int, int > b) {
    return {
        a.first * b.second,
        a.second * b.first
    };
}

// Function to input a polynomial
void inputPolynomial(vector < pair < int, int >>& poly) {
    int degree;
    cout << "Enter the degree of your polynomial >>  ";
    cin >> degree;

    poly.resize(degree + 1);
    for (int i = degree; i >= 0; --i) {
        cout << "Enter coefficient before x^" << i << ">> ";
        int numerator, denominator = 1;
        char slash;

        cin >> numerator; // Always read numerator
        if (cin.peek() == '/') {
            cin >> slash >> denominator; // Read '/' and denominator if present
        }

        poly[i] = {
            numerator,
            denominator
        };
        simplify(poly[i]);
    }
}

// Function to display a polynomial
void displayPolynomial(const vector < pair < int, int >>& poly) {
    bool firstTerm = true;

    for (int i = poly.size() - 1; i >= 0; --i) {
        if (poly[i].first == 0)
            continue;

        if (!firstTerm && poly[i].first > 0) {
            cout << "+";
        }

        if (poly[i].second == 1) {
            cout << poly[i].first;
        }
        else {
            cout << poly[i].first << "/" << poly[i].second;
        }

        if (i > 0)
            cout << "x";
        if (i > 1)
            cout << "^" << i;

        firstTerm = false;
    }

    if (firstTerm) {
        cout << "0"; // if no things were printed, polynomial is 0
    }

    cout << endl;
}

// Input and display a polynomial
// The polynoms are inputed in desending order but saved as vector in assending order of deg
vector < pair < int, int >> inputAndDisplayPolynomial(const string& polyName) {
    vector < pair < int, int >> poly;
    cout << "Enter Polynomial " << polyName << "\n";
    inputPolynomial(poly);
    cout << polyName << " = ";
    displayPolynomial(poly);
    return poly;
}

pair < int, int > inputFraction() {
    pair < int, int > number;
    cout << "Enter a Number >>  ";
    int numerator, denominator = 1;
    char slash;

    cin >> numerator; // Always read numerator
    if (cin.peek() == '/') {
        cin >> slash >> denominator; // Read '/' and denominator if present
    }
    number = {
        numerator,
        denominator
    };
    return number;
}

void dispalyFraction(pair < int, int > result) {
    cout << result.first << "/" << result.second << endl;
}

bool isZeroPolynomial(const vector < pair < int, int >>& poly) {
    if (poly.empty()) {
        return true;
    }

    for (const auto& term : poly) {
        if (term.first != 0) {
            return false;
        }
    }

    return true;
}

// Perform addition or subtraction on two polynomials
vector < pair < int, int >> performPolynomialOperation(
    const vector < pair < int, int >>& p1,
    const vector < pair < int, int >>& p2,
    pair < int, int >(*operation)(const pair < int, int >&,
        const pair < int, int >&)) {

    vector < pair < int, int >> result;
    size_t maxSize = max(p1.size(), p2.size());

    for (size_t i = 0; i < maxSize; ++i) {
        int numerator1 = (i < p1.size()) ? p1[i].first : 0;
        int denominator1 = (i < p1.size()) ? p1[i].second : 1;

        int numerator2 = (i < p2.size()) ? p2[i].first : 0;
        int denominator2 = (i < p2.size()) ? p2[i].second : 1;

        pair < int, int > term1 = {
            numerator1,
            denominator1
        };
        pair < int, int > term2 = {
            numerator2,
            denominator2
        };
        result.push_back(operation(term1, term2));
    }

    return result;
}

vector < pair < int, int >> multiplyPolynomials(const vector < pair < int, int >>& p1,
    const vector < pair < int, int >>& p2) {
    size_t degree1 = p1.size();
    size_t degree2 = p2.size();
    vector < pair < int, int >> result(degree1 + degree2 - 1, { 0, 1 }); // Initialize result with 0s

    for (size_t i = 0; i < degree1; ++i) {
        for (size_t j = 0; j < degree2; ++j) {
            int numerator = p1[i].first * p2[j].first;
            int denominator = p1[i].second * p2[j].second;

            // Add to the existing term in the result
            pair < int, int > term = {
                numerator,
                denominator
            };
            result[i + j] = addRational(result[i + j], term);
        }
    }
    return result;
}

pair < vector < pair < int, int >>, vector < pair < int, int >>> dividePolynomials(
    vector < pair < int, int >> numinator,
    vector < pair < int, int >> denominator
) {
    size_t degNum = numinator.size() - 1;
    if (denominator.empty()) {
        cout << "Denominator cannot be zero.";
        return {};
    }

    size_t degDen = denominator.size() - 1;
    if (degNum < degDen) {
        cout << "Degree of numerator must be greater than or equal to the degree of denominator." << endl;
        return {};
    }

    vector < pair < int, int >> quotient(degNum - degDen + 1, { 0, 0 });
    vector < pair < int, int >> remainder = numinator;

    for (int i = degNum; i >= degDen; --i) {
        if (remainder[i].first != 0) {
            pair < int, int > coeffQuotient = divideFractions(remainder[i], denominator[degDen]);
            int degreeQuotient = i - degDen;

            quotient[degreeQuotient] = coeffQuotient;

            for (int j = degDen; j >= 0; --j) {
                int remainderIndex = i - (degDen - j);
                remainder[remainderIndex] = subtractFractions(
                    remainder[remainderIndex],
                    multiplyFractions(coeffQuotient, denominator[j]));
            }
        }
    }
    return {
        quotient,
        remainder
    };
}

void evaluatePolynomial() {
    vector < pair < int, int >> poly = inputAndDisplayPolynomial("P(x) ");
    pair < int, int > x = inputFraction();

    pair < int, int > result = { 0, 1 };

    for (int i = poly.size() - 1; i >= 0; --i) {
        pair < int, int > coeff = poly[i];
        pair < int, int > term = {
            coeff.first,
            coeff.second
        };

        pair < int, int > x_pow = { 1, 1 };
        for (int j = 0; j < i; ++j) {
            x_pow.first *= x.first;
            x_pow.second *= x.second;
        }

        term.first *= x_pow.first;
        term.second *= x_pow.second;

        int gcd_val = gcd(term.first, term.second);
        term.first /= gcd_val;
        term.second /= gcd_val;

        result.first = result.first * term.second + result.second * term.first;
        result.second *= term.second;

        gcd_val = gcd(result.first, result.second);
        result.first /= gcd_val;
        result.second /= gcd_val;
    }
    simplify(result);
    dispalyFraction(x);
    dispalyFraction(result);
}

void gcdPolynomials() {
    vector < pair < int, int >> poly1 = inputAndDisplayPolynomial("P(x) ");
    vector < pair < int, int >> poly2 = inputAndDisplayPolynomial("Q(x) ");

    while (!isZeroPolynomial(poly2)) {
        auto division = dividePolynomials(poly1, poly2);
        poly1 = poly2;
        poly2 = division.second;
    }

    cout << "gcd (P(x), Q(x)) = ";
    displayPolynomial(poly1);
}

// Function to calculate and print the sum of the roots (x1 + x2 + ... + xn)
void calculateAndPrintSumOfRoots(const vector < pair < int, int >>& poly, int deg) {
    for (int i = 0; i < deg; ++i) {
        cout << "x" << i + 1;
        if (i < deg - 1) {
            cout << " + ";
        }
    }

    pair < int, int > sumOfRoots = divideFractions({
            -poly[deg - 1].first,
            poly[deg - 1].second
        },
        poly[deg]
    );
    simplify(sumOfRoots);
    cout << " = " << sumOfRoots.first << "/" << sumOfRoots.second << endl;
}

// Function to calculate and print the sum of the products of the roots taken two at a time (x1x2 + x1x3 + ... + x(n-1)xn)
void calculateAndPrintSumOfProductsTwoAtATime(const vector < pair < int, int >>& poly, int deg) {
    for (int i = 0; i < deg; ++i) {
        for (int j = i + 1; j < deg; ++j) {
            cout << "x" << i + 1 << "x" << j + 1;
            if (i < deg - 2) {
                cout << " + ";
            }
        }
    }

    pair < int, int > sumOfProductsTwoAtATime = divideFractions(
        poly[deg - 2],
        poly[deg]
    );
    simplify(sumOfProductsTwoAtATime);
    cout << " = " <<
        sumOfProductsTwoAtATime.first << "/" << sumOfProductsTwoAtATime.second << endl;
}

// Function to calculate and print the sum of the products of the roots taken three at a time (x1x2x3 + x1x2x4 + ...)
void calculateAndPrintSumOfProductsThreeAtATime(const vector < pair < int, int >>& poly, int deg) {
    for (int i = 0; i < deg; ++i) {
        for (int j = i + 1; j < deg; ++j) {
            for (int k = j + 1; k < deg; ++k) {
                cout << "x" << i + 1 << "x" << j + 1 << "x" << k + 1;
                if (i < deg - 3) {
                    cout << " + ";
                }
            }
        }
    }

    pair < int, int > sumOfProductsThreeAtATime = divideFractions({
            -poly[deg - 3].first,
            poly[deg - 3].second
        },
        poly[deg]
    );
    simplify(sumOfProductsThreeAtATime);
    cout << " = " <<
        sumOfProductsThreeAtATime.first << "/" << sumOfProductsThreeAtATime.second << endl;
}

// Function to calculate and print the product of all the roots (x1x2x3...xn)
void calculateAndPrintProductOfRoots(const vector < pair < int, int >>& poly, int deg) {
    for (int i = 0; i < deg; ++i) {
        cout << "x" << i + 1;
        if (i < deg - 1) {
            cout << " * ";
        }
    }

    pair < int, int > productOfRoots = divideFractions({
            poly[0].first,
            poly[0].second
        },
        poly[deg]
    );

    if (deg % 2 == 1) {
        productOfRoots.first = -productOfRoots.first;
    }
    simplify(productOfRoots);
    cout << " = " << productOfRoots.first << "/" << productOfRoots.second << endl;
}

// Main function to calculate and print all Viet's formulas
void vietFormulas() {
    const vector < pair < int, int >>& poly = inputAndDisplayPolynomial("P(x) ");
    int deg = poly.size() - 1;

    if (deg < 1) {
        cout << "Polynomial degree is too low to compute Viet's formulas!" << endl;
        return;
    }

    calculateAndPrintSumOfRoots(poly, deg);

    if (deg >= 2) {
        calculateAndPrintSumOfProductsTwoAtATime(poly, deg);
    }

    if (deg >= 3) {
        calculateAndPrintSumOfProductsThreeAtATime(poly, deg);
    }

    calculateAndPrintProductOfRoots(poly, deg);
}

// Add two polynomials
vector < pair < int, int >> addPolynomials(const vector < pair < int, int >>& p1,
    const vector < pair < int, int >>& p2) {
    return performPolynomialOperation(p1, p2, addRational);
}

// Subtract two polynomials
vector < pair < int, int >> subtractPolynomials(const vector < pair < int, int >>& p1,
    const vector < pair < int, int >>& p2) {
    return performPolynomialOperation(p1, p2, subtractRational);
}

void dividePolynomialsWithInput() {
    // Get the polynomials
    vector < pair < int, int >> numerator = inputAndDisplayPolynomial("P(x)");
    vector < pair < int, int >> denominator = inputAndDisplayPolynomial("Q(x)");

    // Divide the polynomials
    auto result = dividePolynomials(numerator, denominator);

    // Printing the Quotient and Remainder
    cout << "Quotient: ";
    displayPolynomial(result.first);
    cout << "Remainder: ";
    displayPolynomial(result.second);
}

// Perform and display a polynomial operation
void performAndDisplayOperation(
    const string& operationName,
    vector < pair < int, int >>(*operation)(const vector < pair < int, int >>&,
        const vector < pair < int, int >>&)) {
    // Input Polynomials
    vector < pair < int, int >> poly1 = inputAndDisplayPolynomial("P(x) ");
    vector < pair < int, int >> poly2 = inputAndDisplayPolynomial("Q(x) ");

    cout << "P(x) " << operationName << " Q(x) = ";
    vector < pair < int, int >> result = operation(poly1, poly2);
    displayPolynomial(result);
}

// Function to multiply a polynomial by a scalar
vector < pair < int, int >> multiplyByScalar(const vector < pair < int, int >>& poly,
    const pair < int, int >& scalar) {
    vector < pair < int, int >> result;

    for (const auto& term : poly) {
        int numerator = term.first * scalar.first;
        int denominator = term.second * scalar.second;

        pair < int, int > newTerm = {
            numerator,
            denominator
        };
        simplify(newTerm);
        result.push_back(newTerm);
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
        switch (numberOfChoice) {
        case 1: {
            // Perform and display addition
            performAndDisplayOperation("+", addPolynomials);
        }
              break;

        case 2: {
            // Perform and display subtraction
            performAndDisplayOperation("-", subtractPolynomials);
        }
              break;

        case 3: {
            vector < pair < int, int >> polyP = inputAndDisplayPolynomial("P(x) ");
            vector < pair < int, int >> polyQ = inputAndDisplayPolynomial("Q(x) ");

            cout << "P(x) * Q(x) = ";
            vector < pair < int, int >> result = multiplyPolynomials(polyP, polyQ);
            displayPolynomial(result);
            cout << endl; // Add blank line after the operation
        }
              break;

        case 4:
            // Perform and display the quotient and the remainder of the division.
            dividePolynomialsWithInput();
            break;

        case 5: {
            vector < pair < int, int >> polyP = inputAndDisplayPolynomial("P(x) ");

            cout << "Enter scalar (format: numerator/denominator or just numerator)>> ";
            int numerator, denominator = 1;
            char slash;
            cin >> numerator;
            if (cin.peek() == '/') {
                cin >> slash >> denominator;
            }

            pair < int, int > scalar = {
                numerator,
                denominator
            };
            simplify(scalar);

            vector < pair < int, int >> result = multiplyByScalar(polyP, scalar);
            cout << "Result: ";
            displayPolynomial(result);
            cout << endl;
        }
              break;

        case 6:
            // Calculates the value of a polynomial for a given rational number
            evaluatePolynomial();
            break;

        case 7:
            //
            gcdPolynomials();
            break;

        case 8:
            vietFormulas();
            break;

            // Moved the if to the switch and added an early return instead of breaking the while loop and then returning
        case 11: {
            cout << "I hope i helped, have a nice day!" << endl;
            return 0;
        }
               break;

        default:
            cout << "Invalid input. Try again!" << endl;
        }
    }

    return 0;
}