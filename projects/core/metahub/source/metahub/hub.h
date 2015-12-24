#pragma once

#include "common.h"
#include "node.h"
#include "list.h"

typedef struct Hub {
    List nodes;
} Hub;

int metahub_create_hub(Hub **hub);

int metahub_delete_hub(Hub *hub);