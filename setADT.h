/**
This program inplements a SET ADT for the Mechanics of Programming Class at RIT.
The program is an in class exercise under alp.

@authors Andrew Searns <abs2157>, Starbuck Beagley <sb1389>
*/

#ifndef _SETADT_H_
#define _SETADT_H_

#ifndef _SET_IMPL_
typedef struct {} SetADT;
#endif

typedef STYPE sdata_t;

SetADT* set_create(void);
void set_destroy(SetADT* set);
void set_clear(SetADT* set);
void set_add(SetADT* set, sdata_t n);
int set_contains(SetADT* set, sdata_t n);
void set_remove(SetADT* set, sdata_t n);

//Mathematical operations
SetADT* set_union(SetADT* set1, SetADT* set2);
SetADT* set_intersect(SetADT* set1, SetADT* set2);
SetADT* set_relative_complement(SetADT* set1, SetADT* set2);

#endif
