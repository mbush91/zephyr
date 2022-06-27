#ifndef SCHEDULER
#define SCHEDULER

#include <zephyr/zephyr.h>

// Config Macros


// Function like macros
#define BEGIN_RUNNABLE	while(1) {
#define END_RUNNABLE	k_sleep(K_FOREVER); }



static inline bool is_thread_finished(k_tid_t thread)
{
	uint8_t state = thread->base.thread_state;

	return (state & (_THREAD_PENDING | _THREAD_PRESTART | _THREAD_DEAD |
			 _THREAD_DUMMY | _THREAD_SUSPENDED)) != 0U;

}

#endif // SCHEDULER
