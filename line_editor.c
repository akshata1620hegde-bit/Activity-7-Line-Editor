
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char lines[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

// Display document
void displayDocument()
{
    if (lineCount == 0)
    {
        printf("\nDocument is empty!\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d. %s\n", i + 1, lines[i]);
    }
}

// Insert a line
void insertLine()
{
    int position;
    char text[MAX_LENGTH];

    if (lineCount == MAX_LINES)
    {
        printf("Document is full!\n");
        return;
    }

    printf("Enter line number: ");
    scanf("%d", &position);
    getchar();

    if (position < 1 || position > lineCount + 1)
    {
        printf("Invalid line number!\n");
        return;
    }

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);
    text[strcspn(text, "\n")] = '\0';

    for (int i = lineCount; i >= position; i--)
    {
        strcpy(lines[i], lines[i - 1]);
    }

    strcpy(lines[position - 1], text);
    lineCount++;

    printf("Line inserted successfully!\n");
}

// Delete a line
void deleteLine()
{
    int position;

    if (lineCount == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("Enter line number to delete: ");
    scanf("%d", &position);

    if (position < 1 || position > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    for (int i = position - 1; i < lineCount - 1; i++)
    {
        strcpy(lines[i], lines[i + 1]);
    }

    lineCount--;

    printf("Line deleted successfully!\n");
}

// Save document
void saveFile()
{
    FILE *fp = fopen("document.txt", "w");

    if (fp == NULL)
    {
        printf("Unable to save file!\n");
        return;
    }

    for (int i = 0; i < lineCount; i++)
    {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);
    printf("Document saved successfully!\n");
}

// Load document
void loadFile()
{
    FILE *fp = fopen("document.txt", "r");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    lineCount = 0;

    while (lineCount < MAX_LINES &&
           fgets(lines[lineCount], MAX_LENGTH, fp) != NULL)
    {
        lines[lineCount][strcspn(lines[lineCount], "\n")] = '\0';
        lineCount++;
    }

    fclose(fp);
    printf("Document loaded successfully!\n");
}

// Search for a word
void searchWord()
{
    char word[MAX_LENGTH];
    int found = 0;

    printf("Enter word to search: ");
    scanf(" %199[^\n]", word);

    for (int i = 0; i < lineCount; i++)
    {
        if (strstr(lines[i], word) != NULL)
        {
            printf("Found at line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("Word not found!\n");
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n===== SIMPLE LINE EDITOR =====\n");
        printf("1. Display Document\n");
        printf("2. Insert Line\n");
        printf("3. Delete Line\n");
        printf("4. Save File\n");
        printf("5. Load File\n");
        printf("6. Search Word\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayDocument();
            break;

        case 2:
            insertLine();
            break;

        case 3:
            deleteLine();
            break;

        case 4:
            saveFile();
            break;

        case 5:
            loadFile();
            break;

        case 6:
            searchWord();
            break;

        case 7:
            printf("Exiting Editor...\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }

    } while (choice != 7);

    return 0;
}
