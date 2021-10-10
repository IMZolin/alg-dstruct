#include"unrolled_list.h"

list_t* CreateHead()
{
	list_t* head = (list_t*)malloc(sizeof(list_t));
	if (head != NULL)
	{
		head->N = 0;
		head->next = NULL;
		return head;
	}
	else
	{
		return NULL;
	}
}

void PushList(list_t* last, int x)
{
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	if (tmp != NULL)
	{
		tmp->N = 1;
		tmp->data[0] = x;
		tmp->next = NULL;
		last->next = tmp;
		return;
	}
	else
	{
		return NULL;
	}
}

list_t* GetNth(list_t* head, int num) {
	int count = 0;
	while (count < num && head) {
		count += head->N;
		head = head->next;
	}
	return head;
}

list_t* PopList(list_t* head, int num)
{
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	list_t* prev = (list_t*)malloc(sizeof(list_t));
	if (num == 0)
	{
		tmp = head->next;
		free(head);
		head = tmp;
		return head;
	}
	prev = GetNth(head, num-1);
	tmp = prev->next;
	if (tmp == NULL)
	{
		prev->next = NULL;
	}
	else
	{
		prev->next = tmp->next;
	}
	
	free(tmp);
	return head;
}

list_t* GetLastNode(list_t* head)
{
	if (head->next != NULL)
	{
		while (head->next != NULL)
		{
			head = head->next;
		}
		return head;
	}
	else
	{
		return head;
	}
}

void DestroyList(list_t* head)
{
	list_t* tmp;
	while (head!= NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}

void AddItem(list_t* head, int x)
{
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	
	tmp = head;
	while (tmp != NULL)
	{
		if ((tmp->next == NULL) && (tmp->N == ARRAY_SIZE))
		{
			PushList(tmp, x);
			return;
		}

		if (tmp->N < ARRAY_SIZE)
		{
				tmp->data[tmp->N] = x;
				tmp->N++;
				return;
		}
		tmp = tmp->next;
	}
}

int FindNumberByKey(list_t* head, int key)
{
	list_t* tmp = head;
	int iterate = 0;
	
	int number = 0;
	while (tmp != NULL)
	{
		for (iterate = 0; iterate < tmp->N; iterate++)
		{
			if (tmp->data[iterate] == key)
			{
				return number;
			}
			number++;
		}
		tmp = tmp->next;
	}
	return ERROR;
}

int QuantityItems(list_t* head)
{
	list_t* tmp = head;
	int count = 0;
	while (tmp != NULL)
	{
		for (int i = 0; i < tmp->N; i++)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return count;
}

int FindItem(list_t* head, int num)
{
	list_t* tmp = head;
	int iterate = 0;
	int count = 0;
	if (num < 0)
	{
		//The element number must be non-negative
		return ERROR;
		
	}
	if (QuantityItems(tmp) < num)
	{
		//The number of elements is less than the number
		return ERROR;
	}
	while (tmp != NULL)
	{
		for (iterate = 0; iterate < tmp->N; iterate++)
		{
			if (count == num)
			{
				return tmp->data[iterate];
			}
			count++;
		}
		tmp = tmp->next;
	}
}

void DeleteItem(list_t* head, int num)
{
	list_t* tmp = head;
	tmp->N = head->N;
	int iterate = 0;
	int iterate_shift = 0;
	int counter = 0;
	if (num < 0)
	{
		//The element number must be non-negative
		return ERROR;

	}
	if (QuantityItems(tmp) < num)
	{
		//The number of elements is less than the number
		return ERROR;
	}
	while (tmp != NULL)
	{
		for (iterate = 0; iterate < tmp->N; iterate++)
		{
			counter++;
			if (counter == num)
			{
				if ((iterate != tmp->N - 1))
				{
					for (iterate_shift = iterate; iterate_shift < tmp->N - iterate - 1; iterate_shift++)
					{

						tmp->data[iterate_shift] = tmp->data[iterate_shift + 1];
					}
				}

				if (tmp->N == 1)
				{
					tmp = PopList(head, num);

				}
				tmp->N--;
				//tmp = head;
				return;
			}
		}
		tmp = tmp->next;
	}
}

int Iteration(list_t* head, int key)
{
	list_t* tmp = head;
	int iterate = 0;
	while (tmp != NULL)
	{
		for (iterate = 0; iterate < tmp->N; iterate++)
		{
			if (tmp->data[iterate] == key)
			{
				if (iterate == (tmp->N - 1))
				{
					if (tmp->next == NULL)
					{
						return ERROR;
					}
					else
					{
						return tmp->next->data[0];
					}
				}
				else
				{
					return tmp->data[iterate + 1];
				}
			}
		}
		tmp = tmp->next;
	}
	return ERROR;
}





