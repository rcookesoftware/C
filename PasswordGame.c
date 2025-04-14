#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int index;
    char symbol;
}AsciiMap;

bool ascii_map_func(AsciiMap* map);
bool load_ascii_map(AsciiMap* map);
void encrypt_password_to_indexes(const char* password, AsciiMap* map, int* output, int max_len);
void decrypt_indexes_to_password(int* input, AsciiMap* map, char* output);
void shuffle_array(int* array, int size);

int main() 
{
    AsciiMap map[95];
    srand(time(NULL));
    if (ascii_map_func(map))
    {
        if(load_ascii_map(map))
        {
            printf("Loaded ASCII map!\n");

            // Example: print first 5 entries
            for(int i = 0; i < 5; i++)
            {
                printf("Index: %d\tChar: %c\n", map[i].index, map[i].symbol);
            }

            char password[50];
            int encrypted_indexes[50];

            printf("Enter your password: ");
            fgets(password, sizeof(password), stdin);
            strtok(password, "\n");

            encrypt_password_to_indexes(password, map, encrypted_indexes, 50);

            printf("Encrypted Index Sequence: ");
            for (int i = 0; encrypted_indexes[i] != -1; i++)
            {
                printf("%d ", encrypted_indexes[i]);
            }
            printf("\n");

            char decrypted[50];
            decrypt_indexes_to_password(encrypted_indexes, map, decrypted);
            printf("Decrypted password: %s\n", decrypted);

            int shuffled[50];
            int size = 0;

            bool guessed[50] = { false };  // Track which letters are guessed
            int correct = 0;
            int length = strlen(password);

            while (correct < length)
            {
                printf("\nGuess a character: ");
                char guess;
                scanf(" %c", &guess);  // space before %c skips leftover newline

                // Shuffle encrypted values and show them
                for (int i = 0; i < length; i++)
                    shuffled[i] = encrypted_indexes[i];
                shuffle_array(shuffled, length);

                printf("Shuffled encrypted values: ");
                for (int i = 0; i < length; i++)
                    printf("%d ", shuffled[i]);
                printf("\n");

                // Check guess
                bool found = false;
                for (int i = 0; i < length; i++)
                {
                    if (password[i] == guess && !guessed[i])
                    {
                        guessed[i] = true;
                        correct++;
                        found = true;
                    }
                }

                if (found)

                    printf("Correct guess!\n");
                else
                    printf("Nope! Try again.\n");

                printf("Progress: ");
                for (int i = 0; i < length; i++)
                {
                    if (guessed[i])
                        printf("%c ", password[i]);
                    else
                        printf("_ ");
                }
                printf("\n");
            }

            printf("\nAll characters guessed! Password cracked!\n");

        }
        return 0;
    }
        
    return 1;
}

bool ascii_map_func()
{
    FILE* fp = fopen("ascii_map.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return false;
    }

    // Line 1: numbers 1 to 95
    for (int i = 1; i <= 95; i++) {
        fprintf(fp, "%d", i);
        if (i < 95)
            fprintf(fp, " ");
    }
    fprintf(fp, "\n");

    // Line 2: printable ASCII characters (codes 32 to 126)
    for (int i = 32; i <= 126; i++) {
        fprintf(fp, "%c", i);
        if (i < 126)
            fprintf(fp, " ");
    }
    fprintf(fp, "\n");

    fclose(fp);
    printf("ascii_map.txt created!\n");
    return true;
}

bool load_ascii_map(AsciiMap* map)
{
    FILE* fp = fopen("ascii_map.txt", "r");
    if(fp == NULL)
    {
        printf("Could not open acsii_map.txt\n");
        return false;
    }

    // Temporary buffers to hold both lines
    char index_line[500];
    char char_line[500];

    fgets(index_line, sizeof(index_line), fp);
    fgets(char_line, sizeof(char_line), fp);
    fclose(fp);

    // Use strtok to split the number line
    char* token = strtok(index_line, " ");
    int i = 0;
    while(token != NULL && i < 95)
    {
        map[i].index = atoi(token);
        token = strtok(NULL, " ");
        i++;
    }

    // Now load characters one by one
    i = 0;
    token = strtok(char_line, " ");
    while(token != NULL && i < 95)
    {
        map[i].symbol = token[0];
        token = strtok(NULL, " ");
        i++;
    }
    return true;
}

void encrypt_password_to_indexes(const char* password, AsciiMap* map, int* output, int max_len)
{
    int i = 0;
    while (password[i] != '\0' && i < max_len - 1)
    {
        char current = password[i];
        bool found = false;

        for (int j = 0; j < 95; j++)
        {
            if (map[j].symbol == current)
            {
                int base_index = map[j].index;
                int transformed = (base_index * 7) + 13;
                output[i] = transformed;
                found = true;
                break;
            }
        }

        if (!found)
        {
            printf("Character '%c' not in Ascii Map!\n", current);
            output[i] = -1;
        }
        i++;
    }
    output[i] = -1;
}

void decrypt_indexes_to_password(int* input, AsciiMap* map, char* output)
{
    int i = 0;
    while (input[i] != -1)
    {
        int original_index = (input[i] - 13) / 7;

        for (int j = 0; j < 95; j++)
        {
            if (map[j].index == original_index)
            {
                output[i] = map[j].symbol;
                break;
            }
        }
        i++;
    }
    output[i] = '\0';
}

void shuffle_array(int* array, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}