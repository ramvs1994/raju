#include <stdio.h>
#include <stdbool.h>

#define NUMBER_OF_ORDERS 10
#define MAX_CRATES 5
#define DEBUG 0

#define MAX_ALLOWED_WEIGHT_PER_CRATE 15

typedef struct {
    int crate_ID;
    int current_weight;
} CRATE;

CRATE crate[MAX_CRATES]; //

typedef struct {
    int weight;
    bool fit_done;
} ORDER_WEIGH;

int main() {

	ORDER_WEIGH orders_weight[NUMBER_OF_ORDERS] = {{2,0}, {5,0}, {9,0}, {4,0}, {10,0}, {6,0}, {8,0}, {13,0}, {16,0}, {20,0}};
	int i;
	int j = 0;

	for (i = 0; i < MAX_CRATES; i++) {
	    crate[i].crate_ID = i + 1;
	    for ( ;((j < NUMBER_OF_ORDERS) && (crate[i].current_weight <= 15)); j++) {
		if (orders_weight[j].fit_done == 1) {
		    continue;
		}
	        if ((crate[i].current_weight + orders_weight[j].weight) < MAX_ALLOWED_WEIGHT_PER_CRATE) {
		    // place the order in the crate[i]
#ifdef DEBUG
    			printf(" DEBUG : order %d with weight %d fits in crate %d\n",j, orders_weight[j].weight, i);
#endif
    			crate[i].current_weight += orders_weight[j].weight;
		} else {
	            if ((j+1 < NUMBER_OF_ORDERS) && (crate[i].current_weight + orders_weight[j+1].weight) < MAX_ALLOWED_WEIGHT_PER_CRATE) {
#ifdef DEBUG
    			printf(" DEBUG : order %d with weight %d fits in crate %d\n",j+1, orders_weight[j+1].weight, i);
#endif
    			crate[i].current_weight += orders_weight[j+1].weight;
	                orders_weight[j+1].fit_done = 1; 
	            }
	            if ((j+2 < NUMBER_OF_ORDERS) && (crate[i].current_weight + orders_weight[j+2].weight < MAX_ALLOWED_WEIGHT_PER_CRATE)) {
#ifdef DEBUG
    			printf(" DEBUG : order %d with weight %d fits in crate %d\n",j+2, orders_weight[j+2].weight, i);
#endif
    			crate[i].current_weight += orders_weight[j+2].weight;
		        orders_weight[j+2].fit_done = 1; 
		   }
		   /* Go to next Crate */
		   break;
		}

	    }
	}
        for (; j < NUMBER_OF_ORDERS; j++) {
            if (orders_weight[j].fit_done == 0)
               printf("WARN : order %d with weight %d is not fitted in any of the crates\n",j, orders_weight[j].weight);
        }

}
