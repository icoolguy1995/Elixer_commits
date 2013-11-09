+#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +  {
 +    .procname  = "dynamic_dirty_writeback",
 +    .data    = &dyn_dirty_writeback_enabled,
 +    .maxlen    = sizeof(dyn_dirty_writeback_enabled),
 +    .mode    = 0644,
 +    .proc_handler  = dynamic_dirty_writeback_handler,
 +    .extra1    = &zero,
 +    .extra2    = &one,
 +  },
 +  {
 +    .procname  = "dirty_writeback_active_centisecs",
 +    .data    = &dirty_writeback_active_interval,
 +    .maxlen    = sizeof(dirty_writeback_active_interval),
 +    .mode    = 0644,
 +    .proc_handler  = dirty_writeback_active_centisecs_handler,
 +    .extra1    = &zero,
 +  },
 +  {
 +    .procname  = "dirty_writeback_suspend_centisecs",
 +    .data    = &dirty_writeback_suspend_interval,
 +    .maxlen    = sizeof(dirty_writeback_suspend_interval),
 +    .mode    = 0644,
 +    .proc_handler  = dirty_writeback_suspend_centisecs_handler,
 +    .extra1    = &zero,
 +  },
 +#endif

 {
      .procname  = "dirty_expire_centisecs",
      .data    = &dirty_expire_interval,
