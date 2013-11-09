  
    free_uid(new->user);
    new->user = new_user;
 +  sched_autogroup_create_attach(current);
    return 0;
  }
  
    write_unlock_irq(&tasklist_lock);
    if (err > 0) {
      proc_sid_connector(group_leader);
 -    sched_autogroup_create_attach(group_leader);
    }
    return err;
  }
