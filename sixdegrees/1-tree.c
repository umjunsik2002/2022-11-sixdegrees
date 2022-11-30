#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sixdegrees.h"


int height(struct Tree *tree) {
	if (tree == NULL) {
		return 0;
	}
	return tree->height;
}

int balance(struct Tree *tree) {
	if (tree == NULL) {
		return 0;
	}
	return height(tree->left) - height(tree->right);
}

int larger(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

struct Tree *rotateleft(struct Tree *tree) {
	struct Tree *parent = tree->right;
	struct Tree *child = parent->left;
	tree->right = child;
	parent->left = tree;
	tree->height = larger(height(tree->left), height(tree->right)) +1;
	parent->height = larger(height(parent->left), height(parent->right)) +1;
	return parent;
}

struct Tree *rotateright(struct Tree *tree) {
	struct Tree *parent = tree->left;
	struct Tree *child = parent->right;
	tree->left = child;
	parent->right = tree;
	tree->height = larger(height(tree->left), height(tree->right)) +1;
	parent->height = larger(height(parent->left), height(parent->right)) +1;
	return parent;
}

struct Tree *intinsert(struct Tree *tree, struct Node *node) {
	if (tree == NULL) {
		tree = (struct Tree *)malloc(sizeof(struct Tree));
		tree->node = node;
		tree->left = NULL;
		tree->right = NULL;
		tree->height = 1;
		return tree;
	}
	else if (node->identifier<tree->node->identifier) {
		tree->left = intinsert(tree->left, node);
	}
	else if (node->identifier>tree->node->identifier){
		tree->right = intinsert(tree->right, node);
	}
	else {
		return tree;
	}
	tree->height = larger(height(tree->left), height(tree->right)) +1;
	int b = balance(tree);
	if ((b>1)&&(node->identifier<tree->left->node->identifier)) {
		return rotateright(tree);
	}
	if ((b>1)&&(node->identifier>tree->left->node->identifier)) {
		tree->left = rotateleft(tree->left);
		return rotateright(tree);
	}
	if ((b<-1)&&(node->identifier>tree->right->node->identifier)) {
		return rotateleft(tree);
	}
	if ((b<-1)&&(node->identifier<tree->right->node->identifier)) {
		tree->right = rotateright(tree->right);
		return rotateleft(tree);
	}
	return tree;
}

struct Tree *stringinsert(struct Tree *tree, struct Node *node) {
	if (tree == NULL) {
		tree = (struct Tree *)malloc(sizeof(struct Tree));
		tree->node = node;
		tree->left = NULL;
		tree->right = NULL;
		tree->height = 1;
		return tree;
	}
	else if (strcmp(node->string,tree->node->string)<0) {
		tree->left = stringinsert(tree->left, node);
	}
	else if (strcmp(node->string,tree->node->string)>0){
		tree->right = stringinsert(tree->right, node);
	}
	else {
		return tree;
	}
	tree->height = larger(height(tree->left), height(tree->right)) +1;
	int b = balance(tree);
	if ((b>1)&&(strcmp(node->string,tree->left->node->string)<0)) {
		return rotateright(tree);
	}
	if ((b>1)&&(strcmp(node->string,tree->left->node->string)>0)) {
		tree->left = rotateleft(tree->left);
		return rotateright(tree);
	}
	if ((b<-1)&&(strcmp(node->string,tree->right->node->string)>0)) {
		return rotateleft(tree);
	}
	if ((b<-1)&&(strcmp(node->string,tree->right->node->string)<0)) {
		tree->right = rotateright(tree->right);
		return rotateleft(tree);
	}
	return tree;
}

struct Node *intsearch(struct Tree *tree, int identifier) {
	if (tree == NULL) {
		return NULL;
	}
	else if (tree->node->identifier > identifier) {
		return intsearch(tree->left, identifier);
	}
	else if (tree->node->identifier < identifier) {
		return intsearch(tree->right, identifier);
	}
	return tree->node;
}

struct Node *stringsearch(struct Tree *tree, char *string) {
	if (tree == NULL) {
		return NULL;
	}
	else if (strcmp(tree->node->string,string)>0) {
		return stringsearch(tree->left, string);
	}
	else if (strcmp(tree->node->string,string)<0) {
		return stringsearch(tree->right, string);
	}
	return tree->node;
}
