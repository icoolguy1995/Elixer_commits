 * The minimum number of bits of entropy before we wake up a read on
   * /dev/random.  Should be enough to do a significant reseed.
   */
 -static int random_read_wakeup_thresh = 64;
 +static int random_read_wakeup_thresh = 256;
  
  /*
   * If the entropy count falls under this number of bits, then we
   * should wake up processes which are selecting or polling on write
   * access to /dev/random.
   */
 -static int random_write_wakeup_thresh = 128;
 +static int random_write_wakeup_thresh = 512;
  
  /*
   * When the input pool goes over trickle_thresh, start dropping most
 @@ -1028,57 +1028,7 @@ void rand_initialize_disk(struct gendisk *disk)
  static ssize_t
  random_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
  {
 -  ssize_t n, retval = 0, count = 0;
 -
 -  if (nbytes == 0)
 -    return 0;
 -
 -  while (nbytes > 0) {
 -    n = nbytes;
 -    if (n > SEC_XFER_SIZE)
 -      n = SEC_XFER_SIZE;
 -
 -    DEBUG_ENT("reading %d bits\n", n*8);
 -
 -    n = extract_entropy_user(&blocking_pool, buf, n);
 -
 -    DEBUG_ENT("read got %d bits (%d still needed)\n",
 -        n*8, (nbytes-n)*8);
 -
 -    if (n == 0) {
 -      if (file->f_flags & O_NONBLOCK) {
 -        retval = -EAGAIN;
 -        break;
 -      }
 -
 -      DEBUG_ENT("sleeping?\n");
 -
 -      wait_event_interruptible(random_read_wait,
 -        input_pool.entropy_count >=
 -             random_read_wakeup_thresh);
 -
 -      DEBUG_ENT("awake\n");
 -
 -      if (signal_pending(current)) {
 -        retval = -ERESTARTSYS;
 -        break;
 -      }
 -
 -      continue;
 -    }
 -
 -    if (n < 0) {
 -      retval = n;
 -      break;
 -    }
 -    count += n;
 -    buf += n;
 -    nbytes -= n;
 -    break;    /* This break makes the device work */
 -        /* like a named pipe */
 -  }
 -
 -  return (count ? count : retval);
 +  return extract_entropy_user(&nonblocking_pool, buf, nbytes);
  }
  
  static ssize_t
