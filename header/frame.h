#ifdef __FRAME_HEADER__
#define __FRAME_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/fb.h>

#define FB_DEV "/dev/fb0"

typedef unsigned int u32;
typedef unsigned char u8;
u32 *pfbdata; /* mmap pointer */
int fb_fd;
struct fb_var_screeninfo fvs;

void swap(u32 *a, u32 *b);
u32 get_color32(u8 a, u8 r, u8 g, u8 b);
u32 random_pixel();

void clean_screen();
void draw_block(u32 pixel, int differ, int randnum);
void draw_block1(u32 pixel);
void draw_block2(u32 pixel);
void draw_block3(u32 pixel);
void draw_block4(u32 pixel);
void draw_block5(u32 pixel);
void draw_block6(u32 pixel);
void draw_block7(u32 pixel);
void draw_block8(u32 pixel);
void draw_time_bar(int count);
void draw_zero(u32 xp, u32 yp);
void draw_one(u32 xp, u32 yp);
void draw_two(u32 xp, u32 yp);
void draw_three(u32 xp, u32 yp);
void draw_four(u32 xp, u32 yp);
void draw_five(u32 xp, u32 yp);
void draw_six(u32 xp, u32 yp);
void draw_seven(u32 xp, u32 yp);
void draw_eight(u32 xp, u32 yp);
void draw_nine(u32 xp, u32 yp);
void draw_score(int score);
void init_frame();
void release_frame();

void init_frame()
{
	int check;

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

	pfbdata = (u32 *)mmap(0, fvs.xres*fvs.yres * 32/8, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
}

void release_frame()
{
	munmap(pfbdata, fvs.xres * fvs.yres * 32/8);
	close(fb_fd);
}

int draw_frame(int randnum)
{

	u32 pixel;

	clean_screen();
	pixel = random_pixel();
	draw_block(pixel, 50, randnum);
	draw_score(0);
	
	return 0;
}

void swap(u32 *a, u32 *b)
{
	u32 temp;
	if(*a > *b) {
		temp = *b;
		*b = *a;
		*a = temp;
	}
}

u32 get_color32(u8 a, u8 r, u8 g, u8 b)
{
	return ((u32) ( (a<<24) | (r<<16) | (g<<8) | b));
}

u32 random_pixel()
{
	return ((u32) (65536.0 * rand() / (RAND_MAX+1.0)));
}

void clean_screen()
{
	int offset, repx, repy;

	for(repy = 0; repy <= 479; repy++) {
		offset = repy * fvs.xres;
		for(repx = 0; repx < 799; repx++) {
			*(pfbdata + offset + repx) = get_color32( 0, 0, 0, 0);
		}
	}
}

void draw_block(u32 pixel, int differ, int randnum)
{
	int i;
	u32 block_pixel[8];

	for(i=0; i<8; i++)
		block_pixel[i] = pixel;

	if(pixel < differ)
		block_pixel[randnum] = pixel + differ;
	else 
		block_pixel[randnum] = pixel - differ;

	draw_block1(block_pixel[0]);
	draw_block2(block_pixel[1]);
	draw_block3(block_pixel[2]);
	draw_block4(block_pixel[3]);
	draw_block5(block_pixel[4]);
	draw_block6(block_pixel[5]);
	draw_block7(block_pixel[6]);
	draw_block8(block_pixel[7]);
}

void draw_time_bar(int count)
{
	int offset, repx, repy;
	u32 pixel;

	pixel = get_color32(0,0+count/4,150-count/4,0);

	if(count<500) {
		for(repy = 310; repy <= 340; repy++) {
			offset = repy * fvs.xres;
			for(repx = 50; repx < 510 - count*46/60; repx++) {
				*(pfbdata + offset + repx) = pixel;
			}
		}
	}

	else {
		if(count%10 >= 5){
			for(repy = 310; repy <= 340; repy++) {
				offset = repy * fvs.xres;
				for(repx = 50; repx < 510 - count*46/60; repx++) {
					*(pfbdata + offset + repx) = pixel;
				}
			}
		}
		
		else {
			for(repy = 310; repy <= 340; repy++) {
				offset = repy * fvs.xres;
				for(repx = 50; repx < 510 - count*46/60; repx++) {
					*(pfbdata + offset + repx) = 0;
				}
			}
		}
	}
			

	for(repy = 310; repy <= 340; repy++) {
		offset = repy * fvs.xres;
		for(repx = 510 - count*46/60 - 1; repx < 510; repx++) {
			*(pfbdata + offset + repx) = 0;
		}
	}
}

void draw_block1(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 50; repy <= 150; repy++) {
		offset = repy * fvs.xres;
		for(repx = 50; repx < 150; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block2(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 50; repy <= 150; repy++) {
		offset = repy * fvs.xres;
		for(repx = 170; repx < 270; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block3(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 50; repy <= 150; repy++) {
		offset = repy * fvs.xres;
		for(repx = 290; repx < 390; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block4(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 50; repy <= 150; repy++) {
		offset = repy * fvs.xres;
		for(repx = 410; repx < 510; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block5(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 170; repy <= 270; repy++) {
		offset = repy * fvs.xres;
		for(repx = 50; repx < 150; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block6(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 170; repy <= 270; repy++) {
		offset = repy * fvs.xres;
		for(repx = 170; repx < 270; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block7(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 170; repy <= 270; repy++) {
		offset = repy * fvs.xres;
		for(repx = 290; repx < 390; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_block8(u32 pixel)
{
	int offset, repx, repy;

	for(repy = 170; repy <= 270; repy++) {
		offset = repy * fvs.xres;
		for(repx = 410; repx < 510; repx++) {
			*(pfbdata + offset + repx) = pixel;
		}
	}
}

void draw_zero(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,1,0,0,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,0,0,0,1,0},
				   {0,1,0,0,0,0,1,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,1,0,0,0,1,0},
				   {0,0,1,1,1,1,0,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
				
		}
	}
}

void draw_one(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,0,0,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,1,1,1,0,0},
				   {0,0,1,1,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,1,0,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_two(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,1,0,0,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,0,0,0,1,1},
				   {0,1,0,0,0,0,1,1},
				   {0,0,0,0,0,0,1,1},
				   {0,0,0,0,0,0,1,0},
				   {0,0,0,0,0,1,1,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,1,1,0,0,0,0},
				   {0,1,1,0,0,0,0,0},
				   {0,1,1,0,0,0,0,0},
				   {1,1,1,1,1,1,1,1} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_three(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,0,0,0,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,0,0,0,1,0},
				   {0,1,0,0,0,0,1,1},
				   {0,0,0,0,0,0,1,0},
				   {0,0,0,0,1,1,1,0},
				   {0,0,0,0,0,1,1,0},
				   {0,0,0,0,0,0,1,1},
				   {0,0,0,0,0,0,0,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,1,0,0,0,1,1},
				   {0,0,1,1,1,1,1,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_four(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,0,0,0,0},
				   {0,0,0,0,0,1,1,0},
				   {0,0,0,0,1,1,1,0},
				   {0,0,0,1,1,1,1,0},
				   {0,0,0,1,0,1,1,0},
				   {0,0,1,0,0,1,1,0},
				   {0,1,1,0,0,1,1,0},
				   {1,1,0,0,0,1,1,0},
				   {1,1,1,1,1,1,1,1},
				   {0,0,0,0,0,1,1,0},
				   {0,0,0,0,0,1,1,0},
				   {0,0,0,0,0,1,1,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_five(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,0,0,0,0},
				   {0,0,1,1,1,1,1,1},
				   {0,0,1,0,0,0,0,0},
				   {0,1,1,0,0,0,0,0},
				   {0,1,1,0,1,0,0,0},
				   {0,1,1,1,1,1,1,0},
				   {0,1,0,0,0,0,1,1},
				   {0,0,0,0,0,0,0,1},
				   {0,0,0,0,0,0,0,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,1,0,0,0,1,0},
				   {0,0,1,1,1,1,0,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_six(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,1,0,0,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,0,0,0,1,1},
				   {0,1,0,0,0,0,0,0},
				   {0,1,0,0,0,0,0,0},
				   {0,1,1,1,1,1,1,0},
				   {1,1,1,0,0,0,1,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,1,0,0,0,1,0},
				   {0,0,1,1,1,1,1,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_seven(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,0,0,0,0},
				   {0,1,1,1,1,1,1,1},
				   {0,0,0,0,0,0,1,0},
				   {0,0,0,0,0,1,1,0},
				   {0,0,0,0,0,1,0,0},
				   {0,0,0,0,1,1,0,0},
				   {0,0,0,0,1,0,0,0},
				   {0,0,0,1,1,0,0,0},
				   {0,0,0,1,0,0,0,0},
				   {0,0,0,1,0,0,0,0},
				   {0,0,1,1,0,0,0,0},
				   {0,0,1,1,0,0,0,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_eight(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,1,0,0,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,0,0,0,1,0},
				   {0,1,1,0,0,0,1,1},
				   {0,1,1,0,0,0,1,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,1,0,1,1,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,1,0,0,0,1,1},
				   {0,0,1,1,1,1,1,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_nine(u32 xp, u32 yp)
{
	int i,j;
	int coordinates[12][8] = { {0,0,0,0,0,0,0,0},
				   {0,0,1,1,1,1,1,0},
				   {0,1,1,0,0,0,1,0},
				   {0,1,0,0,0,0,1,1},
				   {0,1,0,0,0,0,0,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,1,0,0,1,1,1},
				   {0,0,1,1,1,1,0,1},
	 			   {0,0,0,0,0,0,0,1},
				   {0,1,0,0,0,0,1,1},
				   {0,1,1,0,0,1,1,0},
				   {0,0,1,1,1,1,0,0} };
	int offset, repx, repy;
	
	for(i=0; i<12; i++) {
		for(j=0; j<8; j++) {
			if(coordinates[i][j] == 1) {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,255,0,0) ;
					}
				}
			}
			else {
				for(repy = yp + i*10;  repy <=  yp + i*10 + 10; repy++) {
					offset = repy * fvs.xres;
					for(repx = xp + j*10 ; repx < xp + j*10 + 10; repx++) {
						*(pfbdata + offset + repx) = get_color32(0,0,0,0) ;
					}
				}
			}
		}
	}
}

void draw_score(int score)
{
	int first_digit, second_digit;

	first_digit = score % 10;
	second_digit = (score % 100) / 10 ;

	switch (first_digit) {
		case 0 :  	
		draw_zero(650, 180);
		break;
		case 1 :  	
		draw_one(650, 180);
		break;
		case 2 :  	
		draw_two(650, 180);
		break;
		case 3 :  	
		draw_three(650, 180);
		break;
		case 4 :  	
		draw_four(650, 180);
		break;
		case 5 :  	
		draw_five(650, 180);
		break;
		case 6 :  	
		draw_six(650, 180);
		break;
		case 7 :  	
		draw_seven(650, 180);
		break;
		case 8 :  	
		draw_eight(650, 180);
		break;
		case 9 :  	
		draw_nine(650, 180);
		break;
	}

	switch (second_digit) {
		case 0 :  	
		draw_zero(560, 180);
		break;
		case 1 :  	
		draw_one(560, 180);
		break;
		case 2 :  	
		draw_two(560, 180);
		break;
		case 3 :  	
		draw_three(560, 180);
		break;
		case 4 :  	
		draw_four(560, 180);
		break;
		case 5 :  	
		draw_five(560, 180);
		break;
		case 6 :  	
		draw_six(560, 180);
		break;
		case 7 :  	
		draw_seven(560, 180);
		break;
		case 8 :  	
		draw_eight(560, 180);
		break;
		case 9 :  	
		draw_nine(560, 180);
		break;
	}
}

#endif
