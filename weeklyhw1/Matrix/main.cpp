
#include "matrix.hpp"

int main() {
    using namespace MatrixLibrary;

    // Testing constructors
    Matrix<int> mat1(3, 3, 1); // 3x3 matrix filled with 1
    Matrix<int> mat2(matrix<int>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}); // Initialize from a matrix
    Matrix<int> mat3(vector<int>{1, 2, 3}); // Initialize from a vector
    Matrix<double> mat31 = Matrix<double>::identity(5); // Identity matrix
    Matrix<int> mat4(mat2); // Copy constructor

    // Testing matrix operations
    Matrix<int> mat5 = mat2 + mat1; // Addition
    Matrix<int> mat6 = mat2 - mat1; // Subtraction
    Matrix<int> mat7 = -mat2; // Negation
    Matrix<int> mat8 = mat2 * mat2; // Element-wise multiplication
    Matrix<int> mat9 = Matrix<int>::dot(mat2, mat2); // Matrix multiplication
    Matrix<int> mat10 = mat2 + 5; // Scalar addition
    Matrix<int> mat11 = mat2 - 2; // Scalar subtraction

    // Testing determinant, inverse, and trace
    double det = mat31.determinant();
    Matrix<double> inv = mat31.inverse();
    double trace = mat31.trace();

    Matrix<int> mat12 = Matrix<int>::add(mat2, mat1); // Addition
    Matrix<int> mat13 = Matrix<int>::subtract(mat2, mat1); // Subtraction

    // Output matrices and results
    std::cout << "Matrix 1:\n" << mat1 << std::endl;
    std::cout << "Matrix 2:\n" << mat2 << std::endl;
    std::cout << "Matrix 3:\n" << mat3 << std::endl;
    std::cout << "Matrix 4 (Copy of Matrix 2):\n" << mat4 << std::endl;
    std::cout << "Matrix 5 (Matrix 2 + Matrix 1):\n" << mat5 << std::endl;
    std::cout << "Matrix 6 (Matrix 2 - Matrix 1):\n" << mat6 << std::endl;
    std::cout << "Matrix 7 (Negation of Matrix 2):\n" << mat7 << std::endl;
    std::cout << "Matrix 8 (Matrix 2 * Matrix 3 - Element-wise):\n" << mat8 << std::endl;
    std::cout << "Matrix 9 (Matrix 2 * Matrix 2 - Matrix multiplication):\n" << mat9 << std::endl;
    std::cout << "Matrix 10 (Matrix 2 + 5 - Scalar addition):\n" << mat10 << std::endl;
    std::cout << "Matrix 11 (Matrix 2 - 2 - Scalar subtraction):\n" << mat11 << std::endl;
    std::cout << "Matrix 12 (Matrix 2 - Matrix 1 - Static addition):\n" << mat12 << std::endl;
    std::cout << "Matrix 13 (Matrix 2 - Matrix 1 - Static  subtraction):\n" << mat13 << std::endl;
    std::cout << "Determinant of Matrix 31: " << det << std::endl;
    std::cout << "Inverse of Matrix 31:\n" << inv << std::endl;
    std::cout << "Inverse of Matrix 31 * Matrix 31:\n" << Matrix<double>::dot(mat31, inv) << std::endl;
    std::cout << "Trace of Matrix 2: " << trace << std::endl;

    return 0;
}




