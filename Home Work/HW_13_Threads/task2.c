#include <pthread.h>
#include <stdio.h>

#define N 1000
#define MAX_VALUE 1000000
long A = 0;

void* func(void *param){
    long tmp;
    for(int i=0; i < MAX_VALUE; i++){
        tmp = A;
        tmp++;
        A = tmp;
    }
}

int main(void){
    pthread_t tid[N];

    for(int i=1; i < N; i++){
        pthread_create(&tid[i-1], NULL, func, NULL);
    }

    for(int i=0; i < N; i++){
        pthread_join(tid[i], NULL);
    }

    printf("A =  %ld\n", A);
    return 0;
}
