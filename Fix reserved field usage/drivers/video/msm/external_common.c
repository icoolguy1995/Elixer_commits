uint32 format = HDMI_VFRMT_1920x1080p60_16_9;
    struct fb_var_screeninfo *var = &mfd->fbi->var;
    bool changed = TRUE;
 +  uint32_t userformat = 0;
 +  userformat = var->reserved[3] >> 16;
  
 -  if (var->reserved[3]) {
 -    format = var->reserved[3]-1;
 +  if (userformat) {
 +    format = userformat-1;
      DEV_DBG("reserved format is %d\n", format);
    } else if (hdmi_prim_resolution) {
      format = hdmi_prim_resolution - 1;
    } else {
 -    DEV_DBG("detecting resolution from %dx%d use var->reserved[3]"
 -      " to specify mode", mfd->var_xres, mfd->var_yres);
 +    DEV_DBG("detecting resolution from %dx%d use top 2 bytes of"
 +      " var->reserved[3] to specify mode", mfd->var_xres,
 +      mfd->var_yres);
      switch (mfd->var_xres) {
      default:
      case  640:
