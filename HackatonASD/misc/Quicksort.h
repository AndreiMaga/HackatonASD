#include "../data/Entry.h"

template <typename T>
void swap(std::vector<T*>* e, int i, int j) {
    T* ei= (*e)[i];
    (*e)[i] = (*e)[j];
    (*e)[j] = ei;
}

template <typename T>
int partition(std::vector<T*>* e, int left, int right, bool reversed) {
    int pi = left + (right - left) / 2;
    T* pv = (*e)[pi];

    int i = left, j = right;

    while (i <= j) {
        while ( reversed ? *(*e)[i] > * pv : *(*e)[i] < *pv) {
            i++;
        }
        while ( reversed ? *(*e)[j] < * pv : *(*e)[j] > *pv) {
            j--;
        }
        if (i <= j) {
            swap<T>(e, i, j);
            i++;
            j--;
        }
    }

    return i;
}
template <typename T>
void quicksort(std::vector<T*>* e, int left, int right, bool reversed = false) {
    if (left < right) {
        int pi = partition(e, left, right);
        quicksort(e, left, pi - 1);
        quicksort(e, pi, right);
    }
}

template <typename T>
void quicksort(std::vector<T*>* e, bool reversed = false) {
    quicksort<T>(e, 0, (int)e->size() - 1, reversed);
}