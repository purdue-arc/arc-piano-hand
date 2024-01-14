//
// Created by TPNml on 10/6/2023.
//

#include "phSpace.h"
using namespace phSpace;

// Ignore this file

int cool_thing() {
    int **x = (int **) malloc(20 * sizeof(int *));
    for (int i = 0; i < 20; i++) {
        *(x + i) = (int *) malloc(i * sizeof(int));
    }
    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j < i; j++) {
            x[i][j] = i + j;
        }
    }
    int sum = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < i; j++) {
            sum += *(*(x+i)+j);
        }
    }
    for (int i = 0; i < 20; i++) {
        free(*(x + i));
        *(x + i) = nullptr;
    }
    free(x);
    x = nullptr;
    std::cout << sum << std::endl;
    return 0;
}

int main() {
    FILE *fp = fopen("cmake-build-debug/cool_numbers.txt", "w+");
    if (fp == nullptr) {
        return 0;
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < i; j++) {
            fprintf(fp, "%d ", j);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    fp = nullptr;
    return 0;
}