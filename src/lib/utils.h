#include "str_utils.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

struct candidate
{
    // Declaration of the structure variables
    bool removed;
    int id;
    // Name and surname must be a maximum of 20 characters
    char firstName[20];
    char lastName[20];
    char birthDate[11]; // Array must be of 11 chars to accomodate for the \0 terminator.
    bool employed;
    float salary;
};

// Functions declaration
char *convertDateToSql(char *);

int addNewCandidate(char *, struct candidate *, int);
int evaluateEntriesNumber(FILE *);
int isInteger(char[]);
int *searchByLastName(struct candidate *, char *, int);
int *searchByName(struct candidate *, int[], char *, int);

void convertDbToCsv(char *, int, struct candidate *);
void format(char *, int, struct candidate *);
void formatDateInSQL(char *, int, struct candidate *);
void printCandidate(struct candidate *, int);
void printInOrder(struct candidate *, int, int);
void removeCandidate(struct candidate *, int);
void updateDatabase(FILE *, struct candidate *, int, char *);
void writeOnTextFile(FILE *, int i, struct candidate *);

// v: counter
int v;

void writeOnTextFile(FILE *fp, int i, struct candidate *candidates)
{
    fprintf(
        fp, "\n%d,%s,%s,%s,%d,%.2f,%d",
        candidates[i].id,
        candidates[i].firstName,
        candidates[i].lastName,
        candidates[i].birthDate,
        candidates[i].employed,
        candidates[i].salary,
        candidates[i].removed);
}

void updateDatabase(FILE *fp, struct candidate *candidates, int nCand, char *filename)
{
    fp = fopen(filename, "r+");
    for (int i = 0; i < nCand; i++)
    {
        writeOnTextFile(fp, i, candidates);
    }
    fseek(fp, 0, SEEK_END);
}
// Search for a candidate into the struct (case insensitive)
// I: Array of struct candidate, candidate Last Name, number of entries
// O: Index of the candidate in array or -1 if not found
int *searchByLastName(struct candidate *candidates, char *lastName, int nEntries)
{
    char tmpLastName[20];
    int i = 0, cont = 0;
    int *index = malloc(nEntries * sizeof(int));
    for (int y = 0; y < nEntries; y++)
    {
        index[y] = -100;
    }
    index[0] = -1;
    // Transform input to lower case
    while (lastName[i] != '0' && i < 20)
    {
        lastName[i] = tolower(lastName[i]);
        i++;
    }
    i = 0;
    do
    {
        // Transform lastName to lower case
        if (candidates[i].removed == 0)
        {
            for (int j = 0; j < sizeof(tmpLastName) / sizeof(char); j++)
            {
                tmpLastName[j] = tolower(candidates[i].lastName[j]);
            }
            if (strcmp(lastName, tmpLastName) == 0)
            {
                index[cont] = i;
                cont += 1;
            }
        }
        i++;
    } while (i < nEntries);
    return index;
}
int *searchByName(struct candidate *candidates, int index[], char *name, int len)
{
    // Transform input to lower case
    int i = 0;
    char tmpName[20];
    while (name[i] != '0' && i < 20)
    {
        name[i] = tolower(name[i]);
        i++;
    }
    i = 0;
    int *indexName = malloc(len * sizeof(int));
    indexName[0] = -1;
    for (int y = 1; y < len; y++)
    {
        indexName[y] = -100;
    }
    int cont = 0;
    do
    {
        // Transform lastName to lower case

        for (int j = 0; j < sizeof(tmpName) / sizeof(char); j++)
        {
            tmpName[j] = tolower(candidates[index[i]].firstName[j]);
        }
        if (strcmp(name, tmpName) == 0)
        {
            indexName[cont] = index[i];
            cont += 1;
        }
        i++;
    } while (i < len);
    return indexName;
}
// Function that prints the chosen candidate
void printCandidate(struct candidate *candidates, int i)
{
    if (candidates[i].employed == 1)
    {
        printf("%s %s %s Salary: %.2f", candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].salary);
    }
    else
    {
        printf("%s %s %s (Not employed)", candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate);
    }
    printf("\n");
}
// Function that sets removed equals to 1 to the chosen candidate
void removeCandidate(struct candidate *candidates, int i)
{
    candidates[i].removed = 1;
}
int evaluateEntriesNumber(FILE *fp)
{
    char ch[100];
    int lines = 0;
    int num = 0;
    rewind(fp);
    // While the lines is not NULL increase the counter variable;
    while (fgets(ch, sizeof(ch), fp) != NULL)
    {
        lines++;
    }
    return lines;
}
// Print the struct array on the text file, each field separated by commas
void convertDbToCsv(char *filename, int nCand, struct candidate *candidates)
{
    FILE *fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < nCand; ++i)
    {
        writeOnTextFile(fp, i, candidates);
    }
    fclose(fp);
}

