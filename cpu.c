#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/sched/loadavg.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module logging CPU load every N seconds");
MODULE_VERSION("1.0");

static unsigned int interval = 10; // Default interval: 10 seconds
module_param(interval, uint, 0444);
MODULE_PARM_DESC(interval, "Time interval in seconds between log entries");

static struct timer_list cpu_timer;

// Timer callback function
static void log_cpu_load(struct timer_list *t) {
    unsigned long load = avenrun[0]; // 1-minute load average in fixed-point
    unsigned long load_int = load >> FSHIFT; // Integer part
    unsigned long load_frac = load & ((1 << FSHIFT) - 1); // Fractional part

    pr_info("[CPU Load Logger] Current CPU load: %lu.%02lu\n",
            load_int, (load_frac * 100) >> FSHIFT);

    // Re-arm the timer
    mod_timer(&cpu_timer, jiffies + interval * HZ);
}

static int __init cpu_logger_init(void) {
    pr_info("[CPU Load Logger] Initializing module with interval = %u seconds\n", interval);

    // Initialize and start the timer
    timer_setup(&cpu_timer, log_cpu_load, 0);
    mod_timer(&cpu_timer, jiffies + interval * HZ);

    return 0;
}

static void __exit cpu_logger_exit(void) {
    pr_info("[CPU Load Logger] Exiting module\n");

    // Remove the timer
    del_timer(&cpu_timer);
}

module_init(cpu_logger_init);
module_exit(cpu_logger_exit);
