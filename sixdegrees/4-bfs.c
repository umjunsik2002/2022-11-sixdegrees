#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sixdegrees.h"


// techiedelight.com/clone-given-linked-list
struct List *copylist(struct List *list) {
	struct List *current = list;
	struct List *copy = NULL;
	struct List *tail = NULL;
	while (current != NULL) {
		if (copy == NULL) {
			copy = (struct List *)malloc(sizeof(struct List));
			copy->node = current->node;
			copy->next = NULL;
			tail = copy;
		}
		else {
			tail->next = (struct List *)malloc(sizeof(struct List));
			tail = tail->next;
			tail->node = current->node;
			tail->next = NULL;
		}
		current = current->next;
	}
	return copy;
}

// geeksforgeeks.org/reverse-a-linked-list
struct List *reverse(struct List *list) {
	struct List *prev = NULL;
	struct List *current = list;
	struct List *next = NULL;
	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list = prev;
	return list;
}

struct Queue *enqueue(struct Queue *queue, struct List *path, struct Tree **visitedmovie, struct Tree **visitedactor, struct Queue **last) {
	struct List *movie = path->node->list;
	while (movie != NULL) {
		if (intsearch(*visitedmovie,movie->node->identifier)==NULL) {
			struct List *actor = movie->node->list;
			while (actor != NULL) {
				if (stringsearch(*visitedactor,actor->node->string)==NULL) {
					struct List *copy = copylist(path);
					copy = push(copy, movie->node);
					copy = push(copy, actor->node);
					struct Queue *newqueue = (struct Queue *)malloc(sizeof(struct Queue));
					newqueue->list = copy;
					newqueue->next = NULL;
					if (queue == NULL) {
						queue = newqueue;
					}
					else {
						(*last)->next = newqueue;
					}
					*last = newqueue;
					*visitedactor = stringinsert(*visitedactor, actor->node);
				}
				actor = actor->next;
			}
			*visitedmovie = intinsert(*visitedmovie, movie->node);
		}
		movie = movie->next;
	}
	deletelist(path);
	return queue;
}

struct List *dequeue(struct Queue **queue) {
	struct Queue *temp = *queue;
	struct List *ret = copylist((*queue)->list);
	*queue = (*queue)->next;
	deletelist(temp->list);
	free(temp);
	return ret;
}

struct List *bfs(struct Node *src, struct Node *dst) {
	struct List *path = NULL;
	path = push(path, src);
	struct Tree *visitedmovie = NULL;
	struct Tree *visitedactor = NULL;
	visitedactor = stringinsert(visitedactor, path->node);
	struct Queue *queue = NULL;
	struct Queue *last = NULL;
	queue = enqueue(queue, path, &visitedmovie, &visitedactor, &last);
	
	while (queue != NULL) {
		path = dequeue(&queue);
		if (path->node == dst) {
			deletequeue(queue);
			deletetree(visitedmovie);
			deletetree(visitedactor);
			path = reverse(path);
			return path;
		}
		queue = enqueue(queue, path, &visitedmovie, &visitedactor, &last);
	}
	deletequeue(queue);
	deletetree(visitedmovie);
	deletetree(visitedactor);
	deletelist(path);
	return NULL;
}
