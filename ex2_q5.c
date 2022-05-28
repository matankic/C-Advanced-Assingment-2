// Course: Advanced C programming
// exercise 2, question 5
// file name: ex2_q5.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q5.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct list
{
	char data;
	struct list* next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
list* createElement(char data, list* next);
list* createCircleListFromString(char* str);
int compareCircleLists(list** lst1, list** lst2);
int circleListLength(list *lst);
void printList(list* lst);
void freeList(list** lst);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	int result;
	list* lst1 = NULL, *lst2 = NULL;
	char str1[] = "duezax";
	char str2[] = "zaxdue";

	// call functions:
	id_num = student_id();
	printf("[id: %lu] start main\n", id_num);
	lst1 = createCircleListFromString(str1);
	lst2 = createCircleListFromString(str2);

	// write output:
	printf("Output:\n");
	result = compareCircleLists(&lst1, &lst2);
	printList(lst1);
	printList(lst2);

	// free list:
	freeList(&lst1);
	freeList(&lst2);

	return 0;
}
#endif
// --------------------------- //


// --------------------------- //
// function implementation section:
unsigned long student_id()
{
	// return your id number,
	// for example if your id is 595207432
	// return 595207432;
	// your code:
	return 333333333;
}
// --------------------------- //


///// <summary>
///// The function receives a value from type int, 
//// and the pointer to the next element in list
///// and returns a dynamic element from type list  
///// </summary>
///// <param>char data - value from type char, the value of the element</param>
///// <param>list* next - pointer to the next value after the newly created element</param>
///// <returns>dynamic value from type list</returns>
list* createElement(char data, list* next)
{
	list* item = (list*)(malloc(sizeof(list)));
	item->data = data;
	item->next = next;
	return item;
}
// --------------------------- //

/// <summary>
/// The function receives a string array
/// and returns a newly created list
/// </summary>
/// <param>char* str - The array string</param>
/// <returns>newly created list</returns>
list* createCircleListFromString(char* str)
{
	list* head = NULL;
	list* tail = NULL;
	while (*str != '\0')
	{
		if (!head)
			head = tail = createElement((*str++), NULL);
		else
		{
			tail->next = createElement((*str++), NULL);
			tail = tail->next;
		}
	}
	if (tail)
		tail->next = head;
	return head;
}
// --------------------------- //


/// <summary>
/// The function receives a list,
/// and print its values.  
/// </summary>
/// <param>list* lst - the list</param>
/// <returns>None</returns>
void printList(list* lst)
{
	// your code:
	while (lst){
		printf("%c ", lst->data);
		lst = lst->next;
	}
	printf("\n");
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list 
/// set first element to be the pivot and split all elements in lst to small and big accordingly
/// </summary>
/// <param>list** lst1 - Pointer to the pointer of the head of the 1st circle list</param>
/// <param>list** lst2 - Pointer to the pointer of the head of the 2nd circle list</param>
/// <returns>true if both lists are circly equal</returns>
int compareCircleLists(list** lst1, list** lst2)
{
	// your code:
	int i, boolean = 0;
	int n1 = circleListLength(*lst1), n2 = circleListLength(*lst2);
	list * cur1 = *lst1, * cur2 = *lst2;
	if (n1 == n2){
		if(!n1) // both lists are empty edge case
			return 1;
		for (i = 0; i < n1; i++){
			if (cur1->data == cur2->data)
				break;
			cur1 = cur1->next;
		}
		if (i != n1){ // a common character does exist
			for (i = 0; i < n1; i++){
				if (cur1->data != cur2->data)
					break;
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			if (i == n1)
				boolean = 1;
		}
	}
	// searching for the lowest character's ASCII value on each list :
	char min1 = cur1->data, min2 = cur2->data;
	if (*lst1 != NULL){ // edge cases for each list separately
		if (n1 == 1)
			(*lst1)->next = NULL;
		else{
			for (i = 0; i < n1; i++){
				if (cur1->data < min1)
					min1 = cur1->data;
				cur1 = cur1->next;
			}
			for (i = 0; i < n1; i++){
				if (cur1->next->data == min1)
					break;
				cur1 = cur1->next;
			}
			* lst1 = cur1->next;
			cur1->next = NULL;
		}
	}
	if (*lst2 != NULL){
		if (n2 == 1)
			(*lst2)->next = NULL;
		else{
			for (i = 0; i < n2; i++){
				if (cur2->data < min2)
					min2 = cur2->data;
				cur2 = cur2->next;
			}
			for (i = 0; i < n2; i++){
				if (cur2->next->data == min2)
					break;
				cur2 = cur2->next;
			}
			* lst2 = cur2->next;
			cur2->next = NULL;
		}
	}
	return boolean;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the circle linked list,
/// and returns how many elements inside.
/// </summary>
/// <param>list* lst - Pointer to an element inside the list</param>
/// <returns>amount of elements in the circle list</returns>
int circleListLength(list* lst)
{
	// your code:
	if (lst == NULL) // edge case No.1 : no elements
		return 0;
	//if (lst->next == lst) // edge case No.2 : one element - no need
	//	return 1;
	list * cur = lst->next;
	char ch = lst->data;
	int length = 1;
	while (cur->data != ch){
		cur = cur->next;
		length++;
	}
	return length;
}
// --------------------------- //


/// <summary>
/// The function free all allocated memory of a list. 
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <returns>None</returns>
void freeList(list** lst)
{
	// your code:
	list * cur = *lst, *temp;
	while (cur){
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	* lst = NULL;
}
// --------------------------- //
