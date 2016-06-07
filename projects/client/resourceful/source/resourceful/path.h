#pragma once

#ifdef IOS

const char *get_resource_path();

#define MYTHIC_RESOURCES_PATH get_resource_path()

#elif ANDROID

#define MYTHIC_RESOURCES_PATH ""

#else

#define MYTHIC_RESOURCES_PATH "resources/"

#endif