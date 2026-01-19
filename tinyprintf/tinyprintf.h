/*
File: tinyprintf.h

Copyright (C) 2004  Kustaa Nyholm
*/
#ifndef __TFP_PRINTF__
#define __TFP_PRINTF__

#include <stdint.h>
#include <stdarg.h>


#ifdef  __cplusplus
extern "C" {
#endif


typedef void (*putcf) (void *, char);

void tfp_format(void *putp, putcf putf, const char *fmt, va_list va);

void tfp_printf(char *fmt, ...);

int tfp_sprintf(char *str, const char *fmt, ...);
int tfp_snprintf(char *str, size_t size, const char *fmt, ...);

int tfp_vsprintf(char *str, const char *fmt, va_list ap);
int tfp_vsnprintf(char *str, size_t size, const char *fmt, va_list ap);


#ifdef  __cplusplus
}
#endif

#endif
