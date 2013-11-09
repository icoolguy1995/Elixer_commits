/* Function prototypes */
  static int  option_probe(struct usb_serial *serial,
        const struct usb_device_id *id);
 +static void option_release(struct usb_serial *serial);
  static int option_send_setup(struct usb_serial_port *port);
  static void option_instat_callback(struct urb *urb);
  
 @@ -1273,7 +1274,7 @@ struct option_blacklist_info {
    .ioctl             = usb_wwan_ioctl,
    .attach            = usb_wwan_startup,
    .disconnect        = usb_wwan_disconnect,
 -  .release           = usb_wwan_release,
 +  .release           = option_release,
    .read_int_callback = option_instat_callback,
  #ifdef CONFIG_PM
    .suspend           = usb_wwan_suspend,
 @@ -1384,6 +1385,15 @@ static int option_probe(struct usb_serial *serial,
    return 0;
  }
  
 +static void option_release(struct usb_serial *serial)
 +{
 +  struct usb_wwan_intf_private *priv = usb_get_serial_data(serial);
 +
 +  usb_wwan_release(serial);
 +
 +  kfree(priv);
 +}
 +
  static void option_instat_callback(struct urb *urb)
  {
    int err;
