#include "config.h"
#include "modules/func.h"
#include "modules/bat.h"

int main(void) {
	char *status;
	char *bat;

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

	for (;;sleep(1)) {
		bat = getbattery(BAT_DIR);
		status = smprintf("B:%s", bat);
		setstatus(status);

		free(status);
		free(bat);
	}

	XCloseDisplay(dpy);

	return 0;
}