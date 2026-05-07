#include <stdio.h>

int main() {
    int x = 10;
    int* p = &x; // ponteiro para x

    printf("Valor de x: %d\n", x); // valor de x
    printf("Endereço de x: %p\n", &x); // endereço de x 0061FF18
    printf("Conteúdo de p: %p\n", p); // valor do ponteiro p (endereço de x) 0061FF18
    printf("Valor apontado por p: %d\n", *p); // valor apontado por p (10)

    return 0;
} 