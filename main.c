#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "ts.h"
#include "fnd.h"
#include "frame.h"
//#include "bmp_print.h"
#include "led.h"

/*
#define START 1 
#define GAMEON0 2
#define GAMEON1 3
#define GAMEON2 4
#define GAMEON3 5
#define GAMEON4 6
#define GAMEON5 7
#define GAMEON6 8
#define END 9
*/

int data = 0;
int score = 0;
//int random=0;

void start_screen();
void play_screen();
void end_screen();

int main(int argc, char **argv)
{
/*	printbmp(START);
	sleep(1);
	printbmp(GAMEON0);
	sleep(1);
	printbmp(GAMEON1);
	sleep(1);
	printbmp(GAMEON2);
	sleep(1);
	printbmp(GAMEON3);
	sleep(1);
*/
	
	pthread_t thread;
	pthread_attr_t attr;
	int ret_pthread;

	pthread_attr_init(&attr);
	
	ret_pthread = pthread_create(&thread, &attr, ts_read, NULL);
	if(ret_pthread < 0)
	{
		printf("thread create failed..\n");
	}
	

	start_screen();

	//ts_open();
	//ts_init();
	//ts_read(random);

	play_screen();

	end_screen();

	pthread_join(thread, NULL);
	//ts_close();

/*
	pthread_t p_thread;

	srand(time(NULL));

	pthread_create(&p_thread, NULL, &button_func, (void*) &data);

	start_screen();

	init_frame();

	play_game();

	release_frame();
	return 0;
*/
}


void start_screen()
{
	printbmp(START);
}

void play_screen()
{
	int i=0;
	int random;
	int num;
	
	//srand(time(NULL));

	printbmp(GAMEON0);
	sleep(1);

	while(10)
	{
		random = rand()%7+2;
		printbmp(random);

		switch(random)
		{
			case GAMEON1:
				//if( x > 60 && x < 155 && y > 95 && y < 180 && (cur_time + offset) < ts.time.tv_sec )
				sleep(2);
				if(yTerminate_one == 1)
				{
				printf("=======yTerminate======== %d\n", yTerminate_one);
					printbmp(GAMEON0);
					sleep(1);
					yTerminate_one = 0;
				}
				break;
			case GAMEON2:
				sleep(2);
				if(yTerminate_two == 1)
				{
				printf("=======yTerminate======== %d\n", yTerminate_two);
					printbmp(GAMEON0);
					sleep(1);
					yTerminate_two = 0;
				}
				break;
			case GAMEON3:
				sleep(2);
				if(yTerminate_three == 1)
				{
				printf("=======yTerminate======== %d\n", yTerminate_three);
					printbmp(GAMEON0);
					sleep(1);
					yTerminate_three = 0;
				}
				break;
			case GAMEON4:
				sleep(2);
				if(yTerminate_four == 1)
				{
				printf("=======yTerminate======== %d\n", yTerminate_four);
					printbmp(GAMEON0);
					sleep(1);
					yTerminate_four = 0;
				}
				break;
			case GAMEON5:
				sleep(2);
				if(yTerminate_five == 1)
				{
				printf("=======yTerminate======== %d\n", yTerminate_five);
					printbmp(GAMEON0);
					sleep(1);
					yTerminate_five = 0;
				}
				break;
			case GAMEON6:
				sleep(2);
				if(yTerminate_six == 1)
				{
				printf("=======yTerminate======== %d\n", yTerminate_six);
					printbmp(GAMEON0);
					sleep(1);
					yTerminate_six = 0;
				}
				break;
		}
		
	}
	gTerminate = 1;

	/*
	int randnum;
	int count = 0;
	int life = 3;
	int differ = 40;

	randnum = rand()%8;

	draw_frame(randnum);
	draw_score(score);

	fnd(life);

	while(count < 600) {
		draw_time_bar(count);
		if(data!=0){
			if(data == randnum+1) {
				randnum = rand()%8;
				if(score < 40)
					draw_block(random_pixel(),differ - score, randnum);
				else
					draw_block(random_pixel(), 1, randnum);	
	
				draw_score(++score);
				data = 0;
			}
			else {
				led_on();
				fnd(--life);
				if(life <= 0){
					fnd(0);
					break;
				}
				data = 0;
			}
		}
			
		count++;
		usleep(100000);
	}

	printbmp(GAMEOVER);
	draw_score(score);
	usleep(200000);
	*/

}

void end_screen()
{
	printbmp(END);
}
