 extern int vm_highmem_is_dirtyable;
  extern int block_dump;
  extern int laptop_mode;

+#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +extern int dyn_dirty_writeback_enabled;
 +extern unsigned int dirty_writeback_active_interval;
 +extern unsigned int dirty_writeback_suspend_interval;
 +#endif
  


  int dirty_writeback_centisecs_handler(struct ctl_table *, int,
                void __user *, size_t *, loff_t *);
  
 +#ifdef CONFIG_DYNAMIC_PAGE_WRITEBACK
 +int dynamic_dirty_writeback_handler(struct ctl_table *, int,
 +              void __user *, size_t *, loff_t *);
 +int dirty_writeback_active_centisecs_handler(struct ctl_table *, int,
 +              void __user *, size_t *, loff_t *);
 +int dirty_writeback_suspend_centisecs_handler(struct ctl_table *, int,
 +              void __user *, size_t *, loff_t *);
 +#endif
 +
  void global_dirty_limits(unsigned l
