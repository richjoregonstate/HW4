#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)/* FIXME */
{
	int index;
	ht->table = (struct hashLink **) malloc(sizeof(struct hashLink)*tableSize);
	ht->tableSize=0;
	ht->count=0;
	for (index = 0; index < tableSize; index++) {
		ht->table[index] = 0;
	}

}

void freeMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	struct hashLink *temp2;
	for(i = 0; i < ht->tableSize; i++){
		temp = ht->table[i];
		while(temp != NULL){
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
	}
	free(ht->table);
	ht->count=0;
	ht->table=0;
	ht->tableSize=0;
}

/* Add an element to the Hash Table */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)/* FIXME */
{
	struct hashLink *newLink = (struct hashLink *) malloc(sizeof(struct hashLink));
	struct hashLink *current;
	int idx;
	newLink->key = k;
	idx = stringHash1(k);
	newLink->key = k;
	newLink->value = 0;
	newLink->next = 0;

	/*printf("Key: %d Word: %s	|		", idx,k);*/
	/*
	while (ht->table[idx] == 0 && ht->table[idx]->key != k) {
		printf("!!!SHIFT!!!");
		idx++;
	}*/

	if (ht->table[idx] == 0){
		/*printf("No collsion");*/
		ht->table[idx] = newLink;
		ht->tableSize++;
	}
	else{
		current = ht->table[idx];
		current->value++;
		/*printf("Collsion w/ 1 + %d",ht->table[idx]->value);*/
		while (current->next != 0) {/*go to the end of the linked list incrmenting the nodes on your way in*/
			current = current->next;
			current->value++;
		}
		current->next = newLink;
	}
	/*printf("\n\n");*/
	ht->count++;

}



/* Returns a pointer to the value of element with key k in the Hash Table
   If the element is not in the Hash Table, returns NULL */
ValueType* atMap (struct hashMap * ht, KeyType k)/* FIXME */
{
	int idx;
	idx = stringHash1(k);

	while (ht->table[idx] != 0 && ht->table[idx]->key != k) {/* If we hit 0 then we insert. If we hit a copy then insert.*/
		idx++;
	}

	if (ht->table[idx] == 0){
		return NULL;
	}
	else{
		return (int*)ht->table[idx]->value;
	}

}

int containsKey (struct hashMap * ht, KeyType k)
{
	if (atMap(ht,k)==0){
		return 0;
	}else{
		return 1;
	}
}

void removeKey (struct hashMap * ht, KeyType k)
{
	int bucket = stringHash2(k)%ht->tableSize;
	struct hashLink *cur;
	struct hashLink *prev;
	if(ht->table[bucket] == 0){
		return;
	}else{
		cur=ht->table[bucket];
		prev=ht->table[bucket];
		while(cur!=0){
			if(strcmp(cur->key,k)==0){
				if(cur==ht->table[bucket]){
					ht->table[bucket]=cur->next;

				}else{
				prev->next=cur->next;
				}
				free(cur);
				ht->count--;
				return;
			}else{
				prev=cur;
				cur=cur->next;
			}
		}
	}
}

int sizeMap (struct hashMap *ht)
{
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{
	int runner = 0;
	int i;
	for(i=0; i<ht->tableSize; i++){
		if(ht->table[i]==0){
			runner++;
		}
	}
	return runner;
}

float tableLoad(struct hashMap *ht)
{
   return (float)sizeMap(ht)/(float)capacityMap(ht);
}
