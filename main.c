#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 100

// Teil A (4. Referenzbeispiel)
void my_getline(char str[], long num)
{
    char c, *strend = str + num - 1, *strtemp = str;
    if (num > 0 && str)     //stings initialisiert
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
                printf("Zeichenkette ist zu lang! Bitte nochmals eingeben:\n");
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

    for(int i = 0; i < textlength; )                 // i ist position in string
    {
        if (inword == 0)
        {
            i = i + get_others(text+i);               //schiebt i auf wortanfang
            inword = 1;                               // sind im wort
        }
        else
        {
            lettercount = get_letters(text+i);
            i = i + lettercount;
            inword = 0;
            wordcount = wordcount+1;

            if (lettercount != 0 && lettercount < 10)       // statistik
            {
                frequencies[lettercount-1] = frequencies[lettercount-1]+1;
            }
            else if (lettercount >= 10)
            {
                frequencies[9] = frequencies[9]+1;
            }
        }
    }


    printf("Wortanzahl: %ld\n", wordcount);
    printf("Statistik:\n");
    printf("------------------------\n");
    printf("Laenge   |   Haeufigkeit\n");

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
    char *ptr = text;       // zeigt auf die erste buchstabe

    textlength = strlen(text);

    for(int i = 0; i < textlength; )        // i ist position in string
    {
        if (inword == 0)
        {
            ptr = get_others_ptr(ptr);
            i = ptr-text;                      // index von wortanfang
            inword = 1;                        // sind im wort
        }
        else
        {
            ptr = get_letters_ptr(ptr);         //pointer auf dem nächsten nicht letter
            lettercount = ptr-&text[i];         // differenz: addr von nächsten nicht letter - addr das letzten wortanfangs
            i = ptr-text;
            inword = 0;
            wordcount = wordcount+1;

            if (lettercount != 0 && lettercount < 10)       // statistik
            {
                frequencies[lettercount-1] = frequencies[lettercount-1]+1;
            }
            else if (lettercount >= 10)
            {
                frequencies[9] = frequencies[9]+1;
            }
        }
    }

    printf("Wortanzahl: %ld\n", wordcount);
    printf("Statistik:\n");
    printf("------------------------\n");
    printf("Laenge   |   Haeufigkeit\n");

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

    for (int i = 0; i < textlength; i++)        // i ist position in string
    {
        isletter = isalpha(text[i]);

        if (isletter != 0)
        {
            if (inword == 0 && seenword == 1)                // prüft ob altes inword kein Wort war vor dem überschreiben (erstes aml leerlauf)
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

    printf("Nur Woerter: %s\n\n", newtext);
}

int main()
{
    char input[N], choice;
    long result;

    do
    {
        printf("Texteingabe: ");
        my_getline(input, N);

        result = get_letters(input);
        printf("Buchstaben am Anfang: %ld\n", result);

      //analyze_text(input);
        analyze_text_ptr(input);

        trim_text(input);

        printf("Nochmal (j|n)?\n");
        choice = getchar();
        while (getchar() != '\n') {;}
        printf("\n\n");
    }
    while (choice == 'j');

    return 0;
}
