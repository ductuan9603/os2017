#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 10

typedef struct{
     char type; // 0=fried chicken, 1=French fries
     int amount; // pieces or weight
     char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last) { 
      // do nothing -- no free buffer item
    }
    memcpy(&buffer[first], i,sizeof(item));
    first = (first + 1) % BUFFER_SIZE;
}
item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) { 
      // do nothing -- nothing to consume
    }
    memcpy(i, &buffer[last],sizeof(item));
    last = (last + 1) % BUFFER_SIZE;
    return i;
}

void produceThread(){
	item I[3];
	//declare the items
	I[0].type = '0';
	I[0].amount = 1;
	I[0].unit = '2';

	I[1].type = '1';
	I[1].amount = 2;
	I[1].unit = '3';

	I[2].type = '0';
	I[2].amount = 5;
    I[2].unit = '2';

	for(int i = 0 ,i < 3, i++){
		produce(&I[i]);
		printf("produce Items [%d]    first: %d    Last: %d\n",i, first, last);}
}
void consumeThread(int n){
	for (int i=0,i<2,i++){
		consume();
		printf("consume: \n first: %d\n last: %d \n",first, last);}
}

int main(){
    pthread_t tid_producer;
	pthread_create(&tid_producer,NULL,produceThread,NULL);
    pthread_t tid_consumer;
	pthread_create(&tid_consumer,NULL,consumeThread,NULL);
    pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);
return 0;
}
