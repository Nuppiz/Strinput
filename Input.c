#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define STRING_MAX_LENGTH   21

int running = 1;
int string_count = 0;
int strings_capacity = 20;

char** strings;

void stringInput()
{
    char input_str [STRING_MAX_LENGTH];
    
    printf("Enter a new string, limit 20 chars.\n");
    fgets(input_str, STRING_MAX_LENGTH, stdin);
    
    strings[string_count] = malloc(strlen(input_str));
    strcpy(strings[string_count], input_str);
    string_count++;
    
    if (string_count == strings_capacity)
    {
        strings_capacity *= 2;
        strings = realloc(strings, sizeof(char*) * strings_capacity);
    }
}

void stringList()
{
    int i;
    
    printf("\nThe string list contains the following items:\n");
    
    for (i = 0; i < string_count; i++)
    {
        printf("%s", strings[i]);
    }
    printf("\n%d string(s) saved.\n", string_count);
}

int stringCompare(char* searchString, char* compString)
{
    int comparison_char = 0;
    
    while (searchString[comparison_char] != '\0' || compString[comparison_char] != '\0')
    {
        if (searchString[comparison_char] != compString[comparison_char])
            return FALSE;
        comparison_char++;
    }
    return TRUE;
}

void stringSearch()
{
    char search_input [STRING_MAX_LENGTH];
    int string_index;
    int match_string = 0;
    char result = FALSE;
    
    printf("Enter a string to search from the list.\n");
    fgets(search_input, STRING_MAX_LENGTH, stdin);
    
    for (string_index = 0; string_index < string_count; string_index++)
    {
        result = stringCompare(search_input, strings[string_index]);
        if (result == TRUE)
        {
            match_string = string_index;
            printf("Found a result matching the search:\n");
            printf("%s\n", strings[match_string]);
            break;
        }
    }
    
    if (result == FALSE)
        printf("No matching strings found.\n");
}

void stringSwapper(char** str1, char** str2)
{
    char* temp [STRING_MAX_LENGTH];
    
    *temp = *str1;
    *str1 = *str2;
    *str2 = *temp;
}

void stringSwapMenu()
{
    int str1, str2;
    
    printf("Enter the index number of the first string:\n");
    scanf("%d", &str1);
    printf("Enter the index number of the second string:\n");
    scanf("%d", &str2);
    
    stringSwapper(&strings[str1], &strings[str2]);
}

void stringBubbler(char** str1, char** str2)
{
    char* temp [STRING_MAX_LENGTH];
    
    if (*str1[0] < *str2[0])
    {
        *temp = *str1;
        *str1 = *str2;
        *str2 = *temp;
    }
}

void stringBubbleSort()
{
    int string_index = 0;
    int compare_index;
    
    while (string_index < string_count)
    {
        for (compare_index = 0; compare_index < string_count; compare_index++)
        {
            stringBubbler(&strings[string_index], &strings[compare_index]);
        }
        string_index++;
    }
}

void menu()
{
    char selection;
    
    printf("-----------------------------\n");
    printf("Enter A to input a new string,\n");
    printf("B to list currently saved strings,\n");
    printf("C to search for a string in the current list,\n");
    printf("D to swap two strings on the list,\n");
    printf("or E to sort the strings on the list.\n");
    
    scanf(" %c", &selection);
    if (selection == 'A')
    {
        fflush (stdin);
        stringInput();
    }
    else if (selection == 'B')
        stringList();
    else if (selection == 'C')
    {
        fflush (stdin);
        stringSearch();
    }
    else if (selection == 'D')
    {
        fflush (stdin);
        stringSwapMenu();
    }
    else if (selection == 'E')
        stringBubbleSort();
}

int main()
{
    strings = malloc(sizeof(char*) * strings_capacity);
    
	while (running == 1)
		menu();
	return 0;
}