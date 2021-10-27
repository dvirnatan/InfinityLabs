/*****************************
*****Singly Linked List Exercises (Data Structures)
*****Author: Lior Ben Harosh
*****Date: 22/10/2021 
******************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free(), size_t */

#include "sllist_ex.h" /* node_t, Flip(), HasLoop(), FindIntersection() */

/* Data type defintions */
struct node
{
	void *data;
	struct node *next;
};

/* Function declarations */
static void TestToFlip(void);
static void TestToHasLoop(void);
static void TestToFindIntersection(void);


/* Main */
int main() 
{
	printf("\n");
	TestToFlip();
	printf("\n\n");   
	TestToHasLoop();
	printf("\n\n");
	TestToFindIntersection();
	printf("\n");
	return 0;
}

static void TestToFlip(void)
{   
   	int arr[5] = {1, 2, 3, 4, 5};
   	size_t i = 0;
   	
   	node_t *new_node;
    node_t *head = (node_t*)malloc(sizeof(node_t));
    head->data = &(arr[0]);
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[1]);
    head->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[2]);
    head->next->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[3]);
    head->next->next->next = new_node;

    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[4]);
    head->next->next->next->next = new_node;
	
    head->next->next->next->next->next = NULL;
	
    printf("Before Flip:\n");
    printf("%d(head) -> %d -> %d -> %d -> %d(tail)\n", *(int *)head->data, 
    *(int *)head->next->data, *(int *)head->next->next->data, 
    *(int *)head->next->next->next->data, *(int *)head->next->next->next->next->data);
	
	head = Flip(head);
	
    printf("After Flip:\n");
	if (new_node == head)
	{
	    printf("%d(head) -> %d -> %d -> %d -> %d(tail)\n", *(int *)head->data, 
	    *(int *)head->next->data, *(int *)head->next->next->data, 
	    *(int *)head->next->next->next->data, *(int *)head->next->next->next->next->data);	
	}
	
	for (i = 0; i < 5; ++i)
	{
		new_node = head->next;
		free(head);
		head = new_node;
	}
	
	head = NULL; new_node = NULL;
}

static void TestToHasLoop(void)
{   
   	int arr[6] = {1, 2, 3, 4, 5, 6};
	size_t i = 0;
   	
   	node_t *new_node;
   	node_t *loop_node;
    node_t *head = (node_t*)malloc(sizeof(node_t));
    head->data = &(arr[0]);
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[1]);
    head->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[2]);
    head->next->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[3]);
    head->next->next->next = new_node;
	loop_node = new_node;
	
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[4]);
    head->next->next->next->next = new_node;
	
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[5]);
    head->next->next->next->next->next = new_node;
	
	
    head->next->next->next->next->next->next = loop_node;
    
    printf("SLlist With Loop:\n");
    printf("%d(head) -> %d -> %d -> %d(loop node) -> %d -> %d -> %d(loop node) -> %d \n",
    *(int *)head->data, 
    *(int *)head->next->data, 
    *(int *)head->next->next->data, 
    *(int *)head->next->next->next->data, 
    *(int *)head->next->next->next->next->data,
    *(int *)head->next->next->next->next->next->data, 
    *(int *)head->next->next->next->next->next->next->data,
    *(int *)head->next->next->next->next->next->next->next->data);
	
	printf("HasLoop result: %d \n", HasLoop(head));

	
    head->next->next->next->next->next->next = NULL;

    printf("SLlist Without Loop:\n");
    printf("%d(head) -> %d -> %d -> %d -> %d -> %d -> %p \n",
    *(int *)head->data, 
    *(int *)head->next->data, 
    *(int *)head->next->next->data, 
    *(int *)head->next->next->next->data, 
    *(int *)head->next->next->next->next->data,
    *(int *)head->next->next->next->next->next->data, 
    (void *)head->next->next->next->next->next->next);

	printf("HasLoop result: %d \n", HasLoop(head));
    
	for (i = 0; i < 6; ++i)
	{
		new_node = head->next;
		free(head);
		head = new_node;
	}
	
	head = NULL; new_node = NULL;
}


