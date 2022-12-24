#include "config.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <X11/Xlib.h>

static Display *dpy;

char *smprintf(char *fmt, ...) {
	va_list fmtargs;
	char *ret;
	int len;

	va_start(fmtargs, fmt);
	len = vsnprintf(NULL, 0, fmt, fmtargs);
	va_end(fmtargs);
	ret = malloc(++len);
	if (ret == NULL) {
		perror("malloc");
		exit(1);
	}

	va_start(fmtargs, fmt);
	vsnprintf(ret, len, fmt, fmtargs);
	va_end(fmtargs);

	return ret;
}

char mktimes() {
	char buf[129];
	time_t tim;
	struct tm *timtm;

	setenv("TZ", TZNAME, 1);
	tim = time(NULL);
	timtm = localtime(&tim);
	if (timtm == NULL)
		return smprintf("");

	if (!strftime(buf, sizeof(buf)-1, TIME_FORMAT, timtm)) {
		fprint(stderr, "strftime == 0\n");
		return smprintf("");
	}

	return smprintf("%s", buf);
}

void setstatus(char *str) {
	XStoreName(dpy, defaultRootWindow(dpy), str);
	XSync(dpy, False);
}

char *readfile(char *base, char *file) {
	char *path, line[513];
	FILE *fd;

	memset(line, 0, sizeof(line));

	path = smprintf("%s/%s", base, file);
	fd = fopen(path, "r");
	free(path);
	if (fd == NULL)
		return NULL;

	if (fgets(line, sizeof(line)-1, fd) == NULL)
		return NULL;
	fclose(fd);

	return smprintf("%s", line);
}

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