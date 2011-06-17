#include <pthread.h>
#include <librcc.h>

static rcc_class_default_charset default_oem[] = {
    { "ru", "IBM866" },
    { NULL, NULL }
};

static rcc_class_default_charset default_iso[] = {
    { "ru", "CP1251" },
    { NULL, NULL }
};

#define ARC_CLASS 0
#define OUT_CLASS 1
#define ARCOUT_CLASS 0
static rcc_class classes[] = {
    { "oem", RCC_CLASS_STANDARD, NULL, default_oem, "OEM Encoding", 0 },
    { "out", RCC_CLASS_STANDARD, "LC_CTYPE", NULL, "Output", 0 },
    { NULL, RCC_CLASS_STANDARD, NULL, NULL, NULL, 0 }
};

static int initialized = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *rcc_init() {
    rcc_context ctx;
    
    pthread_mutex_lock(&mutex);
    if (!initialized) {
       rccInit();
//     rccInitDefaultContext(NULL, 0, 0, classes, 0);
//     rccInitDb4(NULL, NULL, 0);
//     rccLoad(NULL, "zip");
    }
    initialized++;
    pthread_mutex_unlock(&mutex);
    
    ctx = rccCreateContext(NULL, 0, 0, classes, 0);
    if (ctx) {
       rccInitDb4(ctx, NULL, 0);
       rccLoad(ctx, "zip");
    }

    return ctx;
}


void rcc_free(void *ctx) {
    if (ctx) rccFreeContext((rcc_context)ctx);

    pthread_mutex_lock(&mutex);
    if (initialized == 1) rccFree();
    initialized--;
    pthread_mutex_unlock(&mutex);
}


char *rcc_read(void *ctx, const char *string, size_t size) {
    if (!initialized) {
       rcc_init();
       if (!initialized) return NULL;
    }
    return rccSizedRecode((rcc_context)ctx, ARC_CLASS, OUT_CLASS, string, size, NULL);
}

char *rcc_write(void *ctx, const char *string, size_t size) {
    if (!initialized) {
       rcc_init();
       if (!initialized) return NULL;
    }
    return rccSizedRecode((rcc_context)ctx, OUT_CLASS, ARCOUT_CLASS, string, size, NULL);
}

