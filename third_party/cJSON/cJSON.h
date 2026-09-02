/* cJSON Lightweight JSON parser in C */

#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7)

typedef struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;
    int type;
    char *valuestring;
    int valueint;
    double valuedouble;
    char *string;
} cJSON;

const char *cJSON_Version(void);
cJSON *cJSON_Parse(const char *value);
char  *cJSON_Print(const cJSON *item);
char  *cJSON_PrintUnformatted(const cJSON *item);
void   cJSON_Delete(cJSON *item);

cJSON *cJSON_CreateObject(void);
cJSON *cJSON_CreateArray(void);
cJSON *cJSON_CreateString(const char *string);
cJSON *cJSON_CreateNumber(double num);
cJSON *cJSON_CreateBool(int b);

void   cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);

#ifdef __cplusplus
}
#endif

#endif
