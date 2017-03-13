#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 10

typedef struct{
     char type; // 0=fried chicken, 1=French fries
     int amount; // pieces or weight
     char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t s;
void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last) { 
      // do nothing -- no free buffer item
    }
    sem_wait(&s);
    memcpy(&buffer[first], i,sizeof(item));
    first = (first + 1) % BUFFER_SIZE;
    sem_post(&s);

}
item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) { 
      // do nothing -- nothing to consume
    }
    sem_wait(&s);
    memcpy(i, &buffer[last],sizeof(item));
    last = (last + 1) % BUFFER_SIZE;
    sem_post(&s);
    return i;
}

void *produceThread(void *params){
	item i1; item i2; item i3;
	printf("Produce thread.\n");
	//declare the items
	i1.type = '0';
	i1.amount = 1;
	i1.unit = '2';

	i2.type = '1';
	i2.amount = 2;
	i2.unit = '3';

	i3.type = '0';
	i3.amount = 5;
  i3.unit = '2';
	printf("Produce item 1: Type: %c   Amount: %d   Unit: %c  ", i1.type,i1.amount,i1.unit );
        produce(&i1);
        printf(" First: %d, last: %d\n", first, last);
        printf("Produce item 2: Type: %c   Amount: %d   Unit: %c  ", i2.type,i2.amount,i2.unit );
        produce(&i2);
        printf(" First: %d, last: %d\n", first, last);
        printf("Produce item 3: Type: %c   Amount: %d   Unit: %c  ", i3.type,i3.amount,i3.unit );
        produce(&i3);
        printf(" First: %d, last: %d\n", first, last);
  }
void *consumeThread(void *params){
	printf("Consume thread\n");
        consume();
        printf("Consume:\n First: %d, last: %d\n", first, last );
        consume();
        printf("Another:\n First: %d, last: %d\n", first, last );
}

int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_destroy(sem_t *sem);

int main(){
	pthread_t tid_producer, tid_consumer;
  sem_init(&s, 0, BUFFER_SIZE);
	pthread_create(&tid_producer,NULL,produceThread,NULL);
	pthread_create(&tid_consumer,NULL,consumeThread,NULL);
  pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);
  sem_destroy(&s);
return 0;
}
