
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */
 
#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#define STUDENT_NAME "Huirong Huang"
#define STUDENT_ID "3615907"
#define INFO "Advanced Programming Techniques, Assignment Two, Semester 1, 2017"

#define INTRO_LENGTH 270
#define FILENAME_MAX_LENGTH 70
#define COMMAND_MAX_LENGTH 80
#define COMMAND_OTHER_MAX_LENGTH 80

#define MAX_NAME_LENGTH 15
#define TEL_LENGTH 10

#define DELIM_SPACE " "
#define DELIM_END ""
#define TYPE_LENGTH 4
#define FILETYPE_TXT ".txt"


#include "commands.h"

void command_0_Valid(unsigned, AddressBookList*);

#endif
