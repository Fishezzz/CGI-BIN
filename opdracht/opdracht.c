#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLEN 80
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN+EXTRA+2
/* 1 for added line break, 1 for trailing NUL */
#define DATAFILE "../data/data.json"

void unencode(char *src, char *last, char *dest)
{
    for (; src != last; src++, dest++)
    {
        if (*src == '+')
        {
            *dest = ' ';
        }
        else if (*src == '%')
        {
            int code;
            if (sscanf(src+1, "%2x", &code) != 1)
            {
                code = '?';
            }
            *dest = code;
            src +=2;
        }     
        else
        {
            *dest = *src;
        }
    }
    *dest = '\n';
    *++dest = '\0';
}

unsigned long fsize(char* file)
{
    FILE * f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}

int main(void)
{
    char *lenstr;
    char input[MAXINPUT], data[MAXINPUT];
    long len;
    
    // printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
    // printf("<TITLE>Response</TITLE>\n");

    lenstr = getenv("CONTENT_LENGTH");
    if (lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || len > MAXLEN)
    {
        printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
        printf("<TITLE>Response</TITLE>\n");
        printf("<P>Error in invocation - wrong FORM probably.</P>\n");
    }
    else
    {
        fgets(input, len+1, stdin);
        unencode(input+EXTRA, input+len, data);
        
        #pragma region UberStringPicker9000
        char *pLastAmp = strrchr(data, '&');
        char *pAge = pLastAmp ? pLastAmp + 1 : data;

        size_t name_len = strlen(data) - strlen(pLastAmp);
        char name[name_len];
        strncpy(name, data, name_len);

        int age;
        sscanf(pAge, "age=%i", &age);
        #pragma endregion UberStringPicker9000

        unsigned timestamp = (unsigned)time(NULL);
        
        unsigned long file_len = fsize(DATAFILE);
        FILE *fp = fopen(DATAFILE,"r+");
        if (!fp)
        {
            printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
            printf("<TITLE>Response</TITLE>\n");
            printf("File opening failed<br>");
        }
        else
        {   
            fseek(fp, file_len-3, SEEK_SET);    // -2 voor karakter achter de laatste '}'
            fprintf(fp, "},\n    {\n        \"timestamp\": %u,\n        \"name\": \"%s\",\n        \"age\": %i\n    }\n]", timestamp, name, age);
            fclose(fp);
            printf("Location: ../../opdracht/\n");
            printf("%s%c%c", "Content-Type:text/html;charset=iso-8859-1\n", 13, 10);
        }
    }

    return 0;
}