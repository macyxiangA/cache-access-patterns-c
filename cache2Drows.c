#include <stdio.h>

int arr2D[3000][500];  // 3000 rows × 500 cols

int main(void) {
    for (int row = 0; row < 3000; row++) {
        for (int col = 0; col < 500; col++) {
            arr2D[row][col] = row + col;  // row-major traversal
        }
    }
    return 0;
}
