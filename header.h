#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>

typedef struct QNode {
	char* data;
	struct QNode* next;
}QNode;


typedef struct Queue {
	struct QNode *front, *rear;
}Queue;

struct Queue* createQueue();
int enQueue(struct Queue* q, char* data);
int deQueue(struct Queue* q);
int isempty(Queue *q);
void deleteQueue(struct Queue* q);

int stringGenerate(char *s, Queue* str,int choice, size_t*n);
int verifyString(char* s,size_t len, size_t* count, int* position, int* end_position);

int findAllFiles(char* path,Queue* files,size_t* n);
int isDirectoryExists(char *path);
int rename_file(char* old_name, char* new_name);
int fileexists(char* filename);
int copy_files(char* source_file,char* dest_file);
char *get_filename_ext(char *filename);


#endif // HEADER_H_INCLUDED
