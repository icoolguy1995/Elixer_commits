   return sprintf(buf, "%u\n", policy->cpuinfo.max_freq);
  }
  
 +#ifdef CONFIG_CPU_VOLTAGE_TABLE
 +
 +extern ssize_t acpuclk_get_vdd_levels_str(char *buf);
 +extern void acpuclk_set_vdd(unsigned acpu_khz, int vdd);
 +
 +static ssize_t show_vdd_levels(struct kobject *a, struct attribute *b, char *buf) {
 +  return acpuclk_get_vdd_levels_str(buf);
 +}
 +
 +static ssize_t store_vdd_levels(struct kobject *a, struct attribute *b, const char *buf, size_t count) {
 +
 +  int i = 0, j;
 +  int pair[2] = { 0, 0 };
 +  int sign = 0;
 +
 +  if (count < 1)
 +    return 0;
 +
 +  if (buf[0] == '-') {
 +    sign = -1;
 +    i++;
 +  }
 +  else if (buf[0] == '+') {
 +    sign = 1;
 +    i++;
 +  }
 +
 +  for (j = 0; i < count; i++) {
 +
 +    char c = buf[i];
 +
 +    if ((c >= '0') && (c <= '9')) {
 +      pair[j] *= 10;
 +      pair[j] += (c - '0');
 +    }
 +    else if ((c == ' ') || (c == '\t')) {
 +      if (pair[j] != 0) {
 +        j++;
 +
 +        if ((sign != 0) || (j > 1))
 +          break;
 +      }
 +    }
 +    else
 +      break;
 +  }
 +
 +  if (sign != 0) {
 +    if (pair[0] > 0)
 +      acpuclk_set_vdd(0, sign * pair[0]);
 +  }
 +  else {
 +    if ((pair[0] > 0) && (pair[1] > 0))
 +      acpuclk_set_vdd((unsigned)pair[0], pair[1]);
 +    else
 +      return -EINVAL;
 +  }
 +  return count;
 +}
 +
 +#endif  /* CONFIG_CPU_VOLTAGE_TABLE */
 +
  cpufreq_freq_attr_ro_perm(cpuinfo_cur_freq, 0400);
  cpufreq_freq_attr_ro(cpuinfo_min_freq);
  cpufreq_freq_attr_ro(cpuinfo_max_freq);




 cpufreq_freq_attr_rw(scaling_max_freq);
  cpufreq_freq_attr_rw(scaling_governor);
  cpufreq_freq_attr_rw(scaling_setspeed);
 +#ifdef CONFIG_CPU_VOLTAGE_TABLE
 +define_one_global_rw(vdd_levels);
 +#endif

 NULL
  };
  
 +#ifdef CONFIG_CPU_VOLTAGE_TABLE
 +static struct attribute *vddtbl_attrs[] = {
 +  &vdd_levels.attr,
 +  NULL
 +};
 +
 +static struct attribute_group vddtbl_attr_group = {
 +  .attrs = vddtbl_attrs,
 +  .name = "vdd_table",
 +};
 +#endif  /* CONFIG_CPU_VOLTAGE_TABLE */
 +
  struct kobject *cpufreq_global_kobject;
  EXPORT_SYMBOL(cpufreq_global_kobject);



int cpu;
 +  #ifdef CONFIG_CPU_VOLTAGE_TABLE
 +  int rc;
 +  #endif  /* CONFIG_CPU_VOLTAGE_TABLE */
  
    if (cpufreq_disabled())
      return -ENODEV;


   cpufreq_global_kobject = kobject_create_and_add("cpufreq", &cpu_subsys.dev_root->kobj);
    BUG_ON(!cpufreq_global_kobject);
    register_syscore_ops(&cpufreq_syscore_ops);
 +  
 +  #ifdef CONFIG_CPU_VOLTAGE_TABLE
 +  rc = sysfs_create_group(cpufreq_global_kobject, &vddtbl_attr_group);
 +  #endif  /* CONFIG_CPU_VOLTAGE_TABLE */
  
    return 0;
  }
