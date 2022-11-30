#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sixdegrees.h"


void deletelist(struct List *list) {
	struct List *current = list;
	struct List *next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	list = NULL;
}

void deletetree(struct Tree *tree) {
	if (tree == NULL) {
		return;
	}
	deletetree(tree->left);
	deletetree(tree->right);
	free(tree);
}

void deletequeue(struct Queue *queue) {
	struct Queue *current = queue;
	struct Queue *next;
	while (current != NULL) {
		next = current->next;
		deletelist(current->list);
		free(current);
		current = next;
	}
	queue = NULL;
}

void delete(struct Tree *tree) {
	if (tree == NULL) {
		return;
	}
	deletelist(tree->node->list);
	free(tree->node);
	delete(tree->left);
	delete(tree->right);
	free(tree);
}