static void TestToFindIntersection(void)
{   
	int arr[6] = {1, 2, 3, 4, 5, 6};
	int arr2[6] = {11, 12, 13, 14, 15, 16};
	int arr3[2] = {21, 22};
	size_t i = 0;
	
   	node_t *new_node;
    node_t *head1 = (node_t*)malloc(sizeof(node_t));
    node_t *head2 = (node_t *)malloc(sizeof(node_t));
	node_t *head3 = (node_t *)malloc(sizeof(node_t));
    head1->data = &(arr[0]);
    head2->data = &(arr2[0]);
 	head3->data = &(arr3[0]);
 	
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[1]);
    head1->next = new_node;
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr2[1]);
    head2->next = new_node;
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr3[1]);
    head3->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[2]);
    head1->next->next = new_node;
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr2[2]);
    head2->next->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[3]);
    head1->next->next->next = new_node;
    head2->next->next->next = new_node;
	
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[4]);
    head1->next->next->next->next = new_node;
    head3->next->next = new_node;
    
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr[5]);
    head1->next->next->next->next->next = new_node;
 
    head1->next->next->next->next->next->next = NULL; 
    
	printf("SLlist1 with intersection:\n");
    printf("%d(head) -> %d -> %d -> (*inter)%d -> %d -> %d \n",
    *(int *)head1->data, 
    *(int *)head1->next->data, 
    *(int *)head1->next->next->data, 
    *(int *)head1->next->next->next->data, 
    *(int *)head1->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->data);
    
	printf("SLlist2 with intersection:\n");
    printf("%d(head) -> %d -> %d -> (*inter)%d -> %d -> %d \n",
    *(int *)head2->data, 
    *(int *)head2->next->data, 
    *(int *)head2->next->next->data, 
    *(int *)head2->next->next->next->data, 
    *(int *)head2->next->next->next->next->data,
    *(int *)head2->next->next->next->next->next->data);
   
	printf("FindIntersection result: %d \n", *((int *)(FindIntersection(head1,head2)->data)));
 	
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr2[3]);
    head2->next->next->next = new_node;
 
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr2[4]);
    head2->next->next->next->next = new_node;
    
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = &(arr2[5]);
    head2->next->next->next->next->next = new_node;
 
    head2->next->next->next->next->next->next = NULL; 
 	
 	printf("\nSLlist1 with no intersection:\n");
    printf("%d(head) -> %d -> %d -> %d -> %d -> %d \n",
    *(int *)head1->data, 
    *(int *)head1->next->data, 
    *(int *)head1->next->next->data, 
    *(int *)head1->next->next->next->data, 
    *(int *)head1->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->data);
    
	printf("SLlist2 with no intersection:\n");
    printf("%d(head) -> %d -> %d -> %d -> %d -> %d \n",
    *(int *)head2->data, 
    *(int *)head2->next->data, 
    *(int *)head2->next->next->data, 
    *(int *)head2->next->next->next->data, 
    *(int *)head2->next->next->next->next->data,
    *(int *)head2->next->next->next->next->next->data);
   
	printf("FindIntersection result: %p \n", (void *)(FindIntersection(head1,head2)));
 
	printf("\nSLlist1 with intersection:\n");
    printf("%d(head) -> %d -> %d -> %d -> (*inter)%d -> %d \n",
    *(int *)head1->data, 
    *(int *)head1->next->data, 
    *(int *)head1->next->next->data, 
    *(int *)head1->next->next->next->data, 
    *(int *)head1->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->data);
         
   	printf("SLlist3 with intersection:\n");
    printf("%d(head) -> %d -> (*inter)%d -> %d \n",
    *(int *)head3->data, 
    *(int *)head3->next->data, 
    *(int *)head3->next->next->data, 
    *(int *)head3->next->next->next->data);

	printf("FindIntersection result: %d \n", (*(int *)(FindIntersection(head1, head3)->data)));
	
	
	head3->next->next = NULL;
	head1->next->next->next->next->next->next = head3; 
	
	
	printf("\nSLlist1 with intersection:\n");
    printf("%d(head) -> %d -> %d -> %d -> %d -> %d -> (*inter)%d\n",
    *(int *)head1->data, 
    *(int *)head1->next->data, 
    *(int *)head1->next->next->data, 
    *(int *)head1->next->next->next->data, 
    *(int *)head1->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->next->data);
         
   	printf("SLlist3 with intersection:\n");
    printf("(*inter)%d(head) -> %d \n",
    *(int *)head3->data, 
    *(int *)head3->next->data);

	printf("FindIntersection result: %d \n", (*(int *)(FindIntersection(head1, head3)->data)));

	head1->next->next->next->next->next->next = head2->next->next; 
	
	printf("\nSLlist1 with intersection:\n");
    printf("%d(head) -> %d -> %d -> %d -> %d -> %d -> (*inter)%d\n",
    *(int *)head1->data, 
    *(int *)head1->next->data, 
    *(int *)head1->next->next->data, 
    *(int *)head1->next->next->next->data, 
    *(int *)head1->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->data,
    *(int *)head1->next->next->next->next->next->next->data);
    
	printf("SLlist2 with intersection:\n");
    printf("%d(head) -> %d -> (*inter)%d -> %d -> %d -> %d \n",
    *(int *)head2->data, 
    *(int *)head2->next->data, 
    *(int *)head2->next->next->data, 
    *(int *)head2->next->next->next->data, 
    *(int *)head2->next->next->next->next->data,
    *(int *)head2->next->next->next->next->next->data);
   	
	printf("FindIntersection result: %d \n", (*(int *)(FindIntersection(head1, head2)->data)));
	
	free(head3->next); 
	free(head3); head3 = NULL;
	
	for (i = 0; i < 6; ++i)
	{
		new_node = head1->next;
		free(head1);
		head1 = new_node;
		
		new_node = head2->next;
		free(head2);
		head2 = new_node;
	}
	
	head1 = NULL; head2 = NULL; new_node = NULL;    
}


