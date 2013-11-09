 #include <mach/msm_bus.h>
  #include <mach/rpm-regulator.h>
  
 +#ifdef CONFIG_FORCE_FAST_CHARGE
 +#include <linux/fastchg.h>
 +#define USB_FASTCHG_LOAD 1000 /* uA */
 +#endif
 +
  #define MSM_USB_BASE  (motg->regs)
  #define DRIVER_NAME  "msm_otg"
  

      return;
  
    dev_info(motg->phy.dev, "Avail curr from USB = %u\n", mA);
 +  
 +  #ifdef CONFIG_FORCE_FAST_CHARGE
 +  if (force_fast_charge == 1) {
 +    // DooMLoRD: dont override charging current if available current is greater
 +    if (mA >= USB_FASTCHG_LOAD){
 +      pr_info("Available current already greater than USB fastcharging current!!!\n");
 +      pr_info("Override of USB charging current cancelled.\n");
 +    } else {        
 +      mA = USB_FASTCHG_LOAD;
 +      pr_info("USB fast charging is ON!!!\n");
 +    }
 +      dev_info(motg->phy.dev, "Avail curr from USB = %u\n", mA);
 +
 +  } else {
 +    pr_info("USB fast charging is OFF.\n");
 +  }
 +#endif
