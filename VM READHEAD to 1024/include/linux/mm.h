
 void task_dirty_inc(struct task_struct *tsk);
  
  /* readahead.c */
 -#define VM_MAX_READAHEAD  128  /* kbytes */
 +#define VM_MAX_READAHEAD  1024  /* kbytes */
  #define VM_MIN_READAHEAD  16  /* kbytes (includes current page) */
  
  int force_page_cache_readahead(struct address_space *mapping, struct file *filp,
