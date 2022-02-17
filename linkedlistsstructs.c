#include <stdlib.h>
#include <stdio.h>

struct node {
	int value;
	struct node* next;
	struct node* prev;
};

typedef struct node node_t;

void printlist(node_t *head) 
{
	node_t *temp = head;

	while (temp != NULL)
	{
		printf("- %d - ", temp -> value);
		temp = temp -> next;
	}
	printf("\n");
}

node_t *create_new_node(int value)  //create a function allocates the new items
{
	node_t *result = malloc(sizeof(node_t));
	result -> value = value;
	result -> next = NULL;
	result -> prev = NULL;
	return (result);
}
// we can make simple fuctions to deal with the nodes.

//version one we have to specify it . We can simplifiet it 
// node_t *inster_at_head(node_t *head, node_t *node_to_insert)
// {
// 	node_to_insert -> next = head;
// 	return (node_to_insert);
// }
//usign double pointer we can change the value inside the function
node_t *inster_at_head(node_t **head, node_t *node_to_insert)
{
	node_to_insert -> next = *head;
	if (*head != NULL)
		(*head) -> prev = node_to_insert;
	*head = node_to_insert;
	node_to_insert -> prev = NULL;
	return (node_to_insert);
}

node_t *find_node(node_t *head, int value)
{
	node_t *tmp = head;
	while (tmp != NULL)
	{
		if (tmp -> value == value)
			return tmp;
		tmp = tmp -> next;
	}
	return NULL;
}

// inserting in middle

void insert_after_node(node_t *node_to_insert_after, node_t *newnode)
{
	newnode -> next = node_to_insert_after-> next;
	if (newnode -> next != NULL)
	{
		newnode -> next -> prev = node_to_insert_after;
	}
	newnode -> prev = node_to_insert_after;
	node_to_insert_after -> next = newnode;
}

void	remove_node(node_t **head, node_t *node_to_remove) 
{
	if (*head == node_to_remove)
	{
		*head = node_to_remove -> next;
		if (*head != NULL)
		{
			(*head) -> prev = NULL;
		}
		(*head) -> prev = NULL;
		return;
	}
	else
	{
		node_to_remove -> prev -> next = node_to_remove -> next;
		if (node_to_remove -> next != NULL)
		{
			node_to_remove -> next -> prev = node_to_remove -> prev;
		}
		node_to_remove -> next = NULL;
		node_to_remove -> prev = NULL;
		//find prev node in list
		// node_t *temp = *head;
		// while (temp != NULL && temp -> next != node_to_remove)
		// {
		// 	temp = temp -> next;
		// }
		// if (temp == NULL)
		// 	return;
		// temp -> next = node_to_remove -> next;
		// node_to_remove -> next = NULL;
	}
	return;
}


int main()
{
	//mostly used by this way
	node_t *head;
	node_t *tmp;
// so we can create a loop dooing this

	head = NULL;
	for (int i = 0; i < 10; i++)
	{
		tmp = create_new_node(i);
		//head = inster_at_head(head, tmp); with double pointer we won't need this
		inster_at_head(&head, tmp);
	}

	//lets search for a value

	tmp = find_node(head, 8);
	//printf("found what we looking or %d\n", tmp ->value);

// insert in middle
	insert_after_node(tmp, create_new_node(42));

	printlist(head);

	remove_node(&head, tmp);
	printlist(head);
	remove_node(&head, head);

	printlist(head);
	remove_node(&head, head);
	printlist(head);

	// ths whtoit making it to a fuction
	// for (int i = 0; i < 10; i++)
	// {
	// 	tmp = create_new_node(i);
	// 	tmp->next = head;
	// 	head = tmp;
	// }

// this one manually doing it
	// tmp = create_new_node(32);
	// head = tmp;
	// tmp = create_new_node(1);
	// tmp->next = head;
	// head = tmp;


	// node_t n1, n2, n3; //nodes are ot used like this
	// node_t *head; // but more when we dont know how many element we have so we
	// node_t n4;
	// node_t n5;

	// n1.value = malloc (sizeof(node_t)); // so we dinamicly allovation some memory for them
	// n2.value = 9;
	//linking them
	// head = &n5;
	// n3.next = &n4;
	// n2.next = &n1;
	// n1.next = NULL;
	
	//printlist(head);
	return 0;
}