#include <linux/input.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include "bmp_print.h"

#define TOUCH_SCREEN_DEV "/dev/input/event1"

#define START 1
#define GAMEON0 2
#define GAMEON1 3
#define GAMEON2 4
#define GAMEON3 5
#define GAMEON4 6
#define GAMEON5 7
#define GAMEON6 8
#define END 9

struct input_event ts;
//struct timeval mytime;
long cur_time=0;
long offset = 2;
int ts_fd;
int gTerminate = 0;
int yTerminate_one = 0;
int yTerminate_two = 0;
int yTerminate_three = 0;
int yTerminate_four = 0;
int yTerminate_five = 0;
int yTerminate_six = 0;
int x,y;

int ts_open()
{
	ts_fd = open(TOUCH_SCREEN_DEV, O_RDONLY);
	if( ts_fd < 0 )
	{
		printf("Touch Screen open error..\n");
		return 0;
	}
}

int ts_close()
{
	if(close(ts_fd) < 0)
	{
		printf("Touch Screen close error..\n");
		return 0;
	}
}

void ts_init()
{
	while(ts.code!=54)
	{
		read(ts_fd, &ts, sizeof(ts));
		cur_time = ts.time.tv_sec;
		printf("ts_init= code : %d, value: %d\n", ts.code, ts.value);
	}
}

void *ts_read(int num)
{
	ts_open();
	ts_init();

	while(!gTerminate)
	{
		read(ts_fd, &ts, sizeof(ts));
		if(ts.code == 53)
			x = ts.value;

		read(ts_fd, &ts, sizeof(ts));
		if(ts.code == 54)
			y = ts.value;


		printf("code : %d, value: %d\n", ts.code, ts.value);
		printf("x: %d, y: %d\n", x, y);

		
		if(x > 60 && x < 155 && y > 95 && y < 180 )
			yTerminate_one = 1;
		if(x > 350 && x < 440 && y > 95 && y < 180 )
			yTerminate_two = 1;
		if(x > 640 && x < 735 && y > 95 && y < 180 )
			yTerminate_three = 1;
		if(x > 60 && x < 155 && y > 310 && y < 400 )
			yTerminate_four = 1;
		if(x > 350 && x < 440 && y > 310 && y < 400 )
			yTerminate_five = 1;
		if(x > 640 && x < 735 && y > 310 && y < 400 )
			yTerminate_six= 1;
	}

	ts_close();

}

