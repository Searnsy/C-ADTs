#include "type.h"
#include <stdlib.h>
#include <stdio.h>

int ORD = 1;

STYPE* create(data_d data, data_t type){
	STYPE* new = malloc(sizeof(STYPE));
	*new = (STYPE){data, type};
	return new;
}

void destroy_data(STYPE* dat){
	free(dat);
}


int compare(STYPE *first, STYPE *second){
	if(first->type == second->type){
		switch(first->type){
			case CHAR:
				return ORD * (2 * ((char)(second->data.c) > (char)(first->data.c)) +
						((char)(second->data.c) == (char)(first->data.c)) - 1);
			case UNSIGNED_CHAR:
				return ORD * (2 * ((unsigned char)(second->data.u_c) > (unsigned char)(first->data.u_c)) + 
						((unsigned char)(second->data.u_c) == (unsigned char)(first->data.u_c)) - 1);
			case INT:
				return ORD * (2 * ((int)(second->data.i) > (int)(first->data.i)) +
						((int)(second->data.i) > (int)(first->data.i)) - 1);
			case UNSIGNED_INT:
				return ORD * (2 * ((unsigned int)(second->data.u_i) > (unsigned int)(first->data.u_i)) +
						((unsigned int)(second->data.u_i) == (unsigned int)(first->data.u_i)) - 1);
			case SHORT:
				return ORD * (2 * ((short)(second->data.s) > (short)(first->data.s)) +
						((short)(second->data.s) == (short)(first->data.s)) - 1);
			case UNSIGNED_SHORT:
				return ORD * (2 * ((unsigned short)(second->data.u_s) > (unsigned short)(first->data.u_s)) +
						((unsigned short)(second->data.u_s) == (unsigned short)(first->data.u_s)) - 1);
			case LONG:
				return ORD * (2 * ((long)(second->data.l) > (long)(first->data.l)) +
						((long)(second->data.l) == (long)(first->data.l)) - 1);
			case UNSIGNED_LONG:
				return ORD * (2 * ((unsigned long)(second->data.u_l) > (unsigned long)(first->data.u_l)) +
						((unsigned long)(second->data.u_l) == (unsigned long)(first->data.u_l)) - 1);
			case FLOAT:
				return ORD * (2 * ((float)(second->data.f) > (float)(first->data.f)) +
						((float)(second->data.f) == (float)(first->data.f)) - 1);
			case DOUBLE:
				return ORD * (2 * ((double)(second->data.d) > (float)(first->data.d)) +
						((double)(second->data.d) == (double)(first->data.d)) - 1);
			default:
				return ORD * (2 * ((void *)(second->data.p) > (void *)(first->data.p)) +
						((void *)(second->data.p) == (void *)(first->data.p)) - 1);
		}
	}
	else{
		return ORD * (2 * (second->type > first->type) + (second->type == first->type) - 1);
	}
}

void print(STYPE *dat){
	switch(dat->type){
		case CHAR:
			printf("%c", (char)dat->data.c);
			break;
		case UNSIGNED_CHAR:
			printf("%u", (unsigned char)dat->data.u_c);
			break;
		case INT:
			printf("%d", (int)dat->data.i);
			break;
		case UNSIGNED_INT:
			printf("%u", (unsigned int)dat->data.u_i);
			break;
		case SHORT:
			printf("%hd", (short)dat->data.s);
			break;
		case UNSIGNED_SHORT:
			printf("%hu", (unsigned short)dat->data.u_s);
			break;
		case FLOAT:
			printf("%f", (float)dat->data.f);
			break;
		case DOUBLE:
			printf("%f", (double)dat->data.d);
			break;
		default:
			printf("%p", (void *)dat->data.p);
	}
}

/*
This may be handy to have at the ready

switch(dat->type){
        case CHAR:
            break;
        case UNSIGNED_CHAR:
            break;
        case INT:
            break;
        case UNSIGNED_INT:
            break;
        case SHORT:
            break;
        case UNSIGNED_SHORT:
            break;
        case FLOAT:
            break;
        case DOUBLE:
            break;
        default:
    }
*/
