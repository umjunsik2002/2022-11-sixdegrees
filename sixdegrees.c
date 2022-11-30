#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sixdegrees.h"

// $ timeout 2m ./sixdegrees <INPUT.txt> <OUTPUT.txt>


struct Node *newnode(char *string, int identifier) {
	struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
	strcpy(node->string, string);
	node->identifier = identifier;
	return node;
}

void initialize(struct Tree **movietree, struct Tree **actortree) {
	FILE *infile;
	infile = fopen("cleaned_movielist.txt", "r");
	char *buf = NULL;
	size_t buf_size = 0;
	char *string;
	struct Node *movie, *actor;
	int identifier = 1;
	while (getline(&buf, &buf_size, infile) != -1) {
		string = strtok(buf, " \r\n");
		movie = newnode(string, identifier);
		*movietree = intinsert(*movietree, movie);
		while (string != NULL) {
			string = strtok(NULL, " \r\n");
			if (string==NULL) {
				break;
			}
			if (stringsearch(*actortree, string)==NULL) {
				actor = newnode(string, 0);
				*actortree = stringinsert(*actortree, actor);
			}
			else {
				actor = stringsearch(*actortree, string);
			}
			movie->list = push(movie->list, actor);
			actor->list = push(actor->list, movie);
		}
		identifier++;
	}
	free(buf);
	fclose(infile);
}

int main(int argc, char *argv[]) {
	FILE *readfile, *writefile;
	readfile = fopen(argv[1], "r");
	writefile = fopen(argv[2], "w");
	struct Tree *movietree = NULL;
	struct Tree *actortree = NULL;
	initialize(&movietree, &actortree);
	
	char *buf = NULL;
	size_t buf_size = 0;
	char *string;
	while (getline(&buf, &buf_size, readfile) != -1) {
		string = strtok(buf, " \r\n");
		struct Node *src = stringsearch(actortree, string);
		string = strtok(NULL, " \r\n");
		struct Node *dst = stringsearch(actortree, string);
		if ((src==NULL) || (dst==NULL)) {
			fprintf(writefile, "Not present");
		}
		else if (src == dst) {
			fprintf(writefile, "%s", src->string);
		}
		else {
			struct List *path = bfs(src, dst);
			if (path != NULL) {
				struct List *current = path;
				while (current != NULL) {
					if (current->node->identifier==0) {
						fprintf(writefile, "%s", current->node->string);
					}
					else {
						fprintf(writefile, " -(%s)- ", current->node->string);
					}
					current = current->next;
				}
				deletelist(path);
			}
			else {
				fprintf(writefile, "Not present");
			}
		}
		fprintf(writefile, "\n");
	}
	free(buf);
	
	delete(movietree);
	delete(actortree);
	fclose(readfile);
	fclose(writefile);
	return 0;
}
