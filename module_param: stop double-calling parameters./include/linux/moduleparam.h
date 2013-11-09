
Browse code
module_param: stop double-calling parameters.
commit ae82fdb upstream.

Commit 026cee0 "params:
<level>_initcall-like kernel parameters" set old-style module
parameters to level 0.  And we call those level 0 calls where we used
to, early in start_kernel().

We also loop through the initcall levels and call the levelled
module_params before the corresponding initcall.  Unfortunately level
0 is early_init(), so we call the standard module_param calls twice.

(Turns out most things don't care, but at least ubi.mtd does).

Change the level to -1 for standard module_param calls.

Reported-by: Benoît Thébaudeau <benoit.thebaudeau@advansee.com>
Signed-off-by: Rusty Russell <rusty@rustcorp.com.au>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
 master
commit 3b9b90d7ab75fd76e106f7cd59989055edfc7353 1 parent 1c183c1
 rustyrussell authored a year ago
 varunchitre15 committed 4 months ago
Showing 2 changed files with 6 additions and 6 deletions. Show Diff Stats
10  include/linux/moduleparam.h View file @ 3b9b90d
 @@ -128,7 +128,7 @@ struct kparam_array
   * The ops can have NULL set or get functions.
   */
  #define module_param_cb(name, ops, arg, perm)              \
 -  __module_param_call(MODULE_PARAM_PREFIX, name, ops, arg, perm, 0)
 +  __module_param_call(MODULE_PARAM_PREFIX, name, ops, arg, perm, -1)
  
  /**
   * <level>_param_cb - general callback for a module/cmdline parameter
 @@ -192,7 +192,7 @@ struct kparam_array
       { (void *)set, (void *)get };        \
    __module_param_call(MODULE_PARAM_PREFIX,      \
            name, &__param_ops_##name, arg,    \
 -          (perm) + sizeof(__check_old_set_param(set))*0, 0)
 +          (perm) + sizeof(__check_old_set_param(set))*0, -1)
  
  /* We don't get oldget: it's often a new-style param_get_uint, etc. */
  static inline int
 @@ -272,7 +272,7 @@ static inline void __kernel_param_unlock(void)
   */
  #define core_param(name, var, type, perm)        \
    param_check_##type(name, &(var));        \
 -  __module_param_call("", name, &param_ops_##type, &var, perm, 0)
 +  __module_param_call("", name, &param_ops_##type, &var, perm, -1)
  #endif /* !MODULE */
  
  /**
 @@ -290,7 +290,7 @@ static inline void __kernel_param_unlock(void)
      = { len, string };          \
    __module_param_call(MODULE_PARAM_PREFIX, name,      \
            &param_ops_string,        \
 -          .str = &__param_string_##name, perm, 0);  \
 +          .str = &__param_string_##name, perm, -1);  \
    __MODULE_PARM_TYPE(name, "string")
  
  /**
 @@ -431,7 +431,7 @@ static inline void destroy_params(const struct kernel_param *params,
    __module_param_call(MODULE_PARAM_PREFIX, name,      \
            &param_array_ops,        \
            .arr = &__param_arr_##name,      \
 -          perm, 0);          \
 +          perm, -1);          \
    __MODULE_PARM_TYPE(name, "array of " #type)
  
  extern struct kernel_param_ops param_array_ops;
