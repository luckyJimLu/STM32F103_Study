/* Minimal cJSON implementation stub for STM32 */

#include "cJSON.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Maximum nesting depth to prevent stack overflow on Cortex-M3 */
#define CJSON_MAX_NESTING_DEPTH 32

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
        /* If strdup failed on a non-NULL input, free item and return NULL */
        if (string != NULL && item->valuestring == NULL)
        {
            free(item);
            return NULL;
        }
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
        /* Saturate double-to-int conversion to avoid undefined behavior */
        if (num >= (double)INT_MAX)
        {
            item->valueint = INT_MAX;
        }
        else if (num <= (double)INT_MIN)
        {
            item->valueint = INT_MIN;
        }
        else
        {
            item->valueint = (int)num;
        }
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
    char *key = NULL;

    if (object == NULL || item == NULL) return;

    /* Allocate the replacement key before mutating the item.  If the heap is
       exhausted, leave the item untouched instead of inserting a nameless
       member or losing its existing key. */
    if (string != NULL)
    {
        key = strdup(string);
        if (key == NULL)
        {
            return;
        }
    }

    /* Free previously allocated key name to prevent memory leak */
    if (item->string != NULL)
    {
        free(item->string);
    }
    item->string = key;

    /* Ensure item's list pointers are clean before insertion */
    item->next = NULL;

    /* Append to end of child list */
    if (object->child == NULL)
    {
        item->prev = NULL;
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

/* Internal recursive delete with depth limit to prevent stack overflow */
static void cJSON_Delete_internal(cJSON *item, int depth)
{
    cJSON *next;
    while (item != NULL)
    {
        next = item->next;
        if (item->child && depth < CJSON_MAX_NESTING_DEPTH)
        {
            cJSON_Delete_internal(item->child, depth + 1);
        }
        if (item->valuestring) free(item->valuestring);
        if (item->string)      free(item->string);
        free(item);
        item = next;
    }
}

void cJSON_Delete(cJSON *item)
{
    cJSON_Delete_internal(item, 0);
}
