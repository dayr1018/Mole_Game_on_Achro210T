
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/fb.h>

#include "bmp_header.h"

#define FB_DEV "/dev/fb0"

#define START 1
#define GAMEON0 2
#define GAMEON1 3
#define GAMEON2 4
#define GAMEON3 5
#define GAMEON4 6
#define GAMEON5 7
#define GAMEON6 8
#define END 9 

unsigned int get_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b);

unsigned int get_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return ((unsigned int) ( (a<<24) | (r<<16) | (g<<8) | b));
}


void printbmp(int file_num);

void printbmp(int file_num)
{
	BITMAPFILEHEADER BmpFileHd;
	BITMAPINFOHEADER BmpInfoHd;

	char *filename;
	switch(file_num){
		case START:
			filename = "start.bmp";
			break;
		case GAMEON0:
			filename = "gameon0.bmp";
			break;
		case GAMEON1:
			filename = "gameon1.bmp";
			break;
		case GAMEON2:
			filename = "gameon2.bmp";
			break;
		case GAMEON3:
			filename = "gameon3.bmp";
			break;
		case GAMEON4:
			filename = "gameon4.bmp";
			break;
		case GAMEON5:
			filename = "gameon5.bmp";
			break;
		case GAMEON6:
			filename = "gameon6.bmp";
			break;
		case END:
			filename = "end.bmp";
			break;
	}

	size_t retval;

	int i,j;
	int fb_fd;
	int check;
	int offset, repx, repy;
	int rwsize;
	char buf[10];
	unsigned int color;

	unsigned int *pfbdata; /* mmap pointer */
	struct fb_var_screeninfo fvs;

	FILE * read_fp = NULL;
	

	if( (fb_fd = open(FB_DEV, O_RDWR)) < 0 ) {
		perror("Frame buffer open error..!!");
		exit(1);
	}
	if( (check = ioctl(fb_fd, FBIOGET_VSCREENINFO, &fvs)) < 0) {
		perror("Cannot read FB information - VSCREENINFO!!");
		exit(1);
	}
	if(fvs.bits_per_pixel != 32 ) {
		perror("Unsupport mode: 32 bpp only..");
		exit(1);
	}

	
	pfbdata = (unsigned int *)mmap(0, fvs.xres*fvs.yres * 32/8, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);

	

	if((read_fp = fopen(filename,"rb")) == NULL) {
		printf("File Open Error\n");
		exit(1);
	}

	fread(&BmpFileHd, sizeof(BITMAPFILEHEADER), 1, read_fp);
	fread(&BmpInfoHd, sizeof(BITMAPINFOHEADER), 1, read_fp);
	
	
	if(BmpFileHd.bfType!=0x4D42) {
		printf("Not Bitmap file or Unsupport Bitmap file\n");
		exit(1);
	}
	
	for(repy = BmpInfoHd.biHeight; repy >= 0; repy--) {
		offset = repy * fvs.xres;
		for(repx = 0; repx < BmpInfoHd.biWidth; repx++) {
			fread(buf, sizeof(char), 3, read_fp);
			color = get_color(0, buf[2], buf[1], buf[0]);
			*(pfbdata + offset + repx) = color;
		}
	}

	fclose(read_fp);
	munmap(pfbdata, fvs.xres * fvs.yres * 32/8);
	close(fb_fd);

}

