#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include < sys/wait.h>

int main(void){
    char input[50];
    printf("Kérem adjon meg egy parancsot!");
    scanf("%s", input);
    system(input);

    exit(0);

}
