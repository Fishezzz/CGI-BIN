#define __STDC_WANT_LIB_EXT1__ 1
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
    
    printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
    printf("<TITLE>Response</TITLE>\n");

    lenstr = getenv("CONTENT_LENGTH");
    if (lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || len > MAXLEN)
    {
        printf("<P>Error in invocation - wrong FORM probably.</P>");
    }
    else
    {
        fgets(input, len+1, stdin);
        unencode(input+EXTRA, input+len, data);
        
        #pragma region UberStringPicker9000
        // printf("Length: %s<br>", lenstr);
        // printf("Raw input: %s<br>", input);
        // printf("Data: %s<br><br>", data);
        
        char *pLastAmp = strrchr(data, '&');
        char *pAge = pLastAmp ? pLastAmp + 1 : data;

        // printf("Tail: %s<br>", pAge);
        // printf("&pLastAmp: %i<br>len: %i<br>", &pLastAmp, strlen(pLastAmp));
        // printf("&data: %i<br>len: %i<br><br>", &data, strlen(data));

        size_t name_len = strlen(data) - strlen(pLastAmp);
        char name[name_len];
        strncpy(name, data, name_len);
        printf("Name: %s<br>", name);
        // printf("name_len: %i<br>", name_len);

        int age;
        sscanf(pAge, "age=%i", &age);
        printf("Age: %i<br>", age);
        #pragma endregion UberStringPicker9000

        unsigned timestamp = (unsigned)time(NULL);
        printf("Time: %u<br>", timestamp);
        
        unsigned long file_len = fsize(DATAFILE);
        FILE *fp = fopen(DATAFILE,"rwb");
        if (!fp)
        {
            printf("File opening failed<br>");
        }
        else
        {   
            fseek(fp, file_len-2, SEEK_SET);    // -2 voor karakter achter de laatste '}'
            // char *text;
            #ifdef __STDC_LIB_EXT1__
            // sprintf_s(text, 200, ",\n    {\n        \"timestamp\": %u,\n        \"name\n: \"%s\",\n        \"age\": %i\n    }\n]%i", timestamp, name, age, EOF);
            fprintf_s(fp, ",\n    {\n        \"timestamp\": %u,\n        \"name\n: \"%s\",\n        \"age\": %i\n    }\n]%i", timestamp, name, age, EOF);
            #endif
            // int ch;
            // while ((ch = fgetc(fp)) != EOF) {
            //     putchar(ch);
            // }
            // printf("%s", text);
            // fputs(text, fp);
            fclose(fp);
        }
        

        // int age;
        // char *name;
        //
        // if (sscanf(data, "age=%i\0", &age) != 1)
        // {
        //     printf("Name: <br>Rest: %i", age);
        // }
        // else
        // {
        //     printf("Name: <br>Age: %i", age);
        // }
        // #ifdef __STDC_LIB_EXT1__
        //     set_constraint_handler_s(ignore_handler_s);
        //     char *token;
        //     char *rest = data;
        //     while (token = strtok_s(rest, sizeof(rest), "&", &rest))
        //     {
        //         printf("token: %s<br>", token);
        //         printf("name: %s<br>", name);
        //         strncat_s(name, token, sizeof(name)+sizeof(token));
        //     }
        //     printf("name: %s<br>", name);
        // #endif
    }

    return 0;
}