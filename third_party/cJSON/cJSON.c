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

cJSON *cJSON_CreateString(const char *string)
{
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item)
    {
        memset(item, 0, sizeof(cJSON));
        item->type = cJSON_String;
        item->valuestring = strdup(string);
    }
    return item;
}

void cJSON_Delete(cJSON *item)
{
    if (!item) return;
    if (item->valuestring) free(item->valuestring);
    if (item->string) free(item->string);
    free(item);
}
