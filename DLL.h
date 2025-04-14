#ifndef DLL
#define DLL
#endif 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node* PREV;
	struct node* NEXT;
}nodeT;

void addAtTheStart(nodeT** top, nodeT** end);
void addAtEnd(nodeT** top, nodeT** end);
void deleteAtStart(nodeT** top, nodeT** end);
void deleteAtEnd(nodeT** top, nodeT** end);
void addAtPos(nodeT** top, int pos);
bool searchItem(nodeT** top, int searchItem);
void displayAtStart(nodeT* top);
void displayAtEnd(nodeT* end);
int length(nodeT* top);
int menu();

