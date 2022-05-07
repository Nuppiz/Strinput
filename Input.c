#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TRUE    101
#define FALSE   100
#define STRING_MAX_LENGTH   21

#define KEY_1   49
#define KEY_2   50
#define KEY_3   51
#define KEY_4   52
#define KEY_5   53
#define KEY_6   54

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

int stringMatch(char* string1, char* string2)
{
    int comparison_char = 0;
    
    while (string1[comparison_char] != '\0' || string2[comparison_char] != '\0')
    {
        if (string1[comparison_char] != string2[comparison_char])
            return FALSE;
        comparison_char++;
    }
    return TRUE;
}

void stringLinearSearch()
{
    char search_input [STRING_MAX_LENGTH];
    int string_index;
    int match_string = 0;
    char result = FALSE;
    
    printf("Enter a string to search from the list.\n");
    fgets(search_input, STRING_MAX_LENGTH, stdin);
    
    for (string_index = 0; string_index < string_count; string_index++)
    {
        result = stringMatch(search_input, strings[string_index]);
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

void stringBubbler(char** str1, char** str2, int char_index)
{
    char* temp [STRING_MAX_LENGTH];

    if (char_index > 0)
    {
        if (*str1[char_index] < *str2[char_index] && *str1[char_index - 1] == *str2[char_index - 1])
        {
            *temp = *str1;
            *str1 = *str2;
            *str2 = *temp;
        }
    }

    else
    {
        if (*str1[char_index] < *str2[char_index])
        {
            *temp = *str1;
            *str1 = *str2;
            *str2 = *temp;
        }
    }
}

int stringCompare(char* string1, char* string2)
{
    int comparison_char = 0;
    
    while (string1[comparison_char] != '\0' || string2[comparison_char] != '\0')
    {
        if (string1[comparison_char] != string2[comparison_char])
            return string1[comparison_char] - string2[comparison_char];
        comparison_char++;
    }
    return 0;
}

void stringBubbleSort()
{
    int string_index = 0;
    int compare_index = 0;
    char comp_result;

    while (string_index < string_count)
    {
        for (compare_index = 0; compare_index < string_count; compare_index++)
        {
            comp_result = stringCompare(strings[string_index], strings[compare_index]);

            if (comp_result < 0)
                stringSwapper(&strings[string_index], &strings[compare_index]);
        }
        string_index++;
    }
}

int stringBinarySearch(char* search_string)
{
    int low = 0;
    int high = string_count;
    int mid;

    char comp_result;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        printf("L:%d\n", low);
        printf("M:%d\n", mid);
        printf("H:%d\n", high);

        if (search_string[0] == strings[mid][0])
        {
            comp_result = stringCompare(search_string, strings[mid]);

            if (comp_result == 0)
                return mid;
            
            else if (comp_result > 0)
                low = mid + 1;

            else
                high = mid - 1;
        }

        else if (strings[mid][0] < search_string[0])
            low = mid + 1;

        else
            high = mid - 1;
    }

    return FALSE;
}

void stringBinarySearchMenu()
{
    char search_input [STRING_MAX_LENGTH];
    int result;

    printf("Enter a string to search from the list.\n");
    fgets(search_input, STRING_MAX_LENGTH, stdin);

    result = stringBinarySearch(search_input);

    if (result == FALSE)
        printf("No matching strings found.\n");

    else
    {
        printf("Found a result matching the search:\n");
        printf("%s\n", strings[result]);
    }
}

void menu()
{
    char selection;
    
    printf("-----------------------------\n");
    printf("Enter 1 to input a new string,\n");
    printf("2 to list currently saved strings,\n");
    printf("3 to search for a string in the current list (linear),\n");
    printf("4 to swap two strings on the list,\n");
    printf("5 to sort the strings on the list,\n");
    printf("or 6 to search for a string in the current list (binary).\n");
    
    scanf("%d", &selection);
    if (selection == 1)
    {
        fflush (stdin);
        stringInput();
    }
    else if (selection == 2)
        stringList();
    else if (selection == 3)
    {
        fflush (stdin);
        stringLinearSearch();
    }
    else if (selection == 4)
    {
        fflush (stdin);
        stringSwapMenu();
    }
    else if (selection == 5)
        stringBubbleSort();
    else if (selection == 6)
    {
        fflush (stdin);
        stringBinarySearchMenu();
    }     
}

int main()
{
    strings = malloc(sizeof(char*) * strings_capacity);
    
	while (running == 1)
		menu();
	return 0;
}