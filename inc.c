#include "common_threads.h"
#include "stdio.h"
#include "stdlib.h"

#define THREAD_POOL_SIZE 128

typedef struct __counter_t {
	int 			value;
	pthread_mutex_t lock;
}counter_t;

void init (counter_t *c) {
	c->value = 0;
	Pthread_mutex_init(&c->lock, NULL);
}

void increment (counter_t *c) {
	Pthread_mutex_lock (&c->lock);
	c->value++;
	Pthread_mutex_unlock (&c->lock);
}

void decrement (counter_t *c) {
	Pthread_mutex_lock (&c->lock);
	c->value -- ;
	Pthread_mutex_unlock (&c->lock) ;
}

int get (counter_t *c) {
	Pthread_mutex_lock (&c->lock) ;
	int rc = c->value;
	Pthread_mutex_unlock (&c->lock) ;
	return rc;
}

counter_t counter;

void addNumber(void* arg) {
	int threadID = *(int*)(arg+1);
	for (int i=0; i<12800000 / *(int*)arg; i++) {
		increment(&counter);
	}
	printf("I am here: %d\n", threadID);
}

void decNumber() {
	for (int i=0; i<20000000; i++) {
		increment(&counter);
	}
}

int main(int argc, char** argv) {
	pthread_t p[THREAD_POOL_SIZE];
	int threadNum = atoi(argv[1]);
	init(&counter);

	//int* args = malloc(sizeof(int) * 2 * (THREAD_POOL_SIZE) );
	int args[2*THREAD_POOL_SIZE];
	for (int i = 0; i < threadNum; i++)
	{
		args[2*i] = threadNum;
		args[2*i+1] = i;
		Pthread_create(&p[i], NULL, (void*)addNumber, (void*) (args+2*i));
	}
	for (int i = 0; i < threadNum; i++)
	{
		Pthread_join(p[i], NULL);
	}
	int ret = get(&counter);
	printf("return %d\n", ret);
	return 0;
}
