# Implementation of C++ Structures and Classes

In this assignment, I successfully implemented three distinct components: Point structure, Calculator class, and Matrix class, showcasing my proficiency in C++ programming. Each component serves specific functionalities and follows best coding practices.

  # 1- Point Structure:
       
• Designed a Point structure using C++ structs with attributes x, y, and z as float.
       
• Implemented functions:

           • zero_distance(): Calculates the distance to the origin (0, 0, 0).
           • distance(): Computes the distance between two Point instances.
           • compare(): Determines which Point is further from the origin.
           • region(): Identifies the region of the Point in 3D space.
           • is_in_same_region(): Verifies whether two Points are in the same region.

  # 2- Calculator:
       
• Created a basic Calculator class with the following methods:

           • addition()
           • subtraction()
           • multiplication()
           • division()
           • square()
           • exponentiation()
           • modulus()
       
• Implemented error handling for invalid user inputs and provided multiple calculation capabilities within one session.
       
• Utilized throw-catch structures for robust error handling.

  # 3- Matrix:
       
• Developed a functional Matrix class using std::vector for implementing operations.
       
• Implemented methods for matrix operations:

           • constructor: Constructs a matrix with specified dimensions and entities, with default for zero matrix.
           • inverse(): Computes the inverse for 3x3 matrices.
           • trace(): Calculates the trace of the matrix.
           • determinant(): Computes the determinant for 3x3 matrices.
           • transpose(): Transposes the matrix.
           • add(), subtract(): Performs addition and subtraction.
           • neg(): Negates the matrix.
           • multiply(), dot(): Handles pairwise and dot multiplication.
           • magnitude(): Computes the magnitude of the matrix.
           • zeroes, ones, identity matrix creators: Constructs specific matrices.
       
• Encapsulated the matrix as a private attribute and employed const keyword and pass by reference for optimization.

This assignment reflects my proficiency in C++ programming, incorporating various concepts such as structs, classes, error handling, and object-oriented design principles.
