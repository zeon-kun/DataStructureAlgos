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

/**
 * @brief Get the Hash Key object
 * 
 * @param key 
 * @return int 
 */
int isPrime(int n) {
    if (n <= 1) return 0;

    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
           return 0;
        }
    }

    return 1;
}

int getMaxPrime(int n){
    while(n){
        if (isPrime(n) == 1){
            break;
        }
        n--;
    }
    return n;
}

int getHashKey2(int key){
    return getMaxPrime(MAX_SIZE) - (key % getMaxPrime(MAX_SIZE));
}
int getHashKey(int key){
    return key % MAX_SIZE;
}

void insertObject(int key, int data){
    int index = getHashKey(key);
    int index2 = getHashKey2(key);
    int loop = 1;
    int i = index; //as a limiter for probing action

    //Double Hashing
    while(hashtable[index].data != -1){
        if (hashtable[index].key == key){
            /*Update Only*/
            hashtable[index].data = data;
        }
        index = (index + loop++ * index2) % MAX_SIZE;
        if (index == i){
            /*Hash Table is Full*/
            printf("\n Key (%d) tidak bisa masuk \n", key);      
            return;
        }
    }
    hashtable[index].data = data;
    hashtable[index].key = key;
    size++;
    printf("\n Key (%d) masuk di Index (%d)\n", key, index);
}

void removeObjectData(int key){
    int index = getHashKey(key);
    int index2 = getHashKey2(key);
    int loop = 1;
    int i = index; //delimiter

    //Double Hashing
    while(hashtable[index].data != -1){
        if (hashtable[index].key == key){
            /*Deleting*/
            hashtable[index].data = -2; //Masih nyimpen key
            size--;
            printf("\n Key (%d) dihapus \n", key);
            return;
        }
        index = (index + loop++ * index2) % MAX_SIZE;
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
    printHash();
    removeObjectData(10);
    removeObjectData(11);
    printHash();
}
