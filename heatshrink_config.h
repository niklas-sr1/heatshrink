#ifndef HEATSHRINK_CONFIG_H
#define HEATSHRINK_CONFIG_H

/* When used as an ESP-IDF component, configuration comes from Kconfig/sdkconfig.h.
 * The Kconfig options are prefixed with CONFIG_ and defined there.
 * For non ESP-IDF usage, we provide defaults here if not already defined. */

/* Should functionality assuming dynamic allocation be used? */
#ifndef HEATSHRINK_DYNAMIC_ALLOC
    #if defined(CONFIG_HEATSHRINK_DYNAMIC_ALLOC)
        #define HEATSHRINK_DYNAMIC_ALLOC CONFIG_HEATSHRINK_DYNAMIC_ALLOC
    #else
        #define HEATSHRINK_DYNAMIC_ALLOC 1
    #endif
#endif

#if HEATSHRINK_DYNAMIC_ALLOC
    /* Optional replacement of malloc/free */
    #define HEATSHRINK_MALLOC(SZ) malloc(SZ)
    #define HEATSHRINK_FREE(P, SZ) free(P)
#else
    /* Required parameters for static configuration */
    #ifndef HEATSHRINK_STATIC_INPUT_BUFFER_SIZE
        #if defined(CONFIG_HEATSHRINK_STATIC_INPUT_BUFFER_SIZE)
            #define HEATSHRINK_STATIC_INPUT_BUFFER_SIZE CONFIG_HEATSHRINK_STATIC_INPUT_BUFFER_SIZE
        #else
            #define HEATSHRINK_STATIC_INPUT_BUFFER_SIZE 32
        #endif
    #endif
    
    #ifndef HEATSHRINK_STATIC_WINDOW_BITS
        #if defined(CONFIG_HEATSHRINK_STATIC_WINDOW_BITS)
            #define HEATSHRINK_STATIC_WINDOW_BITS CONFIG_HEATSHRINK_STATIC_WINDOW_BITS
        #else
            #define HEATSHRINK_STATIC_WINDOW_BITS 8
        #endif
    #endif
    
    #ifndef HEATSHRINK_STATIC_LOOKAHEAD_BITS
        #if defined(CONFIG_HEATSHRINK_STATIC_LOOKAHEAD_BITS)
            #define HEATSHRINK_STATIC_LOOKAHEAD_BITS CONFIG_HEATSHRINK_STATIC_LOOKAHEAD_BITS
        #else
            #define HEATSHRINK_STATIC_LOOKAHEAD_BITS 4
        #endif
    #endif
#endif

/* Turn on logging for debugging. */
#ifndef HEATSHRINK_DEBUGGING_LOGS
    #if defined(CONFIG_HEATSHRINK_DEBUGGING_LOGS)
        #define HEATSHRINK_DEBUGGING_LOGS CONFIG_HEATSHRINK_DEBUGGING_LOGS
    #else
        #define HEATSHRINK_DEBUGGING_LOGS 0
    #endif
#endif

/* Use indexing for faster compression. (This requires additional space.) */
#ifndef HEATSHRINK_USE_INDEX
    #if defined(CONFIG_HEATSHRINK_USE_INDEX)
        #define HEATSHRINK_USE_INDEX CONFIG_HEATSHRINK_USE_INDEX
    #else
        #define HEATSHRINK_USE_INDEX 1
    #endif
#endif

#endif
