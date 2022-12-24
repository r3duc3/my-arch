#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <time.h>
#include <X11/Xlib.h>
#include "config.h"

static Display *dpy;

char *getbattery() {
	char *co, status;
	int descap, remcap;

	descap = -1;
	remcap = -1;

	co = readfile(BAT_DIR, "present");
	if (co == NULL)
		return smprintf("");
	if (co[0] != '1') {
		free(co);
		return smprintf("not present");
	}
	free(co);

	co = readfile(BAT_DIR, ENERGY_FULL);
	if (co == NULL)
		return smprintf("");
	sscanf(co, "%d", &descap);
	free(co);

	co = readfile(BAT_DIR, ENERGY_NOW);
	if (co == NULL)
		return smprintf("");
	sscanf(co, "%d", &remcap);
	free(co);

	co = readfile(BAT_DIR, "status");
	if (!strncmp(co, "Discharging", 11)) {
		status = '-';
	} else if (!strncmp(co, "Charging", 8)) {
		status = '+';
	} else {
		status = '?';
	}

	if (remcap < 0 || descap < 0)
		return smprintf("invalid");

	return smprintf("%.0f%%%c", ((float)remcap / (float)descap) * 100, status);
}

int main(void) {
	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

	for (;;sleep(1)) {
		bat = getbattery(BAT_DIR);
	}
}