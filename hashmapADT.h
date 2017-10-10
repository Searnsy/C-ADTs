/**
This program inplements a HashMap ADT. The goal is to practice
ADT development in c.

@authors Andrew Searns <abs2157>
*/

#ifndef _HASHMAP_ADT_H_
#define _HASHMAP_ADT_H_

#ifndef _HM_IMPL_
typedef struct {} HashMapADT;
#endif

typedef STYPE hmdata_t;

unsigned long int hash(hmdata_t n);

HashMapADT* hm_create(void);
void hm_destroy(HashMapADT* hm);
void hm_clear(HashMapADT* hm);
void hm_add(HashMapADT* hm, hmdata_t key, hmdata_t value);
int hm_contains(HashMapADT* hm, hmdata_t key);
hmdata_t hm_get(HashMapADT* hm, hmdata_t key);
void hm_remove(HashMapADT* set, hmdata_t key);

#endif
