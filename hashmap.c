/**
This program implements the back end of a HashMap ADT using a
simple tree structure. The goal is to practice ADT development in c.

@author Andrew Searns <abs2157@rit.edu>
*/

#include <stdlib.h>
#include <stdio.h>
#include "type.h"

typedef struct HashMap_S HashMapADT;
typedef struct Entry_S Entry;

#define _HM_IMPL_
#include "hashmapADT.h"
#define DEFAULT_SIZE 10
#define DEFAULT_CAPACITY .75

struct HashMap_S{
	Entry** table;
	double capacity;
	size_t size;
	size_t filled;
};

struct Entry_S{
	hmdata_t key;
	hmdata_t value;
};


unsigned long int hash(hmdata_t n){
	return (unsigned long int) n->data;
}


HashMapADT* hm_create(void){
	HashMapADT* new = malloc(sizeof(HashMapADT));
	Entry** tab = calloc(sizeof(Entry*), DEFAULT_SIZE);
	*new = (HashMapADT){table, DEFAULT_CAPACITY, DEFAULT_SIZE, 0};
	return new;
}


static void entry_destroy(Entry* ent){
	destroy_data(ent->key);
	destroy_data(ent->value);
	free(ent);
}

void hm_destroy(HashMapADT* hm){
	for(int i = 0; i < hm->size; i++){
		entry_destroy(table + i);
	}
	free(*(hm->table));
	free(hm);
	hm = NULL;
}


void hm_clear(HashMapADT* hm){
	HashMapADT* loc = hm;
	hm_destroy(hm);
	loc = hm_create();
}


static Entry* entry_create(hmdata_t key, hmdata_t value){
	Entry* new = malloc(sizeof(Entry));
	*new = (Entry){key, value};
	return new;
}

static void hm_resize(HashMapADT* hm){
	//TODO remap table
}

void hm_add(HashMapADT* hm, hmdata_t key, hmdata_t value){
	unsigned long int key_hash = hash(key);
	Entry* loc = hm->table[key_hash % size];
	if(loc == NULL){
		Entry* new = entry_create(key, value);
		hm->table[key_hash % size] = new;
		hm->filled++;
		if((hm->filled / hm->size) > hm->capacity){
			hm_resize(hm);
		}
	}
	else{
		while((loc != NULL) && ((compare(loc->key, key) != 0))){
			loc = hm->table[++key_hash % size];
		}
		if(loc == NULL){
			Entry* new = entry_create(key, value);
			hm->table[key_hash % size] = new;
			hm->filled++;
			if((hm->filled / hm->size) > hm->capacity){
				hm_resize(hm);
			}
		}
		else{
			destroy_data(loc->value);
			loc->value = value;
		}
	}
}


int hm_contains(HashMapADT* hm, sdata_t key){

}


sdata_t hm_get(HashMapADT* hm, sdata_t key){

}


void hm_remove(HashMapADT* hm, sdata_t key){

}
