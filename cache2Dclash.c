#include <stdio.h>

int arr2D[128][8];  // 128 rows × 8 cols

int main(void) {
	//// outer loop repeats 100 times
    for (int iteration = 0; iteration < 100; iteration++) { 
        for (int row = 0; row < 128; row += 64) {
            for (int col = 0; col < 8; col++) { 
                arr2D[row][col] = iteration + row + col;
            }
        }
    }
    return 0;
}
