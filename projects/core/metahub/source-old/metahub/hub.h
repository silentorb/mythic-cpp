#pragma once
#include "commoner/dllexport.h"

#include "common.h"
#include "node.h"
#include "list.h"

typedef struct metahub_Hub {
    List nodes;
} metahub_Hub;

MYTHIC_EXPORT int metahub_create_hub(metahub_Hub **hub);

MYTHIC_EXPORT int metahub_delete_hub(metahub_Hub *hub);