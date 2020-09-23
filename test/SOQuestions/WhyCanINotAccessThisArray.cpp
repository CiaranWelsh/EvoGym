/*
 * Question asked here:
 * https://stackoverflow.com/questions/64028942/why-can-i-not-access-this-array-whilst-implementing-an-initializer-list-construc?noredirect=1#comment113224259_64028942
 * Answer: caught out by setting _Rows and _Cols in the constructor.
 */
#include <initializer_list>
#include <iostream>

template<class T>
class Matrix {

    void resize(unsigned int rows, unsigned int cols) {
        if (rows * cols != _Rows * _Cols) {
            if (_Array) {
                delete[] _Array;
                _Array = nullptr;
            }
            if (rows && cols) {
                _Array = new T[rows * cols];
            }
        }

        _Rows = rows;
        _Cols = cols;
    }

    /**
     * number of rows
     */
        unsigned int _Rows;

    /**
     * number of columns
     */
    unsigned int _Cols;

    /**
     * pointer to block of memory of the data, stored in row-major format.
     */
    T *_Array;

public:
    Matrix<T>(std::initializer_list<std::initializer_list<T>> matrix)
        : _Array(nullptr) {
        resize(matrix.size(), (*matrix.begin()).size());

        for (int row = 0; row < _Rows; row++) {
            const std::initializer_list<T> &r = matrix.begin()[row];
            for (int col = 0; col < _Cols; col++) {
                printf("_Array[%d] is Row: %d; col: %d; value: %d\n", row*_Cols+col , row, col, r.begin()[col]);
                _Array[row*_Cols+col ] = r.begin()[col];
            }
        }
    }
};

int main(){
    Matrix<int> matrix(
            {
                    {1, 2, 3},
                    {4, 5, 6},
            });
}