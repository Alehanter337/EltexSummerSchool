#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_OF_STORES 5
#define NUM_OF_BUYERS 3
#define LOADER_ADD_PRODUCTS 200
#define BUYER_NEED_MAX 10300
#define BUYER_NEED_MIN 9700
#define STORE_PRODUCT_MAX 1100
#define STORE_PRODUCT_MIN 900

int stores[NUM_OF_STORES];
pthread_mutex_t mutexes[NUM_OF_STORES];
int servised  = 0;

struct Buyer_data
{
    int id;
    int need;
};

struct Buyer_data  buyers_data[NUM_OF_BUYERS];

void *buyer_behavior(void *arg)
{
    struct Buyer_data *buyer_data = (struct Buyer_data*) arg;
   
    printf("BUYER: %d | need =  %d\n", buyer_data->id, buyer_data->need);
    
    while (buyer_data->need > 0) 
    {
        sleep(3);
        int curr_store = rand() % NUM_OF_STORES; //выбирается случайный мазагин
        pthread_mutex_lock(&mutexes[curr_store]);
            printf("BUYER %d | in store %d | buy %4d goods | need now = %4d\n",
				buyer_data->id, 
                curr_store + 1, 
                stores[curr_store], 
                buyer_data->need - stores[curr_store]
            );
            buyer_data->need -= stores[curr_store];
            stores[curr_store] = 0;
        pthread_mutex_unlock(&mutexes[curr_store]);
    }
    printf("BUYER: %d | needs = 0\n", buyer_data->id);
    servised++;
    pthread_exit(0);
}

void *loader_behavior(void *param) 
{
	while (servised < NUM_OF_BUYERS) 
    {
        int curr_store = rand() % NUM_OF_STORES;
		pthread_mutex_lock(&mutexes[curr_store]);
			stores[curr_store] += LOADER_ADD_PRODUCTS;
			printf("LOADER: add product %d | current quantity of products %d\n", 
                    curr_store + 1, 
                    stores[curr_store]
                  );
        pthread_mutex_unlock(&mutexes[curr_store]);
		sleep(2);
	}
	pthread_exit(0);
}

void stores_init(int *stores) 
{
    for (int i = 0; i < NUM_OF_STORES; i++)
    {
        stores[i] = rand() % (STORE_PRODUCT_MAX - STORE_PRODUCT_MIN + 1) + STORE_PRODUCT_MIN;
        printf("STORE: %d | GODS: %d\n", i + 1, stores[i]);
    }
}

void mutexes_init(pthread_mutex_t *mutexes)
{
    for (int i = 0; i < NUM_OF_STORES; i++) 
    {
        if (pthread_mutex_init(&mutexes[i], NULL))
        {
             perror("ERROR: mutex create faild");
             exit(EXIT_FAILURE);
        }
    }
}

void buyers_init(pthread_t *buyers)
{
    for (int i = 0; i < NUM_OF_BUYERS; i++) 
    {
        buyers_data[i].id = i + 1;
        buyers_data[i].need = rand() % (BUYER_NEED_MAX - BUYER_NEED_MIN + 1) + BUYER_NEED_MIN;
    }
    
    for (int i = 0; i < NUM_OF_BUYERS; i++)
    {
        void *curr_buyer = &buyers_data[i];
        if (pthread_create(&buyers[i], NULL, buyer_behavior, curr_buyer) != 0) 
        {
             perror("ERROR: buyer create faild");
             exit(EXIT_FAILURE);
        }
    }
}

void loader_init(pthread_t loader)
{
	if (pthread_create(&loader, NULL, loader_behavior, NULL) != 0)
    {
		perror("ERROR: loader create faild");
		exit(EXIT_FAILURE);
	}
}

void all_threads_join(pthread_t *buyers, pthread_t loader)
{
    for (int i = 0; i < NUM_OF_BUYERS; i++) 
    {
		pthread_join(buyers[i], NULL);
    }
	pthread_join(loader, NULL);
}

void all_mutex_destroy()
{
    for (int i = 0; i < NUM_OF_STORES; i++) 
    {
	    pthread_mutex_destroy(&mutexes[i]);
    }
}

int main(void)
{
    srand(time(NULL));
    pthread_t buyers[NUM_OF_BUYERS];
   	pthread_t loader;

    stores_init(stores);
    mutexes_init(mutexes);
    buyers_init(buyers);
    loader_init(loader);
    all_threads_join(buyers, loader);
	all_mutex_destroy();
	
    exit(EXIT_SUCCESS);
}
