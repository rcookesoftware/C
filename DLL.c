#define _CRT_SECURE_NO_WARNINGS
#include "DLL.h"

void addAtTheStart(nodeT** top, nodeT** end)
{
	nodeT* newNode = (nodeT*)malloc(sizeof(nodeT));

	printf("Please enter the data for the new node\n");
	scanf("%d", &newNode->data);

	newNode->PREV = NULL;
	newNode->NEXT = *top;

	if (*top != NULL)
	{
		(*top)->PREV = newNode;
	}

	*top = newNode;

	if (*end == NULL)
	{
		*end = newNode;
	}
}

void addAtEnd(nodeT** top, nodeT** end)
{
	nodeT* newNode = (nodeT*)malloc(sizeof(nodeT));
	nodeT* temp = (nodeT*)malloc(sizeof(nodeT));
	printf("Please enter the data for the new node\n");
	scanf("%d", &newNode->data);

	temp = *end;
	temp->NEXT = newNode;
	newNode->PREV = temp;
	newNode->NEXT = NULL;
	*end = newNode;
}

void deleteAtStart(nodeT** top, nodeT** end)
{
	nodeT* temp = (nodeT*)malloc(sizeof(nodeT));
	nodeT* temp2 = (nodeT*)malloc(sizeof(nodeT));

	if (*top == *end)
	{
		temp = *top;
		*top = NULL;
		*end = NULL;
		free(temp);
	}
	else if (*top != *end)
	{
		temp = *top;
		temp2 = (*top)->NEXT;
		temp2->PREV = NULL;
		*top = temp2;
		free(temp);
	}
}

void deleteAtEnd(nodeT** top, nodeT** end)
{
	nodeT* temp = (nodeT*)malloc(sizeof(nodeT));
	nodeT* temp2 = (nodeT*)malloc(sizeof(nodeT));

	if (*top == *end)
	{
		temp = *end;
		*end = NULL;
		*top = NULL;
		free(temp);
	}
	else if (*top != *end)
	{
		temp = *end;
		temp2 = (*end)->PREV;
		temp2->NEXT = NULL;
		*end = temp2;
		free(temp);
	}
}

void displayAtStart(nodeT* top)
{
	nodeT* temp;

	temp = top;

	while (temp != NULL)
	{
		printf("This value of the node is %d\n", temp->data);
		temp = temp->NEXT;
	}
}

void displayAtEnd(nodeT* end)
{
	nodeT* temp;

	temp = end;

	while (temp != NULL)
	{
		printf("This value of the node is %d\n", temp->data);
		temp = temp->PREV;
	}
}

int length(nodeT* top)
{
	int count = 0;
	nodeT* temp;

	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT;
	}
	return count;
}

void addAtPos(nodeT** top, int pos)
{
	nodeT* newNode = (nodeT*)malloc(sizeof(nodeT));
	nodeT* temp = *top;
	nodeT* temp2;
	printf("Please enter the data for the new node: ");
	scanf("%d", &newNode->data);
	for (int i = 0; i < pos - 2; i++)
	{
		temp = temp->NEXT;
	}
	temp2 = temp->NEXT;

	temp->NEXT = newNode;
	newNode->PREV = temp;
	newNode->NEXT = temp2;
	temp2->PREV = newNode;
}

bool searchItem(nodeT** top, int data)
{
	int found;
	nodeT* temp = *top;

	while (temp != NULL)
	{
		if (data == temp->data)
		{
			found = true;
			break;
		}
		else if (data != temp->data)
		{
			found = false;
		}

		temp = temp->NEXT;
	}
	return found;
}