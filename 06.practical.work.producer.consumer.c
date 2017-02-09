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
int main(){
    item i1;
    i1.type = '0';
    i1.amount = 5;
    i1.unit = '2';
    
    item i2;
    i2.type = '1';
    i2.amount = 3;
    i2.unit = '1';

    printf("- Item 1:\n Type: %c\n Amount: %d\n Unit: %c\n",i1.type,i1.amount,i1.unit);
    produce(&i1);
    printf(" First: %d, last: %d\n", first, last);
    
    printf("\n- Item 2:\n Type: %c\n Amount: %d\n Unit: %c\n",i2.type,i2.amount,i2.unit);
    produce(&i2);
    printf(" First: %d, last: %d\n", first, last);
    
    item* consumed = consume();
    printf("\n- Item consumed:\n Type: %c\n Amount: %d\n Unit: %c\n", consumed->type, consumed->amount, consumed->unit);
    printf(" First: %d, last: %d\n", first, last);
    return 0;
}
