#ifndef MSCNProblem_TABLE_H
#define MSCNProblem_TABLE_H

#include <iostream>

template <typename T>
class Table {
private:
    int size;
    T *table;
public:
    Table() {
        i_size = 0;
        table = NULL;
    };

    Table(Table &other) {
        size = other.size;
        table = new T[size];

        for (int i = 0; i < size; i++) {
            table[i] = other.table[i];
        }
    };

    Table(int init_size) {
        size = init_size;
        table = new T[size];
    };

    ~Table() {
        delete[] table;
    };

    bool set(int index, T value);
    T get(int index);
    void print();
    bool setSize(int new_size);
    int getSize();
};

template <typename T>
bool Table<T>::set(int index, T value) {
    if (index < 0 || index >= size)
        return false;
    table[index] = value;

    return true;
}

template <typename T>
T Table<T>::get(int index) {
    if (index < 0 || index >= size)
        return NULL;

    return table[index];
}

template <typename T>
void Table<T>::print() {
    std::cout<< "[";

    for (int i = 0; i < size; i++) {
        std::cout<<table[i];
        if (i != size - 1)
            std::cout<<", ";
    }

    std::cout<<"]"<<std::endl;
}

template <typename T>
bool Table<T>::setSize(int new_size) {
    if (new_size <= 0)
        return false;

    if (table != NULL)
        delete[] table;

    size = new_size;
    table = new T[size];

    return true;
}

template<typename T>
int Table<T>::getSize() {
    return size;
}

#endif //MSCNProblem_TABLE_H
