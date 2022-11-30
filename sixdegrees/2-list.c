#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sixdegrees.h"


struct List *push(struct List *list, struct Node *node) {
	struct List *newlist = (struct List *)malloc(sizeof(struct List));
	newlist->node = node;
	newlist->next = list;
	list = newlist;
	return list;
}

struct List *append(struct List *list, struct Node *node) {
	struct List *newlist = (struct List *)malloc(sizeof(struct List));
	newlist->node = node;
	newlist->next = NULL;
	if (list == NULL) {
		list = newlist;
		return list;
	}
	struct List *current = list;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newlist;
	return list;
}
