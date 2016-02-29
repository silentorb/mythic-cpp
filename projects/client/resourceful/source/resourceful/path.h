#pragma once

#ifdef IOS

const char *get_resource_path();

#define MYTHIC_RESOURCES_PATH get_resource_path()

#else

#define MYTHIC_RESOURCES_PATH "resources/"

#endif