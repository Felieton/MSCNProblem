#ifndef MSCNProblem_PROBLEMFILEWRITER_H
#define MSCNProblem_PROBLEMFILEWRITER_H

#include <iostream>
#include "Matrix.h"
#include "Table.h"

template <typename T>
class ProblemFileWriter {
private:
    FILE * file;
    bool is_error;

    bool printString(const char* name) {
        if (is_error)
            return false;

        fprintf(file, "%s ", name);

        return true;
    }

    bool newLine() {
        if (is_error)
            return false;

        fprintf(file, "\n");

        return true;
    }

    bool printDouble(double number) {
        if (is_error)
            return false;

        fprintf(file, "%.2f ", number);

        return true;
    }
public:
    ProblemFileWriter(const char* file_name) {
        file = fopen(file_name, "w+");
        is_error = file == NULL;
    }

    ~ProblemFileWriter() {
        fclose(file);
    }

    bool printMatrix(const char *name, Matrix<T>* matrix);
    bool printCount(const char* name, double count);
    bool printTable(const char* name, Table<T>* table);
    bool printBoundaryMatrix(const char* name, Matrix<T>* min_mat, Matrix<T>* max_mat);
};

template <typename T>
bool ProblemFileWriter<T>::printTable(const char* name, Table<T>* table) {
    printString(name);
    newLine();

    for (int i = 0; i < table->getSize(); i++) {
        printDouble(table->get(i));
    }
    newLine();

    return true;
}

template <typename T>
bool ProblemFileWriter<T>::printMatrix(const char* name, Matrix<T> * matrix) {
    printString(name);
    newLine();

    for (int i = 0; i < matrix->get_rows_amount(); i++) {
        for (int j = 0; j < matrix->get_columns_amount(); j++) {
            printDouble(matrix->get(j, i));
        }
        newLine();
    }

    return true;
}

template <typename T>
bool ProblemFileWriter<T>::printBoundaryMatrix(const char* name, Matrix<T>* min_mat, Matrix<T>* max_mat) {
    printString(name);
    newLine();

    for (int i = 0; i < min_mat->get_rows_amount(); i++) {
        for (int j = 0; j < max_mat->get_columns_amount(); j++) {
            printDouble(min_mat->get(j, i));
            printDouble(max_mat->get(j, i));
        }
        newLine();
    }

    return true;
}


template <typename T>
bool ProblemFileWriter<T>::printCount(const char* name, double count) {
    printString(name);
    printDouble(count);
    newLine();

    return true;
}


#endif //MSCNProblem_PROBLEMFILEWRITER_H
