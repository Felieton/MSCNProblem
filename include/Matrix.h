#ifndef MSCNProblem_MATRIX_H
#define MSCNProblem_MATRIX_H

#include <iostream>
#include "Table.h"

template <typename T>
class Matrix {
private:
    Table<Table<T>*>* matrix;
    int columns;
    int rows;
public:
    Matrix() {
        columns = 0;
        rows = 0;
        matrix = new Matrix<T>(0, 0);
    }

    Matrix(int init_columns, int init_rows) {
        columns = init_columns;
        rows = init_rows;

        matrix = new Table<Table<T>*>(rows);
        for (int i = 0; i < rows; i++) {
            matrix->set(i, new Table<T>(columns));
        }
    };

    ~Matrix() {
        for (int i = 0; i < rows; i++)
            delete matrix->get(i);
        delete matrix;
    };

    bool set(int column, int row, T value);
    T get(int column, int row);
    void print();
    T sumColumn(int column_index);
    T sumRow(int row_index);
    bool setSize(int new_columns, int new_rows);
    int get_columns_amount();
    int get_rows_amount();
    int filledSpotsInCol(int column);
    int filledSpotsInRow(int row);
    void fillMatrixWith(T value);
};

template<typename T>
bool Matrix<T>::set(int column, int row, T value) {
    if (column < 0 || column >= columns || row < 0 || row >= rows)
        return false;

    matrix->get(row)->set(column, value);

    return true;
}

template<typename T>
T Matrix<T>::get(int column, int row) {
    if (column < 0 || column >= columns || row < 0 || row >= rows)
        return NULL;

    return matrix->get(row)->get(column);
}

template<typename T>
void Matrix<T>::print() {
    for (int i = 0; i < rows; i++) {
        matrix->get(i)->print();
    }
    std::cout<<"\n";
}

template<typename T>
T Matrix<T>::sumColumn(int column_index) {
    if (column_index < 0)
        return NULL;
    T sum = NULL;
    for (int i = 0; i < rows; i++)
        sum += matrix->get(i)->get(column_index);

    return sum;
}

template<typename T>
T Matrix<T>::sumRow(int row_index) {
    if (row_index < 0)
        return NULL;
    T sum = NULL;
    for (int i = 0; i < columns; i++) {
        sum += matrix->get(row_index)->get(i);
    }

    return sum;
}

template <typename T>
bool Matrix<T>::setSize(int new_columns, int new_rows) {
    if (new_columns < 0 || new_rows < 0)
        return false;
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++)
            delete matrix->get(i);
        delete matrix;
    }

    columns = new_columns;
    rows = new_rows;

    matrix = new Table<Table<T>*>(rows);
    for (int i = 0; i < rows; i++) {
        matrix->set(i, new Table<T>(columns));
    }

    return true;
}

template <typename T>
int Matrix<T>::get_columns_amount() {
    return columns;
}

template <typename T>
int Matrix<T>::get_rows_amount() {
    return rows;
}

template<typename T>
int Matrix<T>::filledSpotsInCol(int column) {
    if (column < 0 || column >= get_columns_amount())
        return NULL;

    int counter = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix->get(i)->get(column) != NULL)
            counter++;
    }

    return counter;
}

template<typename T>
int Matrix<T>::filledSpotsInRow(int row) {
    if (row < 0 || row >= rows)
        return NULL;

    int counter = 0;
    for (int i = 0; i < columns; i++) {
        if (matrix->get(row)->get(i) != NULL)
            counter++;
    }

    return counter;
}
template<typename T>
void Matrix<T>::fillMatrixWith(T value) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            this->set(j, i, value);
        }
    }
}

#endif //MSCNProblem_MATRIX_H
