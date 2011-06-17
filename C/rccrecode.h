#ifndef _RCC_RECODE_H
#define _RCC_RECODE_H

# ifdef __cplusplus 
extern "C" { 
# endif

    void *rcc_init();
    void rcc_free(void *ctx);
    char *rcc_read(void *ctx, const char *string, size_t size);
    char *rcc_write(void *ctx, const char *string, size_t size);

# ifdef __cplusplus 
}
# endif

#endif /* _RCC_RECODE_H */
