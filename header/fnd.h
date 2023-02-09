#ifdef __FND_HEADER__
#define __FND_HEADER__

#include <stdio.h>
#include <fcntl.h>

#define FND_DEV_NAME "/dev/iom_fnd"

int fnd(int fnd_index)
{
	int fd;
	int ret;
	unsigned char fnd_seg_data;

	unsigned char fnd_hex_val[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90}; // 0 is 0xc0


	if( fnd_index < 0 || fnd_index > 9)
	{
		printf("Invalid hex data!! (%d)\n", fnd_index);
		return -1;
	}

	fd = open(FND_DEV_NAME, O_WRONLY);
	if( fd < 0)
	{
		printf("Cannot open the device %s!!\n", FND_DEV_NAME);
		return -1;
	}

	fnd_seg_data = fnd_hex_val[fnd_index]; // [fnd_index-1] 
	ret = write(fd, &fnd_seg_data, sizeof(fnd_seg_data));
	if(ret < 0)
	{
		printf("Cannot write the data on FND..\n");
		return -1;
	}

	close(fd);
	return 0;
}

#endif
