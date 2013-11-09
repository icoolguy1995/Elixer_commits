 }
  
 +#ifdef CONFIG_CPU_VOLTAGE_TABLE
 +// faux123 - Initial definitions
 +#define HFPLL_MIN_VDD     590000
 +#define HFPLL_MAX_VDD    1350000
 +
 +ssize_t acpuclk_get_vdd_levels_str(char *buf) {
 +
 +  int i, len = 0;
 +
 +  if (buf) {
 +    mutex_lock(&driver_lock);
 +
 +    for (i = 0; drv.acpu_freq_tbl[i].speed.khz; i++) {
 +      /* updated to use uv required by 8x60 architecture - faux123 */
 +      len += sprintf(buf + len, "%8lu: %8d\n", drv.acpu_freq_tbl[i].speed.khz,
 +        drv.acpu_freq_tbl[i].vdd_core );
 +    }
 +
 +    mutex_unlock(&driver_lock);
 +  }
 +  return len;
 +}
 +
 +/* updated to use uv required by 8x60 architecture - faux123 */
 +void acpuclk_set_vdd(unsigned int khz, int vdd_uv) {
 +
 +  int i;
 +  unsigned int new_vdd_uv;
 +
 +  mutex_lock(&driver_lock);
 +
 +  for (i = 0; drv.acpu_freq_tbl[i].speed.khz; i++) {
 +    if (khz == 0)
 +      new_vdd_uv = min(max((unsigned int)(drv.acpu_freq_tbl[i].vdd_core + vdd_uv),
 +        (unsigned int)HFPLL_MIN_VDD), (unsigned int)HFPLL_MAX_VDD);
 +    else if ( drv.acpu_freq_tbl[i].speed.khz == khz)
 +      new_vdd_uv = min(max((unsigned int)vdd_uv,
 +        (unsigned int)HFPLL_MIN_VDD), (unsigned int)HFPLL_MAX_VDD);
 +    else 
 +      continue;
 +
 +    drv.acpu_freq_tbl[i].vdd_core = new_vdd_uv;
 +  }
 +  pr_warn("kernel: Using custom voltage!\n");
 +  mutex_unlock(&driver_lock);
 +}
 +#endif  /* CONFIG_CPU_VOTALGE_TABLE */
 +
  #ifdef CONFIG_CPU_FREQ_MSM
  static struct cpufreq_frequency_table freq_table[NR_CPUS][35];
