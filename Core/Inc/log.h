#ifndef _LOG_H_
#define _LOG_H_

#include "SEGGER_RTT.h"
#include "main.h"

#define ERR_RTT_COLOR RTT_CTRL_TEXT_BRIGHT_RED
#define WAR_RTT_COLOR RTT_CTRL_TEXT_BRIGHT_YELLOW
#define INF_RTT_COLOR RTT_CTRL_RESET
#define DBG_RTT_COLOR RTT_CTRL_TEXT_GREEN

/* For bug or bad behaviour that requires a particular attention and that the device cannot handle.
Severity is such that the nominal cycle can no longer be continued */
#define errorPrintln(fmt, ...) errorPrint(fmt "\r\n", ##__VA_ARGS__)
/* For bug or bad behaviour that requires a particular attention and that the device cannot handle.
Severity is such that the nominal cycle can no longer be continued */
#define errorPrint(fmt, ...)   SEGGER_RTT_printf(0, ERR_RTT_COLOR "|%7d|ERR|%s,%u|" fmt, HAL_GetTick(), __FUNCTION__, __LINE__, ##__VA_ARGS__)

/* Messages that require attention but are not critical to the nominal cycle of the device.
May go as far as a bug with a very short and negligible impact that the device can handle itself */
#define warnPrintln(fmt, ...) warnPrint(fmt "\r\n", ##__VA_ARGS__)
/* Messages that require attention but are not critical to the nominal cycle of the device.
May go as far as a bug with a very short and negligible impact that the device can handle itself */
#define warnPrint(fmt, ...)   SEGGER_RTT_printf(0, WAR_RTT_COLOR "|%7d|WAR|%s,%u|" fmt, HAL_GetTick(), __FUNCTION__, __LINE__, ##__VA_ARGS__)

/* Info messages must be understood by normal user.
It gives general info not required for bug hunting */
#define infoPrintln(fmt, ...) infoPrint(fmt "\r\n", ##__VA_ARGS__)
/* Info messages must be understood by normal user.
It gives general info not required for bug hunting */
#define infoPrint(fmt, ...)   SEGGER_RTT_printf(0, INF_RTT_COLOR "|%7d|INF|" fmt, HAL_GetTick(), ##__VA_ARGS__)

/* Messages for developers only.
Not intended to be understood by user and not required to get general infos about the device */
#define debugPrintln(fmt, ...) debugPrint(fmt "\r\n", ##__VA_ARGS__)
/* Messages for developers only.
Not intended to be understood by user and not required to get general infos about the device */
#define debugPrint(fmt, ...)   SEGGER_RTT_printf(0, DBG_RTT_COLOR "|%7d|DBG|" fmt, HAL_GetTick(), ##__VA_ARGS__)

#endif /* _LOG_H_ */
