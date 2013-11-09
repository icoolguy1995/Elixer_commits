   __u32 vmode;      /* see FB_VMODE_*    */
    __u32 rotate;      /* angle we rotate counter clockwise */
    __u32 colorspace;    /* colorspace for FOURCC-based modes */
 -  __u32 reserved[5];    /* Reserved for future compatibility */
 +  __u32 reserved[4];    /* Reserved for future compatibility */
  };
  
  struct fb_cmap {
