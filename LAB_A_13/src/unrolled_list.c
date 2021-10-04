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

list_t* PushList(list_t* last)
{
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	if (tmp != NULL)
	{
		tmp->N = 0;
		tmp->next = NULL;
		last->next = tmp;
		return tmp;
	}
	else
	{
		return NULL;
	}
}

list_t* GetNth(list_t* head, int n) {
	int k = 0;
	while (k < n && head) {
		head = head->next;
		k += head->N;
	}
	return head;
}

list_t* PopList(list_t* head, int n)
{
	list_t* tmp = (list_t*)malloc(sizeof(list_t));
	list_t* prev = (list_t*)malloc(sizeof(list_t));
	int k = 0;
	if (n == 0)
	{
		tmp = head->next;
		free(head);
		head = tmp;
		return head;
	}

	prev = GetNth(head, n-1);
	tmp = prev->next;
	if (tmp == NULL)
	{
		return head;
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

list_t* AddItem(list_t* head, int x)
{
	list_t* q = head;
	q = GetLastNode(head);
	if (q->N == ARRAY_SIZE)
	{
		PushList(q);
		q->data[0] = x;
		q->N = 1;
	}
	else
	{
		q->data[q->N] = x;
		q->N++;
	}
	head = q;
	return head;
}

int FindNumberByKey(list_t* head, int key)
{
	list_t* q = head;
	int i = 0;
	
	int n = 0;
	while (q != NULL)
	{
		for (i = 0; i < q->N; i++)
		{
			if (q->data[i] == key)
			{
				return n;
			}
			n++;
		}
		q = q->next;
	}
	return ERROR;
}

int QuantityItems(list_t* head)
{
	list_t* q = head;
	int counter = 0;
	while (q != NULL)
	{
		for (int i = 0; i < q->N; i++)
		{
			counter++;
		}
		q = q->next;
	}
	return counter;
}

int FindItem(list_t* head, int n)
{
	list_t* q = head;
	int i = 0;
	int k = 0;
	if (n < 0)
	{
		//The element number must be non-negative
		return ERROR;
		
	}
	if (QuantityItems(q) < n)
	{
		//The number of elements is less than the number
		return ERROR;
	}
	while (q != NULL)
	{
		for (i = 0; i < q->N; i++)
		{
			if (k == n)
			{
				return q->data[i];
			}
			k++;
		}
		q = q->next;
	}
}
list_t* DeleteItem(list_t* head, int n)
{
	list_t* q = head;
	int i = 0;
	int j = 0;
	int k = 0;
	if (n < 0)
	{
		//The element number must be non-negative
		return ERROR;

	}
	if (QuantityItems(q) < n)
	{
		//The number of elements is less than the number
		return ERROR;
	}
	while (q != NULL)
	{
		for (i = 0; i < q->N; i++)
		{
			if (k == n)
			{
				for (j = i; j < q->N - i - 1; j++)
				{
					q->data[j] = q->data[j + 1];
				}
				if (q->N == 1)
				{
					q = PopList(head, n);
					
				}
				q->N--;
				q = head;
				return head;
			}
			k++;
		}
		q = q->next;
	}
}

int Iteration(list_t* head, int key)
{
	list_t* q = head;
	int i = 0;
	while (q != NULL)
	{
		for (i = 0; i < q->N; i++)
		{
			if (q->data[i] == key)
			{
				if (i == (q->N - 1))
				{
					if (q->next == NULL)
					{
						return ERROR;
					}
					else
					{
						return q->next->data[0];
					}
				}
				else
				{
					return q->data[i + 1];
				}
			}
		}
		q = q->next;
	}
	return ERROR;
}





