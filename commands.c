
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */
 
#include "commands.h"

/**
 * Note this file is to contain console output,
 * meaning printf's are expected to be seen in this file.
 */

AddressBookList * commandLoad(char * fileName)
{
	FILE *fp;
	char str[MAX_LINE_LENGTH + NULL_SPACE];
	char *idStr, *name, *telephone;
	Boolean idValid = TRUE, nameValid = TRUE, telValid = TRUE;
	int id = 0, idLen = 0, nameLen = 0, telLen = 0, i = 0, count = 0;
	AddressBookList *list = NULL;
	AddressBookNode *node = NULL;
	
	printf("> Opening the file %s.\n", fileName);
	fp = fopen(fileName, "r");
	printf("> Loading the file ...\n");
	if(fp == NULL) 
	{
		fprintf(stderr, "> Error: Unable to find the specified file.\n");
		return NULL;
	}
	else
	{
		list = createAddressBookList();
		while(fgets(str, sizeof str, fp) != NULL)
		{ 
			if(str[0] == HASH)
			{
				continue;
			}
			else
			{
				idStr = strtok(str, DELIM_COMMA);
				if(idStr != NULL)
				{
					if(strcmp(idStr, "") != 0)
					{
						idLen = strlen(idStr);
						i = 0;
						while(i < idLen)
						{
							if(!isdigit(idStr[i]))
							{
								idValid = FALSE;
							}
							i++;
						}
						if(idValid)
						{
							id = atoi(idStr);
							if(id < MIN_ID || id > MAX_ID)
							{
								idValid = FALSE;
							}
						}
					}
					else
					{
						idValid = FALSE;
					}
				}
				else
				{
					idValid = FALSE;
				}
				name = strtok(NULL, DELIM_COMMA);
				if(name != NULL)
				{
					if(name[strlen(name) - NULL_SPACE] == '\n')
					{
						name[strlen(name) - NULL_SPACE] = NULL_TERMINATED;	
					}
					nameLen = strlen(name);
					if(nameLen > NAME_LENGTH - NULL_SPACE)
					{
						nameValid = FALSE;
					}
				}
				else
				{
					nameValid = FALSE;
				}
				if(idValid && nameValid)
				{					
					node = createAddressBookNode(id, name);
					if(insertNode(list, node))
					{
						telephone = strtok(NULL, DELIM_COMMA);
						while(telephone != NULL)
						{
							if(telephone[strlen(telephone) - NULL_SPACE] == '\n')
							{
								telephone[strlen(telephone) - NULL_SPACE] = NULL_TERMINATED;	
							}
							telLen = strlen(telephone);
							if (telLen != 10)
							{
								telValid = FALSE;
							}
							
							else
							{	
								i = 0;
								while(i < 10)
								{
									if(!isdigit(telephone[i]))
									{
										telValid = FALSE;
									}
									i++;
								}
							}
							if(!telValid)
							{
								printf("> Error: The specified file is in the wrong format and cannot be loaded.\n");
								if(list != NULL)
								{
									freeAddressBookList(list);
									list = NULL;
								}
								fclose(fp);
								return NULL;
							}
							else
							{
								if(strcmp(telephone ,"") != 0)
								{
									addTelephone(list->tail->array,telephone);
									telephone = strtok(NULL, DELIM_COMMA);
								}
							}
						}					
						count++;
					}
				}
				else
				{
					
					printf("> Error: The specified file is in the wrong format and cannot be loaded.\n");
					if(list != NULL)
					{
						freeAddressBookList(list);
						list = NULL;
					}
					fclose(fp);
					return NULL;
				}
			}
		}
		printf("> %d phone book entries have been loaded from the file.\n", count);
		printf("> Closing the file.\n");
		fclose(fp);
		list->current = list->head;
		return list;
	}
}

void commandUnload(AddressBookList * list)
{
	if(list != NULL)
	{
		freeAddressBookList(list);
		list = NULL;
		printf("> The list is unloaded.\n");
	}
	else
	{
		printf("> Error: No list has been loaded at the moment.\n");
	}
}

void commandDisplay(AddressBookList * list)
{
	int i = 0;
	int lineNum = 1;
	int num = 23 + 15;
	int max = 4;
	int nameLen = 4;
	char totalStr[35];
	AddressBookNode * node;
	
	if(list != NULL)
	{
		if(list->head != NULL)
		{
			node = list->head;
			while(i < list->size)
			{
				nameLen = strlen(node->name);
				if(nameLen > max)
				{
					max = nameLen;
				}
				if(i != list->size - 1)
				{
					node = node->nextNode;
				}
				i++;
			}
		}
	}
	num += max;
	printf("\n");
	displayHyphen(num);
	printf("%s %-4s%s %-7s%s %-4s%s %-*s%s %-11s%s\n", BAR, POS, BAR, SERIAL, BAR, ID, BAR, max + 1, NAME, BAR, TELEPHONE, BAR);
	displayHyphen(num);
	if(list != NULL)
	{
		if(list->head != NULL)
		{
			node = list->head;
			for(lineNum = 1; lineNum < list->size + 1; lineNum++)
			{
				printf("%s", BAR);
				if(node == list->current)
				{
					printf(" %-4s", CUR);
				}
				else
				{
					printf(" %-4s", "");
				}
				nameLen = strlen(node->name);
				printf("%s %-7d%s %03d %s %-*s%s ", BAR, lineNum, BAR, node->id, BAR,  max + 1, node->name, BAR);
				if(node->array->size == 0)
				{
					printf("\n");
				}
				else
				{
					for(i = 0; i < node->array->size; i++)
					{	
						if(node->array->telephones[i] != NULL)
						{
							printf("%s", node->array->telephones[i]);
						}
						if(i != node->array->size - 1)
						{
							printf("%s", DELIM_COMMA);
						}
						else
						{
							printf("\n");
						}
					}
				}
				if(lineNum != list->size)
				{
					node = node->nextNode;
				}
			}
		}
		else
		{
			displayBlank(num);
		}
	}
	else
	{
		displayBlank(num);
	}
	displayHyphen(num);
	printf("%s", BAR);
	if(list != NULL)
	{
		sprintf(totalStr, " Total phone book entries: %d", list->size);
	}
	else
	{
		sprintf(totalStr, " Total phone book entries: 0");
	}
	printf("%-*s", num - 2, totalStr);
	printf("%s\n", BAR);
	displayHyphen(num);
}

void commandForward(AddressBookList * list, int moves)
{ 
	if(forward(list, moves))
	{
		if(moves == 0)
		{
			printf("> No movement.\n");
		}
		else if(moves == 1)
		{
			printf("> Move forward %d step successfully!\n", moves);
		}
		else
		{
			printf("> Move forward %d steps successfully!\n", moves);
		}
	}
	else
	{
		printf("> Error: Steps go beyond boundary!\n");
	}
}

void commandBackward(AddressBookList * list, int moves)
{
	if(backward(list, moves))
	{
		if(moves == 0)
		{
			printf("> No movement.\n");
		}
		else if(moves == 1)
		{
			printf("> Move backward %d step successfully!\n", moves);
		}
		else
		{
			printf("> Move backward %d steps successfully!\n", moves);
		}
	}
	else
	{
		printf("> Error: Steps go beyond boundary!\n");
	}
}

void commandInsert(AddressBookList * list, int id, char * name, char * telephone)
{
	AddressBookNode * node;
	if(list->head != NULL)
	{
		node = createAddressBookNode(id, name);
		if(insertNode(list, node))
		{
			addTelephone(list->tail->array,telephone);
			printf("> New entry has been successfully inserted!\n");
		}
		else
		{
			printf("> Error: Repeated ID!\n");
		}
	}
}

void commandAdd(AddressBookList * list, char * telephone)
{
	if(addTelephone(list->current->array, telephone))
	{
		printf("> Tel (%s) has been added successfully.\n", telephone);
	}
	else
	{
		printf("> Error: Repeated telephone number!\n");
	}
}

void commandFind(AddressBookList * list, char * name)
{
	if(findByName(list, name) != NULL)
	{
		printf("> Name: (%s) is founded.\n", name);
	}
	else
	{
		printf("> Error: Name does not exist!\n");
	}
}

void commandDelete(AddressBookList * list)
{
	if(deleteCurrentNode(list))
	{
		printf("> Current node has been deleted.\n");
	}
	else
	{
		printf("> Error: Unable to find current node.\n");
	}
}

void commandRemove(AddressBookList * list, char * telephone)
{
	if(removeTelephone(list->current->array, telephone))
	{
		printf("> Tel (%s) has been removed successfully.\n", telephone);
	}
	else
	{
		printf("> Error: Telephone number does not exist!\n");
	}
}

void commandSort(
    AddressBookList * list,
    int sort(const void * node, const void * otherNode))
{
    /* Sort the nodes within list in ascending order using the
     * provided sort function to compare nodes.
     */
}

int compareName(const void * node, const void * otherNode)
{
    /* Compare node name with otherNode name.
     * 
     * return < 0 when node name is smaller than otherNode name.
     * return 0 when the names are equal.
     * return > 0 when node name is bigger than otherNode name.
     */
    return 0;
}

int compareID(const void * node, const void * otherNode)
{
    /* Compare node id with otherNode id.
     * 
     * return < 0 when node id is smaller than otherNode id.
     * return 0 when the ids are equal.
     * return > 0 when node id is bigger than otherNode id.
     */
    return 0;
}

void commandSave(AddressBookList * list, char * fileName)
{
	FILE *fp;
	AddressBookNode * node;
	int count = 0;
	int i = 0;
	
	printf("> Opening the file %s.\n", fileName);
	fp = fopen(fileName, "w");
	printf("> Writing list content to the file ...\n");
	if(fp == NULL) 
	{
		fprintf(stderr, "> Error: Unable to create the specified file.\n");
	}
	else
	{
		if(list->head != NULL)
		{
			node = list->head;
			while(count < list->size)
			{
				fprintf(fp, "%d,%s", node->id, node->name);
				i = 0;
				if(node->array != NULL)
				{
					if(node->array->size == 0)
					{
						fprintf(fp, "\n");
					}
					else
					{	
						fprintf(fp, ",");
						while(i < node->array->size)
						{
							fprintf(fp, "%s", node->array->telephones[i]);
							if(i != node->array->size - 1)
							{
								fprintf(fp, ",");
							}
							else
							{
								fprintf(fp, "\n");
							}
							i++;
						}
					}
					if(node->nextNode != NULL)
					{
						node = node->nextNode;
					}
					count++;
				}
				else
				{
					fprintf(fp, "\n");
				}
			}
			printf("> Closing the file.\n");
		}
		else
		{
			printf("> Error: Unable to find the list.\n");
		}
		fclose(fp);
	}
}

void displayHyphen(int num)
{
	int i = 0;
	for(i = 0; i < num; i++)
	{
		printf("%s", HYPHEN);
	}
	printf("\n");
}

void displayBlank(int num)
{
	int i = 0;
	printf("%s", BAR);
	for(i = 0; i < num - 2; i++)
	{
		printf(" ");			
	}
	printf("%s\n", BAR);	
}