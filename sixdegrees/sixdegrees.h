#pragma once

struct List;
struct Node {
	char string[256];
	int identifier;
	struct List *list;
};

struct List {
	struct Node *node;
	struct List *next;
};

struct Tree {
	struct Node *node;
	struct Tree *left;
	struct Tree *right;
	int height;
};

struct Queue {
	struct List *list;
	struct Queue *next;
};

struct Tree *intinsert(struct Tree *tree, struct Node *node);
struct Tree *stringinsert(struct Tree *tree, struct Node *node);
struct Node *intsearch(struct Tree *tree, int identifier);
struct Node *stringsearch(struct Tree *tree, char *string);

struct List *push(struct List *list, struct Node *node);
struct List *append(struct List *list, struct Node *node);

void deletelist(struct List *list);
void deletetree(struct Tree *tree);
void deletequeue(struct Queue *queue);
void delete(struct Tree *tree);

struct List *bfs(struct Node *src, struct Node *dst);
