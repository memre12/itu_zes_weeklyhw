#include <iostream>
#include <limits>
#include <cstdint>
#include <cfloat>

constexpr int square(int x){
    return x*x;
}
auto my_area(int mylength, int mywidth) -> int{
    return mylength*mywidth;
}

int main() {
    
    
    
    // Variable combinations
    int i;
    char ch;
    unsigned char uch;
    signed char sch;
    wchar_t wch;
    short sh;
    long l;
    short int si;
    long int li;
    long long int lli;
    unsigned int ui;
    unsigned short ush;
    unsigned long ul;
    float f;
    double d;
    int32_t myInt32Variable;
    int64_t myInt64Variable;
    //char8_t m_char8; It is use in cpp2023
    char16_t m_char16;
    char32_t m_char32;

    
    std::cout << "wchar_t: " << sizeof(wch) << " bytes" << std::endl;
    //std::cout << "m_char8: " << sizeof(m_char8) << " bytes" << std::endl;
    std::cout << "m_char16: " << sizeof(m_char16) << " bytes" << std::endl;
    std::cout << "m_char32: " << sizeof(m_char32) << " bytes" << std::endl;
    std::cout << "char16_t: " << sizeof(m_char16) << " bytes" << std::endl;
    std::cout << "Size of int32_t: " << sizeof(int32_t) << " bytes" << std::endl;
    std::cout << "Size of int64_t: " << sizeof(int64_t) << " bytes" << std::endl;
    std::cout << "Sizes of variables:" << std::endl;
    std::cout << "long int: " << sizeof(li) << " bytes" << std::endl;
    std::cout << "signed char: " << sizeof(sch) << " bytes" << std::endl;
    std::cout << "unsigned char: " << sizeof(uch) << " bytes" << std::endl;
    std::cout << "long long int: " << sizeof(lli) << " bytes" << std::endl;
    std::cout << "int: " << sizeof(i) << " bytes" << std::endl;
    std::cout << "short: " << sizeof(sh) << " bytes" << std::endl;
    std::cout << "long: " << sizeof(l) << " bytes" << std::endl;
    std::cout << "unsigned int: " << sizeof(ui) << " bytes" << std::endl;
    std::cout << "unsigned short: " << sizeof(ush) << " bytes" << std::endl;
    std::cout << "unsigned long: " << sizeof(ul) << " bytes" << std::endl;
    std::cout << "float: " << sizeof(f) << " bytes" << std::endl;
    std::cout << "double: " << sizeof(d) << " bytes" << std::endl;

    // Create pointers and print sizes of pointers
    int* pi = &i;
    long long int* plli = &lli;
    long int* pli = &li;
    char* pch = &ch;
    unsigned char* puch = &uch;
    short int* psi = &si;
    short* psh = &sh;
    long* pl = &l;
    unsigned int* pui = &ui;
    unsigned short* push = &ush;
    unsigned long* pul = &ul;
    float* pf = &f;
    double* pd = &d;
    wchar_t* pwch = &wch;
    char16_t* pch16 = &m_char16;
    char32_t* pm_char32 = &m_char32;
   // char8_t* pm_char8 = &m_char8;


    std::cout << "\nSizes of pointers:" << std::endl;
    std::cout << "wchar_t*: " << sizeof(pwch) << " bytes" << std::endl;
    //std::cout << "char16_t: " << sizeof(pch16) << " bytes" << std::endl;
    std::cout << "char32_t*: " << sizeof(pm_char32) << " bytes" << std::endl;
    //std::cout << "char8_t: " << sizeof(pm_char8) << " bytes" << std::endl;
    std::cout << "long long int*: " << sizeof(plli) << " bytes" << std::endl;
    std::cout << "wchar_t*: " << sizeof(pwch) << " bytes" << std::endl;
    std::cout << "char16_t*: " << sizeof(pch16) << " bytes" << std::endl;
    std::cout << "long int*: " << sizeof(pli) << " bytes" << std::endl;
    std::cout << "char*: " << sizeof(pch) << " bytes" << std::endl;
    std::cout << "unsigned char*: " << sizeof(puch) << " bytes" << std::endl;
    std::cout << "short int*: " << sizeof(psi) << " bytes" << std::endl;
    std::cout << "short*: " << sizeof(psh) << " bytes" << std::endl;
    std::cout << "long*: " << sizeof(pl) << " bytes" << std::endl;
    std::cout << "unsigned int*: " << sizeof(pui) << " bytes" << std::endl;
    std::cout << "unsigned short*: " << sizeof(push) << " bytes" << std::endl;
    std::cout << "unsigned long*: " << sizeof(pul) << " bytes" << std::endl;
    std::cout << "float*: " << sizeof(pf) << " bytes" << std::endl;
    std::cout << "double*: " << sizeof(pd) << " bytes" << std::endl;

    // Print max and min values using std::numeric_limits
    std::cout << "\nMax and Min values:" << std::endl;
    std::cout << "char32_t: Max = " << std::numeric_limits<char32_t>::max() << ", Min = " << std::numeric_limits<char32_t>::min() << std::endl;
    //std::cout << "char16_t: Max = " << std::numeric_limits<char16_t>::max() << ", Min = " << std::numeric_limits<char16_t>::min() << std::endl;
    //std::cout << "char8_t: Max = " << std::numeric_limits<char8_t>::max() << ", Min = " << std::numeric_limits<char8_t>::min() << std::endl;
    std::cout << "int32_t: Max = " << std::numeric_limits<int32_t>::max() << ", Min = " << std::numeric_limits<int32_t>::min() << std::endl;
    std::cout << "int64_t: Max = " << std::numeric_limits<int64_t>::max() << ", Min = " << std::numeric_limits<int64_t>::min() << std::endl;
    std::cout << "int: Max = " << std::numeric_limits<int>::max() << ", Min = " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "short: Max = " << std::numeric_limits<short>::max() << ", Min = " << std::numeric_limits<short>::min() << std::endl;
    std::cout << "long: Max = " << std::numeric_limits<long>::max() << ", Min = " << std::numeric_limits<long>::min() << std::endl;
    std::cout << "wchar_t: Max = " << std::numeric_limits<wchar_t>::max() << ", Min = " << std::numeric_limits<wchar_t>::min() << std::endl;
    std::cout << "char16_t: Max = " << std::numeric_limits<char16_t>::max() << ", Min = " << std::numeric_limits<char16_t>::min() << std::endl;
    std::cout << "unsigned int: Max = " << std::numeric_limits<unsigned int>::max() << ", Min = " << std::numeric_limits<unsigned int>::min() << std::endl;
    std::cout << "unsigned short: Max = " << std::numeric_limits<unsigned short>::max() << ", Min = " << std::numeric_limits<unsigned short>::min() << std::endl;
    std::cout << "unsigned long: Max = " << std::numeric_limits<unsigned long>::max() << ", Min = " << std::numeric_limits<unsigned long>::min() << std::endl;
    std::cout << "float: Max = " << std::numeric_limits<float>::max() << ", Min = " << std::numeric_limits<float>::min() << std::endl;
    std::cout << "double: Max = " << std::numeric_limits<double>::max() << ", Min = " << std::numeric_limits<double>::min() << std::endl;
    std::cout << "Long double: Max = " << std::numeric_limits<long double>::max() << ", Min = " << std::numeric_limits<long double>::min() << std::endl;
    std::cout << "char: Max = " << std::numeric_limits<char>::max() << ", Min = " << std::numeric_limits<char>::min() << std::endl;
    std::cout << "Long long int: Max = " << std::numeric_limits<long long int>::max() << ", Min = " << std::numeric_limits<long long int>::min() << std::endl;

    constexpr int result = square(5);
    std::cout << "square of 5: " << result << std::endl;
    auto mylength = 50;
    auto mywidth = 9.3;
    auto area = 0;
    area = my_area(mylength,mywidth);
    std::cout << "Area: " << area << std::endl;
    
    
    // Using size_t to represent sizes and indices
    size_t arraySize = 10;
    int myArray[10];

    for (size_t i = 0; i < arraySize; ++i) {
        myArray[i] = i * 2;
    }

    std::cout << "Array elements: ";
    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;

    // Printing the size of size_t
    std::cout << "Size of size_t: " << sizeof(size_t) << " bytes" << std::endl;
    

    float myFloat32 = 3.14f;         // 32-bit floating-point
    double myFloat64 = 3.1415926535; // 64-bit floating-point
    long double myFloat80 = 3.141592653589793238L;  // 80-bit floating-point

    std::cout << "Fixed-Width Floating-Point Types:" << std::endl;
    std::cout << "float: " << myFloat32 << std::endl;
    std::cout << "double: " << myFloat64 << std::endl;
    std::cout << "long double: " << myFloat80 << std::endl;

    // Print precision information
    std::cout << "Float precision: " << FLT_DIG << " digits" << std::endl;
    std::cout << "Double precision: " << DBL_DIG << " digits" << std::endl;
    std::cout << "Long double precision: " << LDBL_DIG << " digits" << std::endl;
    
    

    
    
    return 0;
}