// Add a new candidate to the struct array and return the updated number of entries
int addNewCandidate(char *filename, struct candidate *candidates, int nCand)
{
    FILE *fp;
    char str[11];
    bool check = 1;
    char temp[5];
    // Reopen the file in append mode
    fp = fopen(filename, "a");
    nCand++;
    int i = nCand - 1; // Last position of the array
    candidates[i].removed = 0;
    candidates[i].id = nCand;
    for (int a = 0; a < 20; a++)
    {
        candidates[i].firstName[a] = '\0';
        candidates[i].lastName[a] = '\0';
    }
    v = 0;
    do
    {
        if (v > 0)
            printf("Invalid last name!\n");
        printf("First name: ");
        scanf(" %20[^\n]", candidates[i].firstName);
        v = +1;
    } while (strlen(candidates[i].firstName) < 2 || strlen(candidates[i].firstName) > 19);
    candidates[i].firstName[0] = toupper(candidates[i].firstName[0]);
    int j = 1;
    while (j < 19)
    {
        if (candidates[i].firstName[j] == ' ')
        {
            if (candidates[i].firstName[j + 1] != '\0')
            {
                candidates[i].firstName[j + 1] = toupper(candidates[i].firstName[j + 1]);
            }
            j += 2;
        }
        else
        {
            candidates[i].firstName[j] = tolower(candidates[i].firstName[j]);
            j += 1;
        }
    }
    v = 0;
    do
    {
        if (v > 0)
            printf("Invalid last name!\n");
        printf("Last name: ");
        scanf(" %20[^\n]", candidates[i].lastName);
        v = +1;
    } while (strlen(candidates[i].lastName) < 2 || strlen(candidates[i].lastName) > 19);
    candidates[i].lastName[0] = toupper(candidates[i].lastName[0]);
    j = 1;
    while (j < 19)
    {
        if (candidates[i].lastName[j] == ' ')
        {
            if (candidates[i].lastName[j + 1] != '\0')
            {
                candidates[i].lastName[j + 1] = toupper(candidates[i].lastName[j + 1]);
            }
            j += 2;
        }
        else
        {
            candidates[i].lastName[j] = tolower(candidates[i].lastName[j]);
            j += 1;
        }
    }
    int ok = 1;
    v = 0;
    printf("Birth date [dd-mm-yyyy]: ");
    scanf("%s", str);

    strcpy(candidates[i].birthDate, convertDateToSql(str));

    char choice;
    do
    {
        printf("Is the candidate employed? [y/n] ");
        scanf(" %c", &choice);
        if (choice == 'y')
        {
            candidates[i].employed = 1;
            printf("Salary: ");
            scanf("%f", &candidates[i].salary);
            writeOnTextFile(fp, i, candidates);
        }
        else if (choice == 'n')
        {
            candidates[i].employed = 0;
            candidates[i].salary = 0.0;
            writeOnTextFile(fp, i, candidates);
        }
        else
        {
            printf("Invalid value\n");
        }
    } while (choice != 'y' && choice != 'n');
    fclose(fp);
    return nCand;
}

void formatDateInSQL(char *filename, int nCand, struct candidate *candidates)
{
    FILE *fp;
    fp = fopen(filename, "w");
    char *elements[3], *p, newDate[11];
    int i, j = 0;
    for (i = 0; i < nCand; i++)
    {
        p = strtok(candidates[i].birthDate, "/");
        while (p != NULL)
        {
            elements[j] = p;
            p = strtok(NULL, "/");
            j++;
        }
        j = 0;
        strcpy(newDate, "");
        strcat(newDate, elements[2]);
        strcat(newDate, "-");
        strcat(newDate, elements[1]);
        strcat(newDate, "-");
        strcat(newDate, elements[0]);

        strcpy(candidates[i].birthDate, newDate);

        writeOnTextFile(fp, i, candidates);
    }
    fclose(fp);
}
int isInteger(char *input)
{
    int intero = 1;
    for (int i = 0; i < 10 && input[i] != '\0' && intero == 1; i++)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            intero = 0;
        }
    }
    return intero;
}

