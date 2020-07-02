#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 *
 */
typedef struct Nodee
{
    char data[500];
    struct Nodee* next;
    struct Nodee* prev;
} Nodee;
/*
 *
 */
typedef struct
{
    Nodee* head;
    Nodee* tail;
} DoublyLinkedList;
/*
 *
 */
Nodee *newNodee(char string[])
{
    Nodee *n = malloc(sizeof(Nodee));
    strcpy(n->data,string);
    n->next=NULL;
    n->prev=NULL;
    return n;
}
DoublyLinkedList* init()
{
    DoublyLinkedList *list = malloc(sizeof(DoublyLinkedList));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

void insert(DoublyLinkedList* list,char string[])
{
    Nodee *temp;
    temp = newNodee(string);
        if(list->head->data)
    {
        temp->prev = list->tail;
        list->tail->next = temp;
        list->tail = temp;
    }
    else
    {
        list->head=temp;
        list->tail=temp;
    }
}


DoublyLinkedList* convertArrayToDoublyLinkedList(char array[], int size)
{
    DoublyLinkedList *list = init();
    int i;
    Nodee *node=newNodee(array[0]);
    list->head = node;
    list->tail = node;
    Nodee *temp;
    for(i=1; i<size; i++)
    {
        temp = newNodee(array[i]);
        temp->next = NULL;
        temp->prev = list->tail;
        list->tail->next = temp;
        list->tail = temp;
    }
    return list;
}

void destroy(DoublyLinkedList* list)
{
    while(list->head!=list->tail)
    {
        list->head=list->head->next;
        free(list->head->prev);
    }
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
}

size_t length(DoublyLinkedList*  list)
{
    size_t count = 0;
    Nodee *temp;
    if(list->head !=NULL)
    {
        temp=list->head;
        while(temp!=NULL)
        {
            count++;
            temp=temp->next;
        }
    }
    return count;
}

