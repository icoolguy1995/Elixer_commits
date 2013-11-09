#include <linux/buffer_head.h> /* __set_page_dirty_buffers */
  #include <linux/pagevec.h>
  #include <trace/events/writeback.h>
 +#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +#include <linux/earlysuspend.h>
 +#endif
  
  /*
   * Sleep at most 200ms at a time in balance_dirty_pages().
 @@ -91,12 +94,37 @@
  unsigned long vm_dirty_bytes;
  
  /*
 - * The interval between `kupdate'-style writebacks
 + * The default intervals between `kupdate'-style writebacks
   */
 -unsigned int dirty_writeback_interval = 5 * 100; /* centiseconds */
 +#define DEFAULT_DIRTY_WRITEBACK_INTERVAL   5 * 100 /* centiseconds */
 +#define HIGH_DIRTY_WRITEBACK_INTERVAL    15 * 100 /* centiseconds */
  
 +/*
 + * The interval between `kupdate'-style writebacks
 + */
 +unsigned int dirty_writeback_interval = DEFAULT_DIRTY_WRITEBACK_INTERVAL; /* centiseconds */
  EXPORT_SYMBOL_GPL(dirty_writeback_interval);
  
 +#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +/*
 + * The dynamic writeback activation status
 + */
 +int dyn_dirty_writeback_enabled = 1;
 +EXPORT_SYMBOL_GPL(dyn_dirty_writeback_enabled);
 +
 +/*
 + * The interval between `kupdate'-style writebacks when the system is active
 + */
 +unsigned int dirty_writeback_active_interval = HIGH_DIRTY_WRITEBACK_INTERVAL; /* centiseconds */
 +EXPORT_SYMBOL_GPL(dirty_writeback_active_interval);
 +
 +/*
 + * The interval between `kupdate'-style writebacks when the system is suspended
 + */
 +unsigned int dirty_writeback_suspend_interval = DEFAULT_DIRTY_WRITEBACK_INTERVAL; /* centiseconds */
 +EXPORT_SYMBOL_GPL(dirty_writeback_suspend_interval);
 +#endif
 +


   return 0;
  }
  
 +#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +/*
 + * Manages the dirty page writebacks activation status
 + */
 +static void set_dirty_writeback_status(bool active) {
 +  /* Change the current dirty writeback interval according to the
 +   * status provided */
 +  dirty_writeback_interval = (active) ?
 +                dirty_writeback_active_interval :
 +                dirty_writeback_suspend_interval;
 +
 +  /* Update the timer related to dirty writebacks interval */
 +  bdi_arm_supers_timer();
 +
 +  /* Print debug info */
 +  pr_debug("%s: Set dirty_writeback_interval = %d centisecs\n",
 +        __func__, dirty_writeback_interval);
 +}
 +
 +/*
 + * sysctl handler for /proc/sys/vm/dyn_dirty_writeback_enabled
 + */
 +int dynamic_dirty_writeback_handler(struct ctl_table *table, int write,
 +  void __user *buffer, size_t *lenp, loff_t *ppos)
 +{
 +  int ret;
 +  int old_status = dyn_dirty_writeback_enabled;
 +
 +  /* Get and store the new status */
 +  ret = proc_dointvec_minmax(table, write, buffer, lenp, ppos);
 +
 +  /* If the dynamic writeback has been enabled then set the active
 +   * dirty writebacks interval, otherwise if the feature has been
 +   * disabled, set the suspend interval (the default interval)
 +   * to restore the standard functionality */
 +  if (ret == 0 && write && dyn_dirty_writeback_enabled != old_status)
 +    set_dirty_writeback_status(!!dyn_dirty_writeback_enabled);
 +
 +  return ret;
 +}
 +
 +/*
 + * sysctl handler for /proc/sys/vm/dirty_writeback_active_centisecs
 + */
 +int dirty_writeback_active_centisecs_handler(ctl_table *table, int write,
 +  void __user *buffer, size_t *length, loff_t *ppos)
 +{
 +  proc_dointvec_minmax(table, write, buffer, length, ppos);
 +  return 0;
 +}
 +
 +/*
 + * sysctl handler for /proc/sys/vm/dirty_writeback_suspend_centisecs
 + */
 +int dirty_writeback_suspend_centisecs_handler(ctl_table *table, int write,
 +  void __user *buffer, size_t *length, loff_t *ppos)
 +{
 +  proc_dointvec_minmax(table, write, buffer, length, ppos);
 +  return 0;
 +}
 +#endif
 +
  #ifdef CONFIG_BLOCK
  void laptop_mode_timer_fn(unsigned long data)
  {

+#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +/*
 + * Sets the dirty page writebacks interval for suspended system
 + */
 +static void dirty_writeback_early_suspend(struct early_suspend *handler)
 +{
 +  if (dyn_dirty_writeback_enabled)
 +    set_dirty_writeback_status(false);
 +}
 +
 +/*
 + * Sets the dirty page writebacks interval for active system
 + */
 +static void dirty_writeback_late_resume(struct early_suspend *handler)
 +{
 +  if (dyn_dirty_writeback_enabled)
 +    set_dirty_writeback_status(true);
 +}
 +
 +/*
 + * Struct for the dirty page writeback management during suspend/resume
 + */
 +static struct early_suspend dirty_writeback_suspend = {
 +  .suspend = dirty_writeback_early_suspend,
 +  .resume = dirty_writeback_late_resume,
 +};
 +#endif
 +


  {
    int shift;

+#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +  /* Register the dirty page writeback management during suspend/resume */
 +  register_early_suspend(&dirty_writeback_suspend);
 +#endif
 +
 writeback_set_ratelimit();
    register_cpu_notifier(&ratelimit_nb);


