#include "jsmn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
    FILE *json;
    jsmn_parser p;
    char buffer[1024];
    char *json_string = NULL;
    size_t complete_items = 0;

    // OPEN JSON FILE
    json = fopen("test.json", "r");
    if (json == NULL)
        return 1;

    // FIND SIZE OF JSON FILE
    fseek(json, 0, SEEK_END);
    long int size = ftell(json);
    rewind(json);

    // TURN JSON TO STRING
    json_string = malloc(sizeof(char) * size); // string that holds entire json file
    memset(buffer, 0, BUFFER_SIZE);

    while (fgets(buffer, BUFFER_SIZE, json) != NULL)
        strcat(json_string, buffer);

    // RUN JSMN THROUGH

    jsmntok_t tokens[size];
    jsmn_init(&p);

    int r = jsmn_parse(&p, json_string, sizeof(char) * size, tokens, size);

    puts(json_string);

    for (int i = 0; i < r; i++)
    {
        int key_size = tokens[i].end - tokens[i].start;
        int start = tokens[i].start;

        for (int j = 0; j < key_size; j++)
            printf("%c", json_string[j + start]);
        printf("\n", NULL);
    }

    fclose(json);

    return 0;
}