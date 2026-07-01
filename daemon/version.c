#include <stdio.h>

#include "version.h"

void version_print(void)
{
    printf("NGSpread %s\n", NG_VERSION);
    printf("Compatible with Spread Toolkit %s\n", NG_SPREAD_COMPAT);
    printf("Git commit : %s\n", NG_GIT_HASH);
    printf("Built      : %s\n", NG_BUILD_DATE);
    printf("Compiler   : %s\n", __VERSION__);
}

