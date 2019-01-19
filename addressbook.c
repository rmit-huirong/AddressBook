
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */
 
#include "addressbook.h"

/**
* This file is to contain the main menu loop and thus it will have console
* output, meaning printf's are expected to be seen in this file.
* 
* After the user enters a command, then the corresponding function is to be
* called from commands.c, e.g., "forward" corresponds to "commandForward(...)".
*/

int main(int argc, char ** argv)
{
	char introduction[INTRO_LENGTH + NULL_SPACE];
	AddressBookList *list = NULL;
	
	sprintf(introduction, "\n"
	"-----------------------------------------------------------------"
	"\nStudent name: %s"
	"\nStudent number: %s"
	"\n%s\n"
	"-----------------------------------------------------------------"
	"\n", STUDENT_NAME, STUDENT_ID, INFO);
	printf("%s", introduction);
	if(argc == 1)
	{
		command_0_Valid(FILENAME_MAX_LENGTH, list);
	}
	else
	{
		printf("\n> File name specified through the command-line argument.\n");
		list = commandLoad(argv[1]);
		command_0_Valid(FILENAME_MAX_LENGTH, list);
	}
	
    return EXIT_SUCCESS;
}

void command_0_Valid(unsigned length, AddressBookList* list)
{
	char command[COMMAND_MAX_LENGTH + EXTRA_SPACES];
	char commandOther[COMMAND_OTHER_MAX_LENGTH + EXTRA_SPACES];
	char *token;
	Boolean quitValid = FALSE;
	Boolean moveValid = TRUE;
	int i = 0;
	int moves = 0;
	int moveLen = 0;
	int newID = 0;
	int newIDLen = 0;
	Boolean newIDValid = TRUE;
	char *newName;
	int newNameLen = 0;
	char * newTel;
	int newTelLen = 0;
	Boolean newTelValid = TRUE;
	int telLen = 0;
	Boolean telValid = TRUE;
	char * tel;
	
	do
	{
		printf("\nEnter your command: ");
		fgets(command, length + EXTRA_SPACES, stdin);
		printf("\n");
		
		/* Check if the input is too long */
		if(command[strlen(command) - NULL_SPACE] != '\n')
		{
			printf(INVALID_INPUT_MESSAGE);
			readRestOfLine();
		}
		else
		{
			command[strlen(command) - NULL_SPACE] = NULL_TERMINATED;	
			strcpy(commandOther, command);
			if(strcmp(command, COMMAND_UNLOAD) != 0 && strcmp(command, COMMAND_DISPLAY) != 0 && strcmp(command, COMMAND_DELETE) != 0 && strcmp(command, COMMAND_QUIT) != 0)
			{
				token = strtok(command, DELIM_SPACE);
				if(token != NULL)
				{					
					if(strcmp(token, COMMAND_LOAD) == 0)
					{
						token = strtok(NULL, DELIM_END);
						
						if(token != NULL)
						{
							if(strcmp(FILETYPE_TXT, token + strlen(token) - TYPE_LENGTH) == 0)
							{
								if(list == NULL)
								{
									list = commandLoad(token);
								}
								else
								{
									freeAddressBookList(list);
									list = commandLoad(token);
								}
							}
							else
							{
								printf(INVALID_FILE_TYPE_MESSAGE);
							}
						}
						else
						{
							printf(INVALID_INPUT_MESSAGE);
						}
					}
					else if(strcmp(token, COMMAND_SAVE) == 0)
					{
						token = strtok(NULL, DELIM_END);
						
						if(token != NULL)
						{
							if(strcmp(FILETYPE_TXT, token + strlen(token) - TYPE_LENGTH) == 0)
							{
								if(list != NULL)
								{
									commandSave(list, token);
								}
								else
								{
									printf("> Error: No list is loaded!\n");
								}
							}
							else
							{
								printf(INVALID_FILE_TYPE_MESSAGE);
							}
						}
						else
						{
							printf(INVALID_INPUT_MESSAGE);
						}
					}
					else if(strcmp(token, COMMAND_FORWARD) == 0)
					{
						if(list == NULL)
						{
							printf("> Error: No list is loaded!\n");
						}
						else
						{
							token = strtok(NULL, DELIM_END);
							if(token != NULL)
							{
								moveLen = strlen(token);
								i = 0;
								while(i < moveLen)
								{
									if(!isdigit(token[i]))
									{
										moveValid = FALSE;
									}
									i++;
								}
								if(!moveValid)
								{
									printf("> Error: Movement is not an integer!\n");
								}
								else
								{
									moves = atoi(token);
									if(moves < list->size)
									{
										commandForward(list, moves);
									}
									else
									{
										printf("> Error: Steps go beyond boundary!\n");
									}
								}
							}
							else
							{
								printf(">Error: No moves!");
							}
							moveValid = TRUE;
						}
					}
					else if(strcmp(token, COMMAND_BACKWARD) == 0)
					{
						if(list == NULL)
						{
							printf("> Error: No list is loaded!\n");
						}
						else
						{
							token = strtok(NULL, DELIM_END);
							if(token != NULL)
							{
								moveLen = strlen(token);
								i = 0;
								while(i < moveLen)
								{
									if(!isdigit(token[i]))
									{
										moveValid = FALSE;
									}
									i++;
								}
								if(!moveValid)
								{
									printf("> Error: Movement is not an integer!\n");
								}
								else
								{
									moves = atoi(token);
									if(moves < list->size)
									{
										commandBackward(list, moves);
									}
									else
									{
										printf("> Error: Steps go beyond boundary!\n");
									}
								}
							}
							else
							{
								printf(">Error: No moves!");
							}
							moveValid = TRUE;
						}
					}
					else if(strcmp(token, COMMAND_INSERT) == 0)
					{
						if(list == NULL)
						{
							printf("> Error: No list is loaded!\n");
						}
						else
						{
							token = strtok(NULL, DELIM_COMMA);
							if(token != NULL)
							{
								newIDLen = strlen(token);
								i = 0;
								while(i < newIDLen)
								{
									if(!isdigit(token[i]))
									{
										newIDValid = FALSE;
									}
									i++;
								}
								if(newIDValid)
								{
									newID = atoi(token);
									if(newID >= 1 && newID <= 9999)
									{
										token = strtok(NULL, DELIM_COMMA);
										if(token != NULL)
										{
											newNameLen = strlen(token);
											if(newNameLen <= MAX_NAME_LENGTH)
											{
												newName = token;
												token = strtok(NULL, DELIM_END);
												if(token != NULL)
												{
													newTelLen = strlen(token);
													if(newTelLen == TEL_LENGTH)
													{
														i = 0;
														while(i < newTelLen)
														{
															if(!isdigit(token[i]))
															{
																newTelValid = FALSE;
															}
															i++;
														}
														if(newTelValid)
														{
															newTel = token;
															commandInsert(list, newID, newName, newTel);
														}
														else
														{
															printf("> Error: Invalid telephone!\n");
														}
													}
													else
													{
														printf("> Error: Invalid telephone!\n");
													}
												}
												else
												{
													printf("> Error: No telephone number!\n");
												}
											}
											else
											{
												printf("> Error: Name is too long!\n");
											}
										}
										else
										{
											printf(INVALID_INPUT_MESSAGE);
										}
									}
									else
									{
										printf("> Error: Invalid ID!\n");
									}
								}
								else
								{
									printf("> Error: Invalid ID!\n");
								}
							}
							else
							{
								printf(INVALID_INPUT_MESSAGE);
							}
							newIDValid = TRUE;
							newTelValid = TRUE;
						}
					}
					else if(strcmp(token, COMMAND_ADD) == 0)
					{
						if(list == NULL)
						{
							printf("> Error: No list is loaded!\n");
						}
						else
						{
							token = strtok(NULL, DELIM_END);
							if(token != NULL)
							{
								telLen = strlen(token);
								if(telLen == TEL_LENGTH)
								{
									i = 0;
									while(i < telLen)
									{
										if(!isdigit(token[i]))
										{
											telValid = FALSE;
										}
										i++;
									}
									if(!telValid)
									{
										printf("> Error: Invalid telephone number!\n");
									}
									else
									{
										tel = token;
										commandAdd(list, tel);
									}
								}
								else
								{
									printf("> Error: Invalid telephone number!\n");
								}
							}
							else
							{
								printf(">Error: No telephone number!\n");
							}
							telValid = TRUE;
						}
					}
					else if(strcmp(token, COMMAND_REMOVE) == 0)
					{
						if(list == NULL)
						{
							printf("> Error: No list is loaded!\n");
						}
						else
						{
							token = strtok(NULL, DELIM_END);
							if(token != NULL)
							{
								telLen = strlen(token);
								if(telLen == TEL_LENGTH)
								{
									i = 0;
									while(i < telLen)
									{
										if(!isdigit(token[i]))
										{
											telValid = FALSE;
										}
										i++;
									}
									if(!telValid)
									{
										printf("> Error: Invalid telephone number!\n");
									}
									else
									{
										tel = token;
										commandRemove(list, tel);
									}
								}
								else
								{
									printf("> Error: Invalid telephone number!\n");
								}
							}
							else
							{
								printf(">Error: No telephone number!\n");
							}
							telValid = TRUE;
						}
					}
					else if(strcmp(token, COMMAND_FIND) == 0)
					{
						if(list == NULL)
						{
							printf("> Error: No list is loaded!\n");
						}
						else
						{
							token = strtok(NULL, DELIM_END);
							if(token != NULL)
							{
								commandFind(list, token);
							}
							else
							{
								printf(">Error: Please enter a name.\n");
							}
						}
					}
					else
					{
						printf(INVALID_INPUT_MESSAGE);
					}
				}
				else
				{
					printf(INVALID_INPUT_MESSAGE);
				}
			}
			else
			{
				if(strcmp(commandOther, COMMAND_QUIT) == 0)
				{
					if(list != NULL)
					{
						freeAddressBookList(list);
						list = NULL;
					}
					printf("> Goodbye.\n\n");
					quitValid = TRUE;  
				}
				else if(strcmp(commandOther, COMMAND_UNLOAD) == 0)
				{
					commandUnload(list);
					list = NULL;
				}
				else if(strcmp(commandOther, COMMAND_DISPLAY) == 0)
				{
					if(list == NULL)
					{
						printf("> Error: No list is loaded.\n");
					}
					else
					{
						commandDisplay(list);
					}
				}
				else if(strcmp(commandOther, COMMAND_DELETE) == 0)
				{
					if(list == NULL)
					{
						printf("> Error: No list is loaded.\n");
					}
					else
					{
						commandDelete(list);
					}
				}
			}
				
		}
	}while(!quitValid);
}