 /* SAW regulator constraints */
  struct regulator_init_data msm8930_saw_regulator_core0_pdata =
    /*        ID  vreg_name         min_uV   max_uV */
 -  SAW_VREG_INIT(S5, "8038_s5",         850000, 1300000);
 +  SAW_VREG_INIT(S5, "8038_s5",         590000, 1300000);
  struct regulator_init_data msm8930_saw_regulator_core1_pdata =
 -  SAW_VREG_INIT(S6, "8038_s6",         850000, 1300000);
 +  SAW_VREG_INIT(S6, "8038_s6",         590000, 1300000);
  
  /* PM8038 regulator constraints */
  struct pm8xxx_regulator_platform_data
