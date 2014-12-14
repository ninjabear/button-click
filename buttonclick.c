// g++ test.cpp -L/usr/X11R6/lib -lX11 -lXtst
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <time.h>


int main(int argc, char* argv[])
{
	Display *display;

	if ((display = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "Cannot open local X-display.\n");
		exit(1);
	}
	int ev, er, ma, mi;
	if(!XTestQueryExtension(display, &ev, &er, &ma, &mi))
	{
		fprintf(stderr, "XTest extension not supported on server.\n");
		exit(1);
	}


	int x = 5;
	do {
		printf ("winning at keypress mode in %ds\r", x); fflush(stdout);
		sleep (1);
	} while (x--);
	printf("\n");

	long timenow;
	time(&timenow);
	long finishtime = timenow+11;
	long c;
	unsigned long tot=0;
	do 
	{
		time(&c);
		XTestFakeButtonEvent(display, 1, True, CurrentTime);
		XTestFakeButtonEvent(display, 1, False, CurrentTime);
		XFlush(display);
		sleep(0.2);
		tot++;
	} while (c < finishtime);
	printf("clicked %lu times in 11 secs\n", tot);
	return 0;
}
