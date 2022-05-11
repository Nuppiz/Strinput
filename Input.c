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

void stringDelete(int delete_index)
{
    int i;

    if (delete_index == string_count)
    {
        free(strings[delete_index]);
        string_count--;
        strings_capacity--;
        strings = realloc(strings, sizeof(char*) * strings_capacity);
    }
    else
    {
        for (i = 0; i < string_count; i++)
        {
            if (i > delete_index)
            {
                stringSwapper(&strings[i], &strings[i - 1]);
            }
        }
        free(strings[string_count]);
        string_count--;
        strings_capacity--;
        strings = realloc(strings, sizeof(char*) * strings_capacity);
    }
}

void stringDeleteMenu()
{
    int string_index;
    printf("Enter the index number of the string you wish to delete.\n");
    scanf("%d", &string_index);

    stringDelete(string_index);
}

int qSortPartition(int low, int high)
{
    /* pivot is the value every other value in the array is compared to at the start of the run, it's the last value in the array
    in this program we're comparing strings, so the pivot is a char pointer */
    char* pivot = strings[high];
    /* i points to a value that is considered to be potentially greater than the pivot value */
    int i = low - 1;
    /* j is simply a running index number that goes through the entire array (or sub-array) until it reaches the "high" value */
    int j;

    /* run through the array */
    for (j = low; j < high; j++)
    {
        /* if a value smaller than the pivot is found */
        if (stringCompare(strings[j], pivot) < 0)
        {
            /* 'i' is advanced by one, and the value at that index is swapped with the value at the 'j' index */
            i++;
            stringSwapper(&strings[i], &strings[j]);
        }
    }
    /* once the array has been gone through, the current 'i' index (incremented by one) is swapped with the pivot
    i has to incremented because otherwise the program may try reading memory outside of the array */
    stringSwapper(&strings[i + 1], &strings[high]);

    /* finally, return the position of the new pivot */
    return i + 1;
}

void quickSort(int start, int end)
{
    /* partition index is the index in the larger array where it's split in half */
    int partition_index;

    /* run the loop until both sub-arrays have been fully processed (start and end indexes are the same)*/
    if (start < end)
    {
        /* calculate new partition index */
        partition_index = qSortPartition(start, end);
        /* run the sort from the beginning of the array until just before the partition index */
        quickSort(start, partition_index - 1);
        /* then the same for values after the partition index */
        quickSort(partition_index + 1, end);
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
    printf("5 to bubble sort the strings on the list,\n");
    printf("6 to search for a string in the current list (binary),\n");
    printf("7 to delete a string from the list,\n");
    printf("8 to quick sort the strings on the list.\n");
    
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
    else if (selection == 7)
    {
        fflush (stdin);
        stringDeleteMenu();
    }
    else if (selection == 8)
    {
        quickSort(0, string_count);
    }
    else
    {
        printf("Invalid choice\n");
    }
}

int main()
{
    strings = malloc(sizeof(char*) * strings_capacity);
    
	while (running == 1)
		menu();
	return 0;
}