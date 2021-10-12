
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftdi.h>
#include <signal.h>

bool interrupted = false;

void onSIGINT(int n)
{
	interrupted = true;
}

void ftdi_fatal (struct ftdi_context *ftdi, char *str)
{
	fprintf (stderr, "%s: %s\n", str, ftdi_get_error_string (ftdi));
	ftdi_free(ftdi);
	exit (1);
}

int main()
{
	struct ftdi_context *ftdi;
	unsigned char data;

	signal(SIGINT, onSIGINT);

	int output = 0xff;

	ftdi = ftdi_new();
	if (ftdi == 0) {
		fprintf(stderr, "ftdi_bew failed\n");
		return EXIT_FAILURE;
	}

	if (ftdi_usb_open(ftdi, 0x0403, 0x6001) < 0) {
		ftdi_fatal (ftdi, "Can't open ftdi device");
	}

	if (ftdi_set_bitmode(ftdi, output, BITMODE_BITBANG) < 0) {
		ftdi_fatal (ftdi, "Can't enable bitbang");
	}

	while (!interrupted) {
		data = 0x55;
		ftdi_write_data(ftdi, &data, 1);
		usleep(500000);
		data = 0xaa;
		ftdi_write_data(ftdi, &data, 1);
		usleep(500000);
	}

	ftdi_usb_close(ftdi);
	ftdi_free(ftdi);

	return 0;
}
