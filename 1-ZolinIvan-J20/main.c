#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TABLESIZE 20000
#pragma warning(disable : 4996)

typedef struct node
{
    char* data;
    struct node* next;
} node;

unsigned int Hashify(const char* str)
{
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        hash = 31 * hash + str[i];
    }
    return hash % TABLESIZE;
}


static int Find(node* table[], const char* key)
{
    unsigned index = Hashify(key);
    const node* it = table[index];
    while (it != NULL && strcmp(it->data, key) != 0)
    {
        it = it->next;
    }
    return it != NULL;
}

int Insert(node* table[], char* key)
{
    if (!Find(table, key))
    {
        unsigned index = Hashify(key);
        node* new_node = (node*)malloc(sizeof * new_node);

        if (new_node == NULL)
            return 0;

        new_node->data = malloc((strlen(key) + 1) * sizeof(char));

        if (new_node->data == NULL)
            return 0;

        strcpy(new_node->data, key);
        new_node->next = table[index];
        table[index] = new_node;
        return 1;
    }
    return 0;
}

int Delete(node* table[], char* key)
{
    if (Find(table, key)) {
        unsigned int index = Hashify(key);
        node* it = table[index];
        node* prev = NULL;
        while (strcmp(it->data, key) != 0) {
            prev = it;
            it = it->next;
        }
        if (prev) {
            prev->next = it->next;
        }
        else { table[index] = it->next; }
    }
    return 0;
}
void nodeDestroy(node* table)
{
    node* del = table;
    while (table != NULL)
    {
        table = del->next;
        free(del);
        del = table;
    }
}
void Destroy(node* table[])
{
    if (table == NULL)
        return;
    else
    {
        for (int i = 0; i < TABLESIZE; i++)
        {
            if (table[i] != NULL)
                nodeDestroy(table[i]);
        }
    }
}

int main() {
    node* table[TABLESIZE] = { 0 };
    char value[10000] = { 0 };
    char command = '0';
    while (scanf("%c", &command) > 0) {

        if (command == 'a') {
            scanf("%s", &value);
            Insert(table, value);
        }
        if (command == 'f') {
            scanf("%s", &value);
            if (Find(table, value)) {
                printf("%s", "yes\n");
            }
            else { printf("%s", "no\n"); }
        }
        if (command == 'r') {
            scanf("%s", &value);
            Delete(table, value);
        }
        if (command == 'q')
        {
            Destroy(table);
            return 0;
        }
    }
}