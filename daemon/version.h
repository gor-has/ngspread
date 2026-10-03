#ifndef NG_VERSION_H
#define NG_VERSION_H

#ifndef NG_NAME
#define NG_NAME                "NGSpread"
#define NG_VERSION_MAJOR       0
#define NG_VERSION_MINOR       1
#define NG_VERSION_PATCH       0
#endif

#ifndef NG_VERSION_STRING
#define NG_VERSION_STRING      "0.1.0"
#define NG_SPREAD_COMPAT       "5.0.1"
#endif

#ifndef NG_BUILD_DATE
#define NG_BUILD_DATE          __DATE__
#define NG_BUILD_TIME          __TIME__
#endif

void version_print(void);

#endif
