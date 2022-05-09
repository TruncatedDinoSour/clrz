#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

/* *************
 * ANSI stuff
 */

#define CSI "\033["

#define ANSI_CUR_SAVE CSI "s"
#define ANSI_CUR_RES  CSI "u"
#define ANSI_CUR_HIDE CSI "?25l"
#define ANSI_CUR_SHOW CSI "?25h"

#define ANSI_CLEAR CSI "2J" CSI "1;1H"

#define NONL(code) fputs(code, stdout)

/* *************
 * Config
 */

#ifndef SLEEP_TIME
#define SLEEP_TIME 15000
#endif

#ifdef _DEBUG
#define DP(msg)                                                            \
    fputs("[DEBUG] " msg "\n        Press enter to continue....", stderr); \
    getchar();
#else
#define DP(msg)
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

static unsigned char clrz(void) {
    DP("Getting terminal size");

    struct winsize ws;
    if (ioctl(1, TIOCGWINSZ, &ws) != 0) {
        perror("ioctl()");
        return 1;
    }

    DP("Making a column");

    char col[ws.ws_col];

    for (unsigned short int idx = 0; idx < ws.ws_col; ++idx)
        col[idx] = ' ';

    DP("Setting up cursor");

    NONL(ANSI_CUR_HIDE);
    NONL(ANSI_CUR_SAVE);

    DP("Filling up columns");

    for (unsigned short int line = 0; line < ws.ws_row; ++line) {
        printf(CSI "%d;%dH", line, 0); // ANSI_CUP
        NONL(col);

#ifndef HAVE_BUFFERING
        fflush(stdout);
#endif
        usleep(SLEEP_TIME);
    }

    DP("Cleanup");

    NONL(ANSI_CUR_RES);
    NONL(ANSI_CLEAR);
    NONL(ANSI_CUR_SHOW);

    return 0;
}

#ifndef CLRZ_H
int main(void) { return clrz(); }
#endif
