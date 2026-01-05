#include <stdio.h>

int arr2D[3000][500];

int main(void) {
    for (int col = 0; col < 500; col++) {      // outer: columns
        for (int row = 0; row < 3000; row++) { // inner: rows
            arr2D[row][col] = row + col;
        }
    }
    return 0;
}
