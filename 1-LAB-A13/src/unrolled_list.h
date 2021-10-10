#pragma once
#include <stdlib.h>
#include <stdio.h>
#define ARRAY_SIZE 5
#define ERROR -1
#pragma warning(disable : 4996)

/*
*@brief Unrolled linked list
*@param N - The current number of elements in the array
*@param data - The list item is an array
*@param next - Pointer to the next node
*/
typedef struct list_t {
	int N;
	struct list_t* next;
	int data[ARRAY_SIZE]; 
}list_t;

//*Additional (intermediate) functions*
/*
*@brief Create a head (pointer to the beginning of the list)
*/
list_t* CreateHead();

/*
*@brief Add a list node
*@param last - Pointer to the last element
*/
void PushList(list_t* last, int x);

/*
*@brief Get Nth node
*@param head - Pointer to the first element
*@param n - The number of the item to be deleted
*/
list_t* GetNth(list_t* head, int num);

/*
*@brief Delete a list node
*@param head - Pointer to the first element
*@param n - The number of the item to be deleted
*/
list_t* PopList(list_t* head, int num);

/*
*@brief Get the last item
*@param head - Pointer to the first element
*/
list_t* GetLastNode(list_t* head);

/*
*@brief Completely deletes the list
*@param head - Pointer to the first element
*/
void DestroyList(list_t* head);

//*Main functions*
/*
*@brief Add an item to a list (to an array)
*@param p - List pointer
*@param x - New element(integer)
*/
void AddItem(list_t* head, int x);

/*
*@brief Find the item number by key
*@param p - List pointer
*@param key - Key
*/
int FindNumberByKey(list_t* head, int key);

/*
*@brief Count the number of elements
*@param p - List pointer
*/
int QuantityItems(list_t* head);

/*
*@brief Find the item with the specified number
*@param p - List pointer
*@param n - Item number
*/
int FindItem(list_t* head, int n);

/*
*@brief Delete an item with the specified number
*@param p - List pointer
*@param n - Item number
*/
void DeleteItem(list_t* head, int n);

/*
*@brief For a given element, find the next one (iteration)
*@param p - List pointer
*@param key - Key
*/
int Iteration(list_t* head, int key);







