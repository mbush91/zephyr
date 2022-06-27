#include <zephyr/zephyr.h>
#include "scheduler.h"


static inline bool scheduler_is_thread_finished(k_tid_t thread)
{
	uint8_t state = thread->base.thread_state;

	return (state & (_THREAD_PENDING | _THREAD_PRESTART | _THREAD_DEAD |
			 _THREAD_DUMMY | _THREAD_SUSPENDED)) != 0U;
}


static inline void scheduler_thread_wakeup(k_tid_t thread)
{
	if (scheduler_is_thread_finished(thread) )
	{
		k_wakeup(thread);
	}
	else
	{
		printk("Thread Overrun!!!!");
	}
}


// Define Timer Tasks to Schedule Threads
static bool scheduler_timer_10ms_first = true;
void scheduler_timer_10ms_task(struct k_timer *dummy)
{
    if (true == scheduler_timer_10ms_first)
    {
        scheduler_timer_10ms_first = false;
        k_thread_start(task_10ms_id);
    }
    else
    {
        scheduler_thread_wakeup(task_10ms_id);
    }
}


static bool scheduler_timer_20ms_first = true;
void scheduler_timer_20ms_task(struct k_timer *dummy)
{
    if (true == scheduler_timer_20ms_first)
    {
        scheduler_timer_20ms_first = false;
        k_thread_start(task_20ms_id);
    }
    else
    {
        scheduler_thread_wakeup(task_20ms_id);
    }
}


static bool scheduler_timer_100ms_first = true;
void scheduler_timer_100ms_task(struct k_timer *dummy)
{
    if (true == scheduler_timer_100ms_first)
    {
        scheduler_timer_100ms_first = false;
        k_thread_start(task_100ms_id);
    }
    else
    {
        scheduler_thread_wakeup(task_100ms_id);
    }
}


// Define Timers
K_TIMER_DEFINE(scheduler_timer_10ms,scheduler_timer_10ms_task,NULL);
K_TIMER_DEFINE(scheduler_timer_20ms,scheduler_timer_20ms_task,NULL);
K_TIMER_DEFINE(scheduler_timer_100ms,scheduler_timer_100ms_task,NULL);


void scheduler_init(void)
{
    scheduler_init_tasks();
    k_timer_start(&scheduler_timer_10ms,K_MSEC(SCHEDULER_TIMER_10MS),K_MSEC(SCHEDULER_TIMER_10MS));
    k_timer_start(&scheduler_timer_20ms,K_MSEC(SCHEDULER_TIMER_20MS),K_MSEC(SCHEDULER_TIMER_20MS));
    k_timer_start(&scheduler_timer_100ms,K_MSEC(SCHEDULER_TIMER_100MS),K_MSEC(SCHEDULER_TIMER_100MS));
}
