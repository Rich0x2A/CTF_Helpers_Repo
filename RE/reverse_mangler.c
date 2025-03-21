// R.McQuesten, 2025-03-20
// Reverse Mangler Utilities
#include <stdio.h>
#include <stdlib.h>

int* get_strlen(char* s)
{
    int* len = (int*)malloc(sizeof(int));
    *len = 0;
    while (s[*len] != '\0') ++(*len);
    return len;
}

void swp(int i, int j, char* s)
{
    int* len = get_strlen(s);
    if (i < 0 || j < 0 || i >= *len || j >= *len)
    {
        printf("ERROR: index out of bounds\n");
        free(len);
        return;
    }
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}

void rev(char* s)
{
    int* len = get_strlen(s);
    for (int i = 0; i < *len / 2; ++i)
    {
        char tmp = s[i];
        s[i] = s[*len-i-1];
        s[*len-i-1] = tmp;
    }
    free(len);
}

void sort(char* s)
{
    int* len = get_strlen(s);
    for (int i = 0; i < *len - 1; ++i)
    {
        for (int j = 0; j < *len - i - 1; ++j)
        {
            if (s[j] > s[j+1])
            {
                char tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
            }
        }
    }
    free(len);
}

int* get_key()
{
    int* key = (int*)malloc(sizeof(int));
    if (key == NULL)
    {
        printf("ERROR: memory allocation failed\n");
        return NULL;
    }

    printf("ENTER XOR KEY: ");
    scanf("%i", key);
    printf("YOU ENTERED: %d\n", *key);
    return key;
}

void xor(char* s, int* key)
{
    int* len = get_strlen(s);
    for (int i = 0; i < *len; ++i) s[i] ^= *key;
    free(len);
}

void menu(char* s)
{
    char opt;
    int i, j;

    while (1)
    {
        printf("\n+---------------------------+\n");
        printf("| (0) Length                |\n");
        printf("| (1) Swap                  |\n");
        printf("| (2) Reverse               |\n");
        printf("| (3) Sort                  |\n");
        printf("| (4) XOR                   |\n");
	    printf("| (q) Quit                  |\n");
        printf("+---------------------------+\n");
        printf("ENTER MANGLER OPTION: ");
        scanf(" %c", &opt);

        if (opt == '0')
        {
            int* len = get_strlen(s);
            printf("STRING LENGTH: %d\n", *len);
            free(len);
        }

        else if (opt == '1')
        {
            printf("ENTER INDEX 1: ");
            scanf("%d", &i);
            printf("ENTER INDEX 2: ");
            scanf("%d", &j);
            swp(i, j, s);
            printf("SWAPPED STRING: %s\n", s);
        }

        else if (opt == '2')
        {
            rev(s);
            printf("REVERSED STRING: %s\n", s);
        }

        else if (opt == '3')
        {
            sort(s);
            printf("SORTED STRING: %s\n", s);
        }

        else if (opt == '4')
        {
            int* key = get_key();
            if (key != NULL)
            {
                xor(s, key);
                printf("STRING XORed WITH KEY %#x: %s\n", *key, s);
                free(key);    
            }         
        }

        else if (opt == 'q')
        {
            printf("THANKS FOR MANGLING, GOODBYE\n");
            break;
        }

        else
        {
            printf("ERROR: invalid option\n");
        }
    }
}

int main()
{
    char s[100];
    printf("ENTER INITIAL STRING: ");
    scanf(" %99[^\n]", s);
    menu(s);
    return 0;
}