#include "hub.h"
#include <malloc.h>

int metahub_create_hub(Hub **hub) {
  *hub = (Hub*)malloc(sizeof(Hub));
  return 0;
}

int metahub_delete_hub(Hub *hub) {
  free(hub);
  return 0;
}

