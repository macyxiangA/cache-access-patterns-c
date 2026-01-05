#include <stdio.h>

int arr[100000];  // global → .bss / DATA

int main(void) {
    for (int i = 0; i < 100000; i++) {
        arr[i] = i;
    }
    return 0;
}
