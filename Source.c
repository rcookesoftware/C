#define _CRT_SCURE_NO_WARNINGS
#include "DLL.h"
void main()
{
	nodeT* headPtr = NULL;
	nodeT* tailPtr = NULL;
	nodeT* newNode;
	nodeT* prev = NULL;
	int position = 0, data;

	while (menu() != -1)
	{
		switch(menu())
		{
		case 1: addAtTheStart(&headPtr, &tailPtr);
			break;
		case 2: addAtEnd(&headPtr, &tailPtr);
			break;
		case 3: deleteAtStart(&headPtr, &tailPtr);
			break;
		case 4: deleteAtEnd(&headPtr, &tailPtr);
			break;
		case 5: displayAtStart(headPtr);
			break;
		case 6: displayAtEnd(tailPtr);
			break;
		case 7: printf("The length of the list is %d\n", length(headPtr));
			break;
		case 8: 
			printf("Please enter the position you want to add the new node: ");
			scanf("%d", position);
			if (position == 1)
			{
				addAtTheStart(&headPtr, &tailPtr);
			}
			else if (position == length(headPtr) + 1)
			{
				addAtEnd(&headPtr, &tailPtr);
			}
			addAtPos(&headPtr, position);
			break;
		case 9: 
			printf("Please enter the data you want to search in the list: ");
			scanf("%d", &data);
			if (searchItem(&headPtr, data))
				printf("%d was in the list\n", data);
			else printf("%d was not in the list\n", data);
			break;
		default:
			break;
		}
	}
}

int menu()
{
	int option;
	printf("Enter 1 to add a node at the beginning\n");
	printf("Enter 2 to add a node at the end\n");
	printf("Enter 3 to delete a node at the start\n");
	printf("Enter 4 to delete a node at the end\n");
	printf("Enter 5 to display the list of nodes from the start\n");
	printf("Enter 6 to display the list of nodes from the end\n");
	printf("Enter 7 to display length of list\n");
	printf("Enter 8 to insert a node at a specific location\n");
	printf("Enter 9 to search a node at a specific loaction\n");
	printf("Enter -1 to exit\n");
	scanf("%d", &option);

	return option;
}
