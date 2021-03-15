#ifndef MSCNProblem_PROBLEMFILEREADER_H
#define MSCNProblem_PROBLEMFILEREADER_H

#include <iostream>
#include "Matrix.h"
#include "Table.h"
#define NEGATIVE_NUMBER -1

template <typename T>
class ProblemFileReader {
private:
    FILE* file;
    bool is_error;
public:
    ProblemFileReader(const char* file_name) {
        file = fopen(file_name, "r");
        is_error = file == NULL;
    };
    ~ProblemFileReader() {
        fclose(file);
    };

    bool fillTable(Table<T>* table);
    bool fillMatrix(Matrix<T>* matrix);
    bool fillBoundaryMatrix(Matrix<T>* min_mat, Matrix<T>* max_mat);
    int loadCount();
    double getNumber();
    bool eatString() {
        if (!is_error) {
            char temp_buff[128];
            fscanf(file, "%s", temp_buff);
            return true;
        }
        else
            return false;
    }
    bool nextLine() {
        if (is_error)
            return false;
        fscanf(file, "\n");
        return true;
    }
};

template <typename T>
bool ProblemFileReader<T>::fillTable(Table<T> *table) {
    if (is_error)
        return false;

    eatString();
    nextLine();
    double temp_number;
    for (int i = 0; i< table->getSize(); i++) {
        temp_number = getNumber();
        if (temp_number == NEGATIVE_NUMBER)
            return false;
        table->set(i, temp_number);
    }
    nextLine();

    return true;
}

template <typename T>
bool ProblemFileReader<T>::fillMatrix(Matrix<T> *matrix) {
    if (is_error)
        return false;

    eatString();
    nextLine();
    double temp_number;
    for (int i = 0; i < matrix->get_rows_amount(); i++) {
        for (int j = 0; j < matrix->get_columns_amount(); j++) {
            temp_number = getNumber();
            if (temp_number == NEGATIVE_NUMBER)
                return false;
            matrix->set(j, i, temp_number);
        }
        nextLine();
    }

    return true;
}

template  <typename T>
bool ProblemFileReader<T>::fillBoundaryMatrix(Matrix<T> *min_mat, Matrix<T> *max_mat) {
    if (is_error)
        return false;

    eatString();
    nextLine();
    double temp_number, temp_number2;
    for (int i = 0; i < min_mat->get_rows_amount(); i++) {
        for (int j = 0; j< min_mat->get_columns_amount(); j++) {
            temp_number = getNumber();
            temp_number2 = getNumber();
            if (temp_number == NEGATIVE_NUMBER || temp_number2 == NEGATIVE_NUMBER)
                return false;
            min_mat->set(j, i, temp_number);
            max_mat->set(j, i, temp_number2);
        }
        nextLine();
    }

    return true;
}

template <typename T>
int ProblemFileReader<T>::loadCount() {
    if (is_error)
        return false;

    eatString();
    int count = 0;
    fscanf(file, "%d", &count);
    nextLine();

    return count;
}

template <typename T>
double ProblemFileReader<T>::getNumber() {
    if (is_error)
        return NULL;

    double number;
    fscanf(file, " %lf ", &number);
    if (number < 0)
        return NEGATIVE_NUMBER;

    return number;
}

#endif //MSCNProblem_PROBLEMFILEREADER_H