void format(char *filename, int nCand, struct candidate *candidates)
{
    char choice[10];
    int inputConverted;
    bool exit = 1;

    do
    {
        printf("What would you like to do?:\n1. Separate values with comma;\n2. change data form in mySQL compatible;\n3. Exit.\n");
        do
        {
            printf("Insert: ");
            scanf("%s", &choice);
            inputConverted = atoi(choice);
            if ((inputConverted < 1 || inputConverted > 3) || isInteger(choice) == 0)
            {
                printf("Invalid value.\n");
            }
        } while ((inputConverted < 1 || inputConverted > 3) || isInteger(choice) == 0);

        switch (inputConverted)
        {
        case 1:
            convertDbToCsv(filename, nCand, candidates);
            break;

        case 2:
            formatDateInSQL(filename, nCand, candidates);
            break;

        case 3:
            exit = 0;
            break;
        }
    } while (exit == 1);
}

void printInOrder(struct candidate *candidates, int removed, int nCandidates)
{
    char orderName[nCandidates][40];
    int orderPosition[nCandidates];
    int cont = 0;
    int i;
    for (i = 0; i < nCandidates; i++)
    {
        if (candidates[i].removed == removed)
        {
            strcpy(orderName[cont], candidates[i].firstName);
            strcpy(orderName[cont] + strlen(candidates[i].firstName), candidates[i].lastName);
            orderPosition[cont] = i;
            cont++;
        }
    }

    if (cont <= 0)
    {
        printf("No candidates found.\n");
    }
    else
    {
        // Sort
        int j, temp1;
        char temp[40];
        for (i = 0; i < cont - 1; i++)
        {
            for (j = i + 1; j < cont; j++)
            {
                if (strcmp(orderName[i], orderName[j]) > 0)
                {
                    strcpy(temp, orderName[i]);
                    strcpy(orderName[i], orderName[j]);
                    strcpy(orderName[j], temp);
                    temp1 = orderPosition[i];
                    orderPosition[i] = orderPosition[j];
                    orderPosition[j] = temp1;
                }
            }
        }

        for (i = 0; i < cont; i++)
        {
            printCandidate(candidates, orderPosition[i]);
        }
    }
}
// Converts any date to SQL format
// Input: any date separated with '-' and 4 digits year
// Output: the same date formatted in yyyy-mm-dd
char *convertDateToSql(char *str)
{
    int j, i;
    char *token;
    char *str2 = (char *)malloc(sizeof(char) * 11);
    strcpy(str2, "");

    // Insert the first token in 'token'
    token = strtok(str, "-");
    // Create an array of 3 String
    char *strData[3];

    //  For every string allocate 5 char
    for (i = 0; i < 3; i++)
    {
        strData[i] = malloc(sizeof(char) * 5);
    }
    //  Cut the date and save every piece of it in strData
    //  Copy the first token in strData
    strcpy(strData[0], str);

    //  Copy the last two tokens of the date in strData[1,2]
    for (i = 1; i <= 2; i++)
    {
        // Get the sequence of str( data ) till the first '-' met and save it in token
        token = strtok(NULL, "-");
        strcpy(strData[i], token);
    }

    for (j = 2; j >= 0; j--)
    {
        switch (j)
        {
        case 0:
        {
            // If it is the year, save it to strData[2]
            // atoi = casting to int
            if (atoi(strData[j]) > 31 && strlen(strData[j]) == 4)
            {
                swapStr(strData[0], strData[2]);
            }
        }
        break;

        case 1:
        {
            // If it is the day, save it to strData[0]
            if (atoi(strData[j]) > 12 && atoi(strData[j]) < 31)
            {
                swapStr(strData[0], strData[1]);
            }
            // If it is the year, save it to strData[2]
            if (atoi(strData[j]) > 31 && strlen(strData[j]) == 4)
            {
                swapStr(strData[2], strData[1]);
            }
        }
        break;

        case 2:
        {
            // If it is the day, save it to strData[0]
            if (atoi(strData[j]) > 12 && atoi(strData[j]) < 31)
            {
                swapStr(strData[0], strData[2]);
            }
        }
        break;
        }
    }

    // Swap the day with the year ( dd mm yyyy -> yyyy mm dd )
    swapStr(strData[0], strData[2]);

    // Compose the string, joining strData[] with '-'
    // concatenation of str2,strData[] and '-' to get ( yyyy-mm-dd )
    for (j = 0; j < 3; j++)
    {
        strcat(str2, strData[j]);
        if (j < 2)
            strcat(str2, "-");
    }

    return str2;
}