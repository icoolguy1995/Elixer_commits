
+#elif defined(CONFIG_CPU_FREQ_DEFAULT_GOV_INTELLIDEMAND)
 +extern struct cpufreq_governor cpufreq_gov_intellidemand;
 +#define CPUFREQ_DEFAULT_GOVERNOR  (&cpufreq_gov_intellidemand)
  #endif
