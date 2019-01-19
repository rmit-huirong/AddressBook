
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */
 
#include "addressbook_array.h"

/**
* Note this file is NOT to contain console output,
* meaning printf's are NOT to be present in this file.
*/

AddressBookArray * createAddressBookArray()
{
    /**
     * Allocates and initialises a new AddressBookArray.
     * malloc or calloc are expected to be used to create the
     * AddressBookArray memory.
     * 
     * If memory cannot be allocated for the array NULL is returned.
     * 
     * Note telephones should be initialised to NULL.
     */
	
	AddressBookArray *array;
	if((array = malloc(2 * sizeof(struct addressBookArray))) == NULL)
	{
		return NULL;
	}
	array->size = 0;
	array->telephones = NULL;
	
    return array;
}

void freeAddressBookArray(AddressBookArray * array)
{
    /**
     * Free's all telephones within the array and the AddressBookArray itself.
     */
	int i = 0;
	if(array->telephones != NULL)
	{
		for(i = 0; i < array->size; i++)
		{
			if(array->telephones[i] != NULL)
			{
				free(array->telephones[i]);
			}
		}
		free(array);
	}
	
}

Boolean addTelephone(AddressBookArray * array, char * telephone)
{
    /**
     * Adds the provided telephone to the telephones array and returns TRUE.
     * 
     * If the telephone already exists or memory cannot be allocated
     * then FALSE is returned.
     * 
     * malloc or calloc are expected to be used to create memory for
     * the new telephone - do not forget to copy the provided telephone over.
     * Here is some sample code:
     * 
     * char * newTelephone = malloc(TELEPHONE_LENGTH);
     * strcpy(newTelephone, telephone);
     * 
     * After this it is expected you use *realloc* to make the telephones
     * array grow by 1. Here is some sample code:
     * 
     * array->telephones = realloc(array->telephones,
     *                     sizeof(*array->telephones) * (array->size + 1));
     * 
     * Once the array has grown by 1 you can store the new telephone in it
     * at the end. Here is some sample code:
     * 
     * array->telephones[array->size] = newTelephone;
     * array->size++;
     */

	char * newTelephone;
	
	if((newTelephone = malloc(TELEPHONE_LENGTH)) == NULL)
	{
		return FALSE;
	}
	else
	{
		strcpy(newTelephone, telephone);
		if(array == NULL)
		{
			return FALSE;
		}
		else
		{
			if(findTelephone(array, newTelephone))
			{
				return FALSE;
			}
			array->telephones = realloc(array->telephones,
			sizeof(*array->telephones) * (array->size + 1));
			array->telephones[array->size] = newTelephone;
			array->size++;
			return TRUE;
		}
	}
}

Boolean removeTelephone(AddressBookArray * array, char * telephone)
{
   /**
    * Removes the provided telephone from the telephones array and
    * returns TRUE.
    * 
    * If the telephone does not exist or memory cannot be reallocated
    * then FALSE is returned.
    * 
    * It is expected you use *realloc* to shrink the telephones
    * array by 1. Here is some sample code:
    * 
    * array->telephones = realloc(array->telephones,
    *                     sizeof(*array->telephones) * (array->size - 1));
    * array->size--;
    * 
    * Note for this to work you will first have to ensure the telephone
    * to remove is at the end of the array.
    * 
    * Also note you will need to free(...) the removed telephone as well.
    * 
    * If you are removing the LAST telephone in the array then you will need to
    * free telephones itself and set it to NULL. Here is some sample code:
    * 
    * free(array->telephones);
    * array->telephones = NULL;
    */

	int i = 0;
	int removeIndex = 0;
	
	if(array == NULL)
	{
		return FALSE;
	}
	else
	{
		if(!findTelephone(array, telephone))
		{
			return FALSE;
		}
		if(removeIndex != array->size - 1)
		{
			for(i = removeIndex; i < array->size - 1; i++)
			{
				array->telephones[i] = array->telephones [i + 1];
			}	
		}
		array->telephones[array->size - 1] = telephone;		
		array->telephones = realloc(array->telephones,
		sizeof(*array->telephones) * (array->size - 1));
		array->size--;
		if(array->size != 0)
		{
			array->telephones[array->size] = NULL;
		}
		else
		{
			free(array->telephones);
			array->telephones = NULL;
		}
		return TRUE;
	}
}

char * findTelephone(AddressBookArray * array, char * telephone)
{
    /**
     * Returns the telephone that matches the telephone provided.
     * 
     * If no telephone exists then NULL is returned.
     */
	
	int i = 0;
	if(array != NULL)
	{
		while(i < array->size)
		{
			if(strcmp(telephone, array->telephones[i]) == 0)
			{
				return array->telephones[i];
			}
			i++;
		}
	}
    return NULL;
}
