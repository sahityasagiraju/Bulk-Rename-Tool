#include "header.h"

/*
Creates a new node with the data contained in the parameters
*/
QNode* newNode(char* data)
{
    if(data==NULL)
    {
        return NULL;
    }

	QNode* temp = (QNode*)malloc(sizeof(QNode));
	if(temp==NULL)
    {
        return NULL;
    }

	temp->data=(char*)malloc(sizeof(char)*strlen(data) +1);
	if(temp->data==NULL)
    {
        free(temp);
        return NULL;
    }
    size_t len=strlen(data)+1;
	int ret=snprintf(temp->data,len,"%s",data);
	if(ret<0||ret>=len)
    {
        free(temp->data);
        free(temp);
        return NULL;
    }

	temp->next = NULL;
	return temp;
}

/*
Dynamically allocates memory for a Queue
*/
Queue* createQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));

	if(q==NULL)
    {
        return NULL;
    }

	q->front = q->rear = NULL;
	return q;
}


/*
Deletes all the nodes in the queue
*/
void deleteQueue(Queue* q)
{
    if(q==NULL)
    {
        return;
    }
    if(q->front==NULL)
    {
        return;
    }
    while(q->front!=NULL)
    {
        if(deQueue(q)==0)
        {
            return;
        }
    }
    free(q);
}

/*
Enqueues the given data into the queue
Returns 1 if the data can be enqueued
*/
int enQueue(Queue* q, char* data)
{
    if(q==NULL||data==NULL)
    {
        return 0;
    }

	QNode* temp = newNode(data);

	if (q->rear == NULL) 
    {
		q->front = q->rear = temp;
		return 1;
	}

	q->rear->next = temp;
	q->rear = temp;
	return 1;
}


/*
Dequeue from the given Queue
Returns 1 if the front node can be succesfully dequeued
*/
int deQueue(Queue* q)
{
    if(q==NULL)
    {
        return 0;
    }

	if (q->front == NULL)
    {
		return 0;
    }

	QNode* temp = q->front;

	q->front = q->front->next;

	if (q->front == NULL)
    {
		q->rear = NULL;
    }

    free(temp->data);
	free(temp);
	return 1;
}

/*
Checks if the given queue is empty or not
Returns 1 if Queue is empty
*/
int isempty(Queue *q)
{
    if(q==NULL)
    {
        return 0;
    }
    return (int)(q->rear == NULL);
}
