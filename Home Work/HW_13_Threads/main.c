#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 10

void *func(void *arg)
{
	int *ptr;
	ptr = (int*)arg;
	printf("%d\n", *ptr);
	pthread_exit(NULL);
}

int main(void) 
{

	int arr[N];
    int *p;
	pthread_t tid;
	p = arr;

	for(int i = 1; i < N; i++, p++)
	{
		*p = i;
		pthread_create(&tid, NULL, func, p);
	}
	sleep(2);
	return 0;
}
