#ifdef __LED_HEADER__
#define __LED_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define LED_DEV "/dev/iom_led"


int led(int led_index)
{
	int fd;
	int ret;

	unsigned char led_hex_data[] = {0x00, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xff};


	if (led_index < 0 || led_index >9) {
		printf ("Invalid range!! (%s) \n", led_index);
		return -1;
	}

	fd = open(LED_DEV, O_WRONLY);
	if( fd < 0){
		printf("Device open error(%s)..\n", LED_DEV);
		return -1;
	}

	ret = write (fd, &led_hex_data[led_index], sizeof(led_hex_data[led_index]));
	if(ret < 0)
	{
		printf("LED write error..\n");
	}

	close (fd);
	return 0;
}

#endif
