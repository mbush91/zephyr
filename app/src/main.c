#include <zephyr/zephyr.h>
#include "stdbool.h"
#include "scheduler.h"

#define MY_STACK_SIZE 4096
#define TRIGGER_TIME_MS	1000
#define RUNNABLE_1X_PRIORITY 5
#define RUNNABLE_2X_PRIORITY 6
#define RUNNABLE_4X_PRIORITY 7


static k_tid_t tid_1x;
struct k_thread runnable_1x_thread;
K_THREAD_STACK_DEFINE(t1x_stack, MY_STACK_SIZE);
void runnable_1x(void *a, void *b, void *c)
{
	BEGIN_RUNNABLE
		printk("1x\n");
	END_RUNNABLE
}

static k_tid_t tid_2x;
struct k_thread runnable_2x_thread;
K_THREAD_STACK_DEFINE(t2x_stack, MY_STACK_SIZE);
void runnable_2x(void *a, void *b, void *c)
{
	BEGIN_RUNNABLE
		printk("2x\n");
	END_RUNNABLE
}

static k_tid_t tid_4x;
struct k_thread runnable_4x_thread;
K_THREAD_STACK_DEFINE(t4x_stack, MY_STACK_SIZE);
void runnable_4x(void *a, void *b, void *c)
{
	BEGIN_RUNNABLE
		printk("4x\n");	
		while(1){}
	END_RUNNABLE
}

void thread_wakeup(k_tid_t thread)
{
	if (is_thread_finished(thread) )
	{
		k_wakeup(thread);
	}
	else
	{
		printk("Thread Overrun!!!!");
	}
}

void init_runnables(void) 
{
tid_1x = k_thread_create(&runnable_1x_thread, t1x_stack,
					K_THREAD_STACK_SIZEOF(t1x_stack),runnable_1x,
					NULL, NULL, NULL,RUNNABLE_1X_PRIORITY, 0, K_FOREVER);

tid_2x = k_thread_create(&runnable_2x_thread, t2x_stack,
					K_THREAD_STACK_SIZEOF(t2x_stack),runnable_2x,
					NULL, NULL, NULL,RUNNABLE_2X_PRIORITY, 0, K_FOREVER);
								
tid_4x = k_thread_create(&runnable_4x_thread, t4x_stack,
					K_THREAD_STACK_SIZEOF(t4x_stack),runnable_4x,
					NULL, NULL, NULL,RUNNABLE_4X_PRIORITY, 0, K_FOREVER);
}


static unsigned char timer_cnt = 0;
static bool timer_first = true;
void timer_fn(struct k_timer *dummy)
{

	printk("Timer Trigger!\n");
	
	if(false == timer_first) {
		thread_wakeup(tid_1x);
		if( 0 == (timer_cnt & 0x01) ) // 2x 
		{
			thread_wakeup(tid_2x);
		}
		if ( 0 == (timer_cnt & 0x03) ) // 4x 
		{
			thread_wakeup(tid_4x);
		}
	}
	else
	{
		k_thread_start(tid_1x);
		k_thread_start(tid_2x);
		k_thread_start(tid_4x);
		timer_first = false;
	}

	timer_cnt++;

}

K_TIMER_DEFINE(my_timer,timer_fn,NULL);
void main(void)
{
	init_runnables();
	k_timer_start(&my_timer,K_MSEC(TRIGGER_TIME_MS),K_MSEC(TRIGGER_TIME_MS));
}

