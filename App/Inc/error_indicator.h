#ifndef ERROR_INDICATOR_H__
#define ERROR_INDICATOR_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "rmw/ret_types.h"
#include <rcl/types.h>
#include "gpio.h"
#include "main.h"
#include "cmsis_os.h"

extern rmw_ret_t rmw_err_code;
extern rcl_ret_t rcl_err_code;

void no_error();
void blink_error(int LD, int times, int on_period, int off_period);
void error_indicator();

#ifdef __cplusplus
}
#endif





#endif // ERROR_INDICATOR_H__