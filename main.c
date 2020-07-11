#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 100

// Teil A
/**
 * @see Programmieren in C ( R.Klima, S.Selberherr) https://www.springer.com/de/book/9783709103920
 */

void my_getline(char str[], long num)
{
    char c, *strend = str + num - 1, *strtemp = str;
    if (num > 0 && str)     //initializes strings
    {
        while (1)
        {
            c = getchar();
            if (c == '\n')
            {
                *strtemp = 0;
                break;
            }
            else if (strtemp < strend)
            {
                *strtemp = c;
                strtemp = strtemp + 1;
            }
            else
            {
                printf("String is too long! Please try again:\n");
                strtemp = str;
                while (getchar() != '\n') {;}
            }
        }
    }
}

long get_letters(char text[])
{
    long countLetter = 0;
    int textlength;

    textlength = strlen(text);

    for(int i = 0; i < textlength; i = i+1)
    {
        if ( (text[i] >= 65 && text[i] <= 90) ||  (text[i] >= 97 && text[i] <= 122) )
        {
            countLetter = countLetter+1;
        }
        else
        {
            return countLetter;
        }

    }
    return countLetter;
}

long get_others(char text[])
{
    long countSymb = 0;
    int textlength;

    textlength = strlen(text);

    for(int i = 0; i < textlength; i = i+1)
    {
        if ( (text[i] < 65 || text[i] > 90) && (text[i] < 97 || text[i] > 122) )
        {
            countSymb = countSymb+1;
        }
        else
        {
            return countSymb;
        }
    }
    return countSymb;
}

//Teil B
void analyze_text(char text[])
{
    int wordcount = 0, inword = 0, lettercount = 0;
    int textlength;
    int frequencies[10] = {0};

    textlength = strlen(text);

    for(int i = 0; i < textlength; )                 // i is position in a string
    {
        if (inword == 0)
        {
            i = i + get_others(text+i);               //moves i to the beginning of a word
            inword = 1;                               // is inside a wort
        }
        else
        {
            lettercount = get_letters(text+i);
            i = i + lettercount;
            inword = 0;
            wordcount = wordcount+1;

            if (lettercount != 0 && lettercount < 10)       // statistics
            {
                frequencies[lettercount-1] = frequencies[lettercount-1]+1;
            }
            else if (lettercount >= 10)
            {
                frequencies[9] = frequencies[9]+1;
            }
        }
    }


    printf("Wordcount: %ld\n", wordcount);
    printf("Statistics:\n");
    printf("------------------------\n");
    printf("Length   |   Frequency \n");

    for (int j = 1; j <= 10; j++)
    {
        if (j < 10)
        {
        printf("%ld        |   %ld\n", j, frequencies[j-1]);
        }
        else
        {
        printf("<=%ld     |   %ld\n", j, frequencies[j-1]);
        }
    }
    printf("------------------------\n");

}

//Teil C
char* get_letters_ptr(char text[])
{
    int countLetter = 0;
    int textlength;

    textlength = strlen(text);

    for(int i = 0; i < textlength; i = i+1)
    {
        if ( (text[i] >= 65 && text[i] <= 90) ||  (text[i] >= 97 && text[i] <= 122) )
        {
            countLetter = countLetter+1;
        }
        else
        {
            return &text[countLetter];
        }
    }
    return &text[countLetter];
}

char* get_others_ptr(char text[])
{
    int countSymb = 0;
    int textlength;

    textlength = strlen(text);

    for(int i = 0; i < textlength; i = i+1)
    {
        if ( (text[i] < 65 || text[i] > 90) && (text[i] < 97 || text[i] > 122) )
        {
            countSymb = countSymb+1;
        }
        else
        {
            return &text[countSymb];
        }
    }
    return &text[countSymb];
}

void analyze_text_ptr(char text[])
{
    int wordcount = 0, inword = 0, lettercount = 0;
    int textlength;
    int frequencies[10] = {0};
    char *ptr = text;       // points to the first letter

    textlength = strlen(text);

    for(int i = 0; i < textlength; )        // i is position in a string
    {
        if (inword == 0)
        {
            ptr = get_others_ptr(ptr);
            i = ptr-text;                      // index of a word beginning
            inword = 1;                        // is inside a word
        }
        else
        {
            ptr = get_letters_ptr(ptr);         // pointer to the next not letter
            lettercount = ptr-&text[i];         // difference: addr of the next not letter - addr of the last beginning of a word
            i = ptr-text;
            inword = 0;
            wordcount = wordcount+1;

            if (lettercount != 0 && lettercount < 10)       // statistics
            {
                frequencies[lettercount-1] = frequencies[lettercount-1]+1;
            }
            else if (lettercount >= 10)
            {
                frequencies[9] = frequencies[9]+1;
            }
        }
    }

    printf("Wordcount: %ld\n", wordcount);
    printf("Statistics:\n");
    printf("------------------------\n");
    printf("Length   |   Frequency\n");

    for (int j = 1; j <= 10; j++)
    {
        if (j < 10)
        {
        printf("%ld        |   %ld\n", j, frequencies[j-1]);
        }
        else
        {
        printf("<=%ld     |   %ld\n", j, frequencies[j-1]);
        }
    }
    printf("------------------------\n");

}

// Teil D
void trim_text(char text[])
{
    int textlength;
    int isletter = 0, j = 0, inword = 0, seenword = 0;

    textlength = strlen(text);

    char newtext[textlength+1];
    newtext[0] = '\0';

    for (int i = 0; i < textlength; i++)        // i is position in a string
    {
        isletter = isalpha(text[i]);

        if (isletter != 0)
        {
            if (inword == 0 && seenword == 1)                // checks that the old inword was not a word (first pass idle)
            {
                newtext[j] = ' ';
                j++;
                newtext[j] = '\0';
            }

            newtext[j] = text[i];
            j++;
            newtext[j] = '\0';

            inword = 1;
            seenword = 1;
        }
        else
        {
            inword = 0;
        }
    }

    printf("Words only: %s\n\n", newtext);
}

int main()
{
    char input[N], choice;
    long result;

    do
    {
        printf("Text input: ");
        my_getline(input, N);

        result = get_letters(input);
        printf("Letters at the beginning: %ld\n", result);

      //analyze_text(input);
        analyze_text_ptr(input);

        trim_text(input);

        printf("Again (y|n)?\n");
        choice = getchar();
        while (getchar() != '\n') {;}
        printf("\n\n");
    }
    while (choice == 'j');

    return 0;
}
