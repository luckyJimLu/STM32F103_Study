/* Minimal cJSON implementation stub for STM32 */

#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

const char *cJSON_Version(void)
{
    return "1.7.15";
}

cJSON *cJSON_CreateObject(void)
{
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item)
    {
        memset(item, 0, sizeof(cJSON));
        item->type = cJSON_Object;
    }
    return item;
}

cJSON *cJSON_CreateArray(void)
{
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item)
    {
        memset(item, 0, sizeof(cJSON));
        item->type = cJSON_Array;
    }
    return item;
}

cJSON *cJSON_CreateString(const char *string)
{
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item)
    {
        memset(item, 0, sizeof(cJSON));
        item->type = cJSON_String;
        item->valuestring = (string != NULL) ? strdup(string) : NULL;
    }
    return item;
}

cJSON *cJSON_CreateNumber(double num)
{
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item)
    {
        memset(item, 0, sizeof(cJSON));
        item->type = cJSON_Number;
        item->valuedouble = num;
        item->valueint = (int)num;
    }
    return item;
}

cJSON *cJSON_CreateBool(int b)
{
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item)
    {
        memset(item, 0, sizeof(cJSON));
        item->type = b ? cJSON_True : cJSON_False;
    }
    return item;
}

/* NOTE: cJSON_Parse and cJSON_Print require a full JSON tokenizer. */
/* These stubs return NULL/empty to prevent link errors in minimal builds. */
cJSON *cJSON_Parse(const char *value)
{
    (void)value;
    return NULL; /* Stub: full parser not implemented for embedded target */
}

char *cJSON_Print(const cJSON *item)
{
    (void)item;
    return NULL; /* Stub: full printer not implemented for embedded target */
}

char *cJSON_PrintUnformatted(const cJSON *item)
{
    (void)item;
    return NULL; /* Stub: full printer not implemented for embedded target */
}

void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item)
{
    if (object == NULL || item == NULL) return;
    item->string = (string != NULL) ? strdup(string) : NULL;
    /* Append to end of child list */
    if (object->child == NULL)
    {
        object->child = item;
    }
    else
    {
        cJSON *last = object->child;
        while (last->next != NULL) { last = last->next; }
        last->next = item;
        item->prev = last;
    }
}

void cJSON_Delete(cJSON *item)
{
    cJSON *next;
    while (item != NULL)
    {
        next = item->next;
        if (item->child)  cJSON_Delete(item->child);
        if (item->valuestring) free(item->valuestring);
        if (item->string)      free(item->string);
        free(item);
        item = next;
    }
}

