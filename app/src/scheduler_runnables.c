#include <zephyr/zephyr.h>
#include "scheduler.h"

// Define Threads witch execute runnables
k_tid_t task_10ms_id;
struct k_thread task_10ms_thread;
K_THREAD_STACK_DEFINE(task_10ms_stack, TASK_STACK_SIZE);
void task_10ms_runnables(void *a, void *b, void *c)
{
	SCHEDULER_BEGIN_RUNNABLE
		printk("10ms runnable\n");
	SCHEDULER_END_RUNNABLE
}

k_tid_t task_20ms_id;
struct k_thread task_20ms_thread;
K_THREAD_STACK_DEFINE(task_20ms_stack, TASK_STACK_SIZE);
void task_20ms_runnables(void *a, void *b, void *c)
{
	SCHEDULER_BEGIN_RUNNABLE
		printk("20ms runnable\n");
	SCHEDULER_END_RUNNABLE
}

k_tid_t task_100ms_id;
struct k_thread task_100ms_thread;
K_THREAD_STACK_DEFINE(task_100ms_stack, TASK_STACK_SIZE);
void task_100ms_runnables(void *a, void *b, void *c)
{
	SCHEDULER_BEGIN_RUNNABLE
		printk("100ms runnable\n");
	SCHEDULER_END_RUNNABLE
}


void scheduler_init_tasks(void) 
{
    task_10ms_id = k_thread_create(&task_10ms_thread, task_10ms_stack,
					K_THREAD_STACK_SIZEOF(task_10ms_stack),task_10ms_runnables,
					NULL, NULL, NULL,TASK_10MS_PRIORITY, 0, K_FOREVER);

    task_20ms_id = k_thread_create(&task_20ms_thread, task_20ms_stack,
					K_THREAD_STACK_SIZEOF(task_20ms_stack),task_20ms_runnables,
					NULL, NULL, NULL,TASK_20MS_PRIORITY, 0, K_FOREVER);

    task_100ms_id = k_thread_create(&task_100ms_thread, task_100ms_stack,
					K_THREAD_STACK_SIZEOF(task_100ms_stack),task_100ms_runnables,
					NULL, NULL, NULL,TASK_100MS_PRIORITY, 0, K_FOREVER);

}
