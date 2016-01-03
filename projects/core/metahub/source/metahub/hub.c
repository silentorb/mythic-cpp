#include "hub.h"
#include <malloc.h>

int metahub_create_hub(metahub_Hub **hub) {
  *hub = (metahub_Hub*)malloc(sizeof(metahub_Hub));
  return 0;
}

int metahub_delete_hub(metahub_Hub *hub) {
  free(hub);
  return 0;
}

