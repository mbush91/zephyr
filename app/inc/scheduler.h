#ifndef SCHEDULER
#define SCHEDULER

#include <zephyr/zephyr.h>


#define SCHEDULER_TIMER_10MS	1000
#define SCHEDULER_TIMER_20MS	2000
#define SCHEDULER_TIMER_100MS	10000

#define TASK_STACK_SIZE        2048
#define TASK_10MS_PRIORITY 5
#define TASK_20MS_PRIORITY 6
#define TASK_100MS_PRIORITY 7

#define SCHEDULER_BEGIN_RUNNABLE	while(1) {
#define SCHEDULER_END_RUNNABLE	k_sleep(K_FOREVER); }

extern k_tid_t task_10ms_id;
extern k_tid_t task_20ms_id;
extern k_tid_t task_100ms_id;

void scheduler_init(void);
void scheduler_init_tasks(void);

#endif // SCHEDULER
