#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct object{
    int key;
    int data;
} Object;

/**
 * hashtable declaration
 * ON DATA : -1 = empty, -2 = deleted
 */
Object hashtable[MAX_SIZE] = {NULL};
int size = 0;

void initHash(){
    int i;
    for(i=0;i<MAX_SIZE;i++){
        /*Set all data to empty*/
        hashtable[i].data = -1;
    }
}

int getHashKey(int key){
    return key % MAX_SIZE;
}

void insertObject(int key, int data){
    int index = getHashKey(key);
    int i = index; //as a limiter for probing action

    //Linear Probing : searching the empty space
    while(hashtable[index].data != -1){
        if (hashtable[index].key == key){
            /*Update Only*/
            hashtable[index].data = data;
        }
        index = (index + 1) % MAX_SIZE;
        if (index == i){
            /*Hash Table is Full*/
            printf("\n Key (%d) tidak bisa masuk \n", key);      
            return;
        }
    }
    hashtable[index].data = data;
    hashtable[index].key = key;
    size++;
    printf("\n Key (%d) masuk \n", key);
}

void removeObjectData(int key){
    int index = getHashKey(key);
    int i = index; //delimiter

    //Linear Probing
    while(hashtable[index].data != -1){
        if (hashtable[index].key == key){
            /*Deleting*/
            hashtable[index].data = -2; //Masih nyimpen key
            size--;
            printf("\n Key (%d) dihapus \n", key);
            return;
        }
        index = (index + 1) % MAX_SIZE;
        if (index == i){
            break;
        }
    }
    printf("\n Key (%d) tidak ada \n", key);
}

void printHash(){
    int i;
    for (i = 0; i < MAX_SIZE; i++){
        if (hashtable[i].data == -1){
            printf("\n Hashtable[%d] : no object here \n", i);
        }else{
            printf("\n Hashtable[%d] : %d (key) and %d (data) \n", i, hashtable[i].key, hashtable[i].data);
        }
    }
}

int main(){
    initHash();
    insertObject(0,1);
    insertObject(10,2); //expected collision >> 0-hash0 0+1-hash1
    insertObject(2,3);
    insertObject(3,4);
    insertObject(4,5);
    insertObject(5,6);
    insertObject(6,7);
    insertObject(7,8);
    insertObject(8,9);
    insertObject(9,0);   
    printHash();
    removeObjectData(10);
    removeObjectData(9);
    removeObjectData(11);
    printHash();
}