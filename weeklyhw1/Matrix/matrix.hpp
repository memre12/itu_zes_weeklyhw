#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<iostream>
#include<vector>
#include<cmath>

namespace MatrixLibrary{

template<typename T>
using vector = std::vector<T>;

template<typename T>
using matrix = std::vector<std::vector<T>>;

template<typename T>
class Matrix{

    public:
    Matrix(int _rows, int _cols, T _initVal = .0){
        m_rows = _rows;
        m_cols = _cols;
        m_matrix = matrix<T>(_rows, vector<T>(_cols, _initVal));
    };
    Matrix(const matrix<T>& _mat){
        m_matrix = _mat;
        m_rows = _mat.size();
        m_cols = _mat[0].size();
    };
    Matrix(const vector<T>& _vec){
        m_matrix = matrix<T>(1, _vec);
        m_rows = 1;
        m_cols = _vec.size();
    };
    Matrix(const Matrix<T>& _mat){
        m_matrix = _mat.m_matrix;
        m_rows = _mat.m_rows;
        m_cols = _mat.m_cols;
    };
    Matrix<T> inverse(){
        if(m_rows != m_cols){
            std::cout << "Inverse is only defined for square matrices" << std::endl;
            return Matrix<T>(0, 0);
        }
        Matrix<T> inv = *this;
        T det = this->determinant();
        if(det == .0){
            std::cout << "Determinant is zero, inverse does not exist" << std::endl;
            return Matrix<T>(0, 0);
        }
        else if(m_rows == 1){
            inv.m_matrix[0][0] = 1 / m_matrix[0][0];
        }
        else if(m_rows == 2){
            inv.m_matrix[0][0] = m_matrix[1][1] / det;
            inv.m_matrix[0][1] = -m_matrix[0][1] / det;
            inv.m_matrix[1][0] = -m_matrix[1][0] / det;
            inv.m_matrix[1][1] = m_matrix[0][0] / det;
        }
        else{
            for(int i = 0; i < m_rows; i++){
                for(int j = 0; j < m_cols; j++){
                    inv.m_matrix[i][j] = pow(-1, i + j) * minor(m_matrix, i, j).determinant() / det;
                }
            }
        }
        return inv;
    };
    T trace() const{
        if(m_rows != m_cols){
            std::cout << "Trace is only defined for square matrices" << std::endl;
            return .0;
        }
        T trace = .0;
        for(int i = 0; i < m_rows; i++){
            trace += m_matrix[i][i];
        }
        return trace;
    };
    T determinant() const{
        if(m_rows != m_cols){
            std::cout << "Determinant is only defined for square matrices" << std::endl;
            return .0;
        }
        T det = .0;
        if(m_rows == 1){
            det = m_matrix[0][0];
        }
        else if(m_rows == 2){
            det = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
        }
        else{
            for(int i = 0; i < m_rows; i++){
                det += pow(-1, i) * m_matrix[0][i] * minor(m_matrix, 0, i).determinant();
            }
        }
        return det;
    };
    Matrix<T> minor(const Matrix<T>& _mat, int _row, int _col) const{
        Matrix<T> minor(_mat.m_rows - 1, _mat.m_cols - 1);
        int r = 0;
        for(int i = 0; i < _mat.m_rows; i++){
            if(i == _row){
                continue;
            }
            int c = 0;
            for(int j = 0; j < _mat.m_cols; j++){
                if(j == _col){
                    continue;
                }
                minor.m_matrix[r][c] = _mat.m_matrix[i][j];
                c++;
            }
            r++;
        }
        return minor;
    };
    Matrix<T> transpose() const{
        Matrix<T> trans(m_cols, m_rows);
        for(int i = 0; i < m_cols; i++){
            for(int j = 0; j < m_rows; j++){
                trans[i][j] = m_matrix[j][i];
            }
        }
        return trans;
    };
    static Matrix<T> add(const Matrix<T>& _mat1, const Matrix<T>& _mat2){
        if(_mat1.m_rows != _mat2.m_rows || _mat1.m_cols != _mat2.m_cols){
            std::cout << "Matrices must have same dimensions" << std::endl;
            return Matrix<T>(0, 0);
        }
        Matrix<T> sum(_mat1.m_rows, _mat1.m_cols);
        for(int i = 0; i < _mat1.m_rows; i++){
            for(int j = 0; j < _mat1.m_cols; j++){
                sum.m_matrix[i][j] = _mat1.m_matrix[i][j] + _mat2.m_matrix[i][j];
            }
        }
        return sum;
    };
    static Matrix<T> subtract(const Matrix<T>& _mat1, const Matrix<T>& _mat2){
        if(_mat1.m_rows != _mat2.m_rows || _mat1.m_cols != _mat2.m_cols){
            std::cout << "Matrices must have same dimensions" << std::endl;
            return Matrix<T>(0, 0);
        }
        Matrix<T> diff(_mat1.m_rows, _mat1.m_cols);
        for(int i = 0; i < _mat1.m_rows; i++){
            for(int j = 0; j < _mat1.m_cols; j++){
                diff.m_matrix[i][j] = _mat1.m_matrix[i][j] - _mat2.m_matrix[i][j];
            }
        }
        return diff;
    };
    Matrix<T> operator+(const Matrix<T>& _mat){
        return add(m_matrix, _mat);
    };
    Matrix<T> operator+(const T& _scalar){
        Matrix<T> sum(m_rows, m_cols);
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_cols; j++){
                sum.m_matrix[i][j] = m_matrix[i][j] + _scalar;
            }
        }
        return sum;
    };
    Matrix<T> operator-(const Matrix<T>& _mat){
        return subtract(m_matrix, _mat);
    };
    Matrix<T> operator-(){
        return neg(m_matrix);
    };
    Matrix<T> operator-(const T& _scalar){
        Matrix<T> diff(m_rows, m_cols);
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_cols; j++){
                diff.m_matrix[i][j] = m_matrix[i][j] - _scalar;
            }
        }
        return diff;
    };
    Matrix<T> operator*(const Matrix<T>& _mat){
        return pwise_mul(m_matrix, _mat);
    };
    Matrix<T> neg(const Matrix<T>& _mat1) const{
        Matrix<T> neg(_mat1.m_rows, _mat1.m_cols);
        for(int i = 0; i < _mat1.m_rows; i++){
            for(int j = 0; j < _mat1.m_cols; j++){
                neg.m_matrix[i][j] = -_mat1.m_matrix[i][j];
            }
        }
        return neg;
    };
    Matrix<T> pwise_mul(const Matrix<T>& _mat1, const Matrix<T>& _mat2) const{
        if(_mat1.m_rows != _mat2.m_rows || _mat1.m_cols != _mat2.m_cols){
            std::cout << "Matrices must have same dimensions" << std::endl;
            return Matrix<T>(0, 0);
        }
        Matrix<T> pwise(_mat1.m_rows, _mat1.m_cols);
        for(int i = 0; i < _mat1.m_rows; i++){
            for(int j = 0; j < _mat1.m_cols; j++){
                pwise.m_matrix[i][j] = _mat1.m_matrix[i][j] * _mat2.m_matrix[i][j];
            }
        }
        return pwise;
    };
    static Matrix<T> dot(const Matrix<T>& _mat1, const Matrix<T>& _mat2){
        if(_mat1.m_cols != _mat2.m_rows){
            std::cout << "Matrices must have compatible dimensions" << std::endl;
            return Matrix<T>(0, 0);
        }
        Matrix<T> dot(_mat1.m_rows, _mat2.m_cols);
        for(int i = 0; i < _mat1.m_rows; i++){
            for(int j = 0; j < _mat2.m_cols; j++){
                for(int k = 0; k < _mat1.m_cols; k++){
                    dot.m_matrix[i][j] += _mat1.m_matrix[i][k] * _mat2.m_matrix[k][j];
                }
            }
        }
        return dot;
    };
    float magnitude(const Matrix<T>& _mat) const{
        float mag = .0;
        for(int i = 0; i < _mat.m_rows; i++){
            for(int j = 0; j < _mat.m_cols; j++){
                mag += pow(_mat.m_matrix[i][j], 2);
            }
        }
        return sqrt(mag);
    };
    Matrix<T> normalize(const Matrix<T>& _mat) const{
        Matrix<T> norm(_mat.m_rows, _mat.m_cols);
        float mag = magnitude(_mat);
        for(int i = 0; i < _mat.m_rows; i++){
            for(int j = 0; j < _mat.m_cols; j++){
                norm.m_matrix[i][j] = _mat.m_matrix[i][j] / mag;
            }
        }
        return norm;
    };
    static Matrix<T> zeroes(int _rows, int _cols){
        return Matrix<T>(_rows, _cols);
    };
    static Matrix<T> ones(int _rows, int _cols){
        return Matrix<T>(_rows, _cols, 1);};
    static Matrix<T> identity(int _rows){
        Matrix<T> id(_rows, _rows);
        for(int i = 0; i < _rows; i++){
            id.m_matrix[i][i] = 1;
        }
        return id;
    };
    const matrix<T>& get_matrix() const {return this->m_matrix;};
    int get_rows() const {return this->m_rows;};
    int get_cols() const {return this->m_cols;};
    void print_matrix(const Matrix<T>& _mat) const{
        for(int i = 0; i < _mat.m_rows; i++){
            for(int j = 0; j < _mat.m_cols; j++){
                std::cout << _mat.get_matrix()[i][j] << " ";
            }
            std::cout << std::endl;
        }
    };

    private:
    matrix<T> m_matrix;
    int m_rows;
    int m_cols;

};
template<typename T>
std::ostream& operator<<(std::ostream &out, const Matrix<T>& _mat){
    if(_mat.get_matrix().empty()){
        out << "Empty matrix!" << std::endl;
        return out;
    }
    out << "[" << std::endl;
    for(int i = 0; i < _mat.get_rows(); i++){
        out << "[";
        for(int j = 0; j < _mat.get_cols(); j++){
            if(j != _mat.get_cols() - 1){
                out << _mat.get_matrix()[i][j] << ", ";
            }else{
                out << _mat.get_matrix()[i][j] << "]";
            }
        }
        out << std::endl;
    }
    out << "]";
    return out;
};
}
#endif
