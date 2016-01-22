#pragma once
#include "dllexport.h"
#include "list.h"

#include <stdint.h>

typedef int32_t int32;

typedef struct metahub_ {
    List nodes;
} Hub;

enum metahub_status {
    metahub_success = 1,
    metahub_error_unknown
} metahub_status_error;