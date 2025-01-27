# Polynomial Calculator

This C++ project is developed as part of the **Introduction to Programming** course at the **Faculty of Mathematics and Informatics, Sofia University**. It is a polynomial calculator capable of handling polynomials with rational coefficients, providing a wide range of mathematical operations and functionalities.

## Features

The polynomial calculator supports the following operations:

1. **Addition of Polynomials**  
   \( P(x) + Q(x) \)
   
2. **Subtraction of Polynomials**  
   \( P(x) - Q(x) \)
   
3. **Multiplication of Polynomials**  
   \( P(x) \cdot Q(x) \)
   
4. **Division of Polynomials**  
   - \( P(x) / Q(x) \), where \( Q(x) \neq 0 \) and \( \text{deg}(P(x)) \geq \text{deg}(Q(x)) \).  
   - Calculates both the **quotient** and **remainder** of the division.
   
5. **Multiplication of a Polynomial by a Rational Number**

6. **Evaluation of a Polynomial**  
   - Evaluate \( P(x) \) for a given rational number \( x \).

7. **GCD (Greatest Common Divisor) of Two Polynomials**  
   - Computed using the **Euclidean algorithm**.

8. **Vieta's Formulas**  
   - Analyze the relationships between the roots and coefficients of a polynomial.

9. **Representation of a Polynomial in Terms of Powers of \( (x + a) \)**

10. **Factorization of Polynomials**  
    - If a polynomial is factorable, extract all **rational roots**.

## Input and Interaction

Users can input polynomials with rational coefficients and perform various operations using an intuitive interface. The calculator is designed to be robust and efficient, making it a valuable tool for exploring polynomial arithmetic and analysis.

## Example Functionalities

### Arithmetic Operations:
- **Addition:** \( P(x) = 2x^2 + 3x + 1, Q(x) = x^2 - x + 2 \)  
  Result: \( P(x) + Q(x) = 3x^2 + 2x + 3 \)

- **Multiplication by a Rational Number:**  
  \( P(x) = x^2 + x, k = \frac{1}{2} \)  
  Result: \( P(x) \cdot k = \frac{1}{2}x^2 + \frac{1}{2}x \)

### Advanced Features:
- **Division:** \( P(x) = x^3 + 2x^2 + x + 1, Q(x) = x + 1 \)  
  Quotient: \( x^2 + x + 1 \)  
  Remainder: \( 0 \)

- **Factorization:**  
  \( P(x) = x^2 - 3x + 2 \)  
  Roots: \( x = 1, x = 2 \)  
  Factorized form: \( P(x) = (x - 1)(x - 2) \)

## How to Run

1. Clone the repository:  
   ```bash
   git clone https://github.com/yourusername/polynomial-calculator.git
   ```
2. Compile the code using a C++ compiler (e.g., `g++`):  
   ```bash
   g++ -o polynomial_calculator polynomial_calculator.cpp
   ```
3. Run the executable:  
   ```bash
   ./polynomial_calculator
   ```

## Future Improvements

- Support for complex coefficients.
- Graphical user interface (GUI) for better interaction.
- Extended factorization methods for irreducible polynomials.

## License

This project is licensed under the [MIT License](LICENSE).

---
