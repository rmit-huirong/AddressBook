
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */
 
#include "addressbook_list.h"

/**
* Note this file is *NOT* to contain console output,
* meaning printf's are *NOT* to be present in this file.
*/

AddressBookList * createAddressBookList()
{
    /**
    * Allocates and initialises a new AddressBookList.
    * malloc or calloc are expected to be used to create the
    * AddressBookList memory.
    * 
    * If memory cannot be allocated for the list NULL is returned.
    * 
    * Note head, tail and current should all be initialised to NULL.
    */
	
	AddressBookList *list;
	if((list = malloc(sizeof(struct addressBookList))) == NULL)
	{
		return NULL;
	}
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
	
    return list;
}

void freeAddressBookList(AddressBookList * list)
{
    /**
     * Free's all nodes within the list and the AddressBookList itself.
     * 
     * Note the freeAddressBookNode(...) function is used to free a node.
     */
	 if(list->head != NULL)
	 {
		AddressBookNode* node = list->head;
		while(node)
		{
			AddressBookNode* next = node->nextNode;
			freeAddressBookNode(node);
			node = next;
		}
	 }
	 if(list != NULL)
	 {
		 free(list);
		 list = NULL;
	 }
}

AddressBookNode * createAddressBookNode(int id, char * name)
{
    /**
    * Allocates and initialises a new AddressBookNode.
    * malloc or calloc are expected to be used to create the
    * AddressBookNode memory.
    * 
    * Note the array of the node should also be created and initialised,
    * which should be done with the createAddressBookArray(...) function.
    * 
    * If memory cannot be allocated for the node or array NULL is returned.
    * 
    * Note previousNode and nextNode should both be initialised to NULL.
    */
	
	AddressBookNode *node;
	AddressBookArray *array = createAddressBookArray();
	if((node = malloc(sizeof(struct addressBookNode))) == NULL)
	{
		return NULL;
	}
	node->id = id;
	strcpy(node->name, name);
	node->array = array;
	node->previousNode = NULL;
	node->nextNode = NULL;
	
    return node;
}

void freeAddressBookNode(AddressBookNode * node)
{
    /**
    * Free's the array within the node and the AddressBookNode itself.
    * 
    * Note the freeAddressBookArray(...) function is used to free the array.
    */
	freeAddressBookArray(node->array);
	if(node != NULL)
	 {
		 free(node);
		 node = NULL;
	 }
}

Boolean insertNode(AddressBookList * list, AddressBookNode * node)
{
    /**
     * Inserts the node into the list and returns TRUE.
     * 
     * If the list already contains a node with the same id
     * then FALSE is returned and the node is not inserted.
     */
	 
	if(list->size == 0)
	{
		list->head = node;
	}
	else
	{
		if(findByID(list, node->id))
		{
			return FALSE;
		}
		else
		{
			node->previousNode = list->tail;
			list->tail->nextNode = node;
		}
	}
	list->tail = node;
	list->size++;
    return TRUE;
}

Boolean deleteCurrentNode(AddressBookList * list)
{
    /**
     * Delete's and free's the current node in the list and returns TRUE.
     * 
     * Note the freeAddressBookNode(...) function is used to free a node.
     * 
     * If the list has no nodes (i.e., there is no current node)
     * then FALSE is returned.
     */
    
	if(list->head == NULL || list->current == NULL)
	{
		return FALSE;
	}
	else
	{		
		AddressBookNode* preNode = list->current->previousNode;
		AddressBookNode* nextNode = list->current->nextNode;
		if(list->head == list->current)
		{
			list->head = nextNode;
		}
		if(nextNode != NULL)
		{
			nextNode->previousNode = preNode;
		}
		if(preNode != NULL)
		{
			preNode->nextNode = nextNode;
		}
		freeAddressBookNode(list->current);
		list->size--;
		if(nextNode != NULL)
		{
			list->current = nextNode;
		}
		else if(preNode != NULL)
		{
			list->current = preNode;
		}
		return TRUE;
	}
	
}

Boolean forward(AddressBookList * list, int forward)
{
    /**
     * Moves the current node forward in the list by the number provided
     * and returns TRUE.
     * 
     * If the current node cannot be moved forward by that many positions
     * then FALSE is returned and current remains unchanged.
     */
	
	AddressBookNode * currentNode = list->current;
	int i = 0;
	Boolean canMove = TRUE;
	
	for(i = 0; i < forward; i++)
	{
		if(list->current->nextNode == NULL)
		{
			canMove = FALSE;
		}
		else
		{
			list->current = list->current->nextNode;
		}
	}
	if(!canMove)
	{
		list->current = currentNode;
		return FALSE;
	}
    return TRUE;
}

Boolean backward(AddressBookList * list, int backward)
{
    /**
    * Moves the current node backward in the list by the number provided
    * and returns TRUE.
    * 
    * If the current node cannot be moved backward by that many positions
    * then FALSE is returned and current remains unchanged.
    */

    AddressBookNode * currentNode = list->current;
	int i = 0;
	Boolean canMove = TRUE;
	
	for(i = 0; i < backward; i++)
	{
		if(list->current->previousNode == NULL)
		{
			canMove = FALSE;
		}
		else
		{
			list->current = list->current->previousNode;
		}
	}
	if(!canMove)
	{
		list->current = currentNode;
		return FALSE;
	}
    return TRUE;
}

AddressBookNode * findByID(AddressBookList * list, int id)
{
    /**
     * Returns the node that matches the id provided.
     * 
     * If no node with a matching id exists then NULL is returned.
     */
	
	int i = 0;
	AddressBookNode* node = list->head;
	
	while(i < list->size)
	{
		if(id == node->id)
		{
			return node;
		}
		else
		{
			if(i != list->size - 1)
			{
				node = node->nextNode;
			}
		}
		i++;
	}
    return NULL;
}

AddressBookNode * findByName(AddressBookList * list, char * name)
{
    /**
    * Sets current to the first node that matches the name provided
    * and returns this node.
    * 
    * If no node with a matching name exists then NULL is returned
    * and current remains unchanged.
    */

	int i = 0;
	AddressBookNode* node = list->head;
	
	while(i < list->size)
	{
		if(strcmp(name, node->name) == 0)
		{
			list->current = node;
			return list->current;
		}
		else
		{
			if(i != list->size - 1)
			{
				node = node->nextNode;
			}
		}
		i++;
	}
    return NULL;
}
