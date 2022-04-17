#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

typedef struct items_t{
    int data;
    int status; //0 = empty, -1 = deleted, 1 = not empty
} Items;

typedef struct object_t{
    char name[10]; //Passed as key in hash, using sum of chars (ASCII)
    Items myData; 
    struct object_t *_next;
} Object;

// typedef struct chain_t{
//     Object *_head;
// } Chain;

void init_hash(Object table[]){
    int i = 0;
    //debugging
    while(i<MAX_SIZE){
        table[i].myData.status = 0;
        table[i]._next = NULL;
        i++;
        //printf("\nsecond >> %d", table[i-1].myData.status);
    }
    printf("\nInitialized");
}

int getKey_hash(char name[]){
    int i = 0, sum = 0;
    while(name[i]!='\0'){
        sum+= (int) name[i];    //typecast char to int
        i++;
    }
    return sum % MAX_SIZE;
}

void search_hash(Object table[], char name[]){
    int index = getKey_hash(name);
    int chain = 0;
    Object *temp = &table[index];
    while(temp->_next != NULL){
        if (!strcmp(temp->name, name)){break;}
        chain++;
        temp = temp->_next;
    }
    if (temp->_next == NULL && strcmp(temp->name, name) != 0 && temp->myData.status == 0){printf("\nFetched - Key is not in hash map");}
    else if (strcmp(temp->name, name) == 0){printf("\nFetched - Index (%d) - Chain (%d) - Data (%d) - Status (%d) - [Key (%s)]",index, chain, temp->myData.data, temp->myData.status, temp->name);}
}

void insert_hash(Object table[], char name[], int data){
    int index = getKey_hash(name);
    int collsCheck = 0;

    if (!strcmp(table[index].name,name)){
        /*Update Only*/
        table[index].myData.data = data;
        printf("\nUpdating - key (%s)", name);
        return;
    }

    if (table[index].myData.status == 0){
        /*Inserting normally*/
        strcpy(table[index].name, name);
        table[index].myData.data = data;
        table[index].myData.status = 1; //set status to not empty
    }

    /*Collission*/
    else if (table[index].myData.status != 0 || table[index].myData.status != -1){
        /*Create new Object*/
        Object *newChain = (Object *) malloc(sizeof(Object));
        strcpy(newChain->name, name);
        newChain->myData.data = data;
        newChain->myData.status = 1;
        newChain->_next = NULL;

        /*Collission Insert*/
        table[index]._next = newChain;
        collsCheck = 1;
    } 

    printf("\nInserted - key (%s)", name);
    if (collsCheck){printf(" with Collission occured");}
}

void remove_hash(Object table[], char name[]){
    int index = getKey_hash(name);
    Object *temp = &table[index];
    while(temp->_next != NULL){
        if(!strcmp(temp->name,name)){
            printf("\nDeleting - key (%s) data", name);
            temp->myData.data = 0;
            temp->myData.status = -1;
            return;
        }
        temp = temp->_next;
    }
}

int main(){
    Object hashtable[MAX_SIZE];
    init_hash(hashtable);
    insert_hash(hashtable, "John Davis", 10);
    insert_hash(hashtable, "John Davis", 9);
    insert_hash(hashtable, "@", 8); //ascii 64 - expected Collission
    search_hash(hashtable, "John Davis");
    search_hash(hashtable, "3");
    remove_hash(hashtable, "John Davis");
    search_hash(hashtable, "@");
    search_hash(hashtable, "John Davis");
    return 0;
}