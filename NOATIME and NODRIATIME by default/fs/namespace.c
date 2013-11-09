 goto dput_out;
  
    /* Default to relatime unless overriden */
 -  if (!(flags & MS_NOATIME))
 -    mnt_flags |= MNT_RELATIME;
 +  // if (!(flags & MS_NOATIME))
 +  //  mnt_flags |= MNT_RELATIME;
  
    /* Separate the per-mountpoint flags */
    if (flags & MS_NOSUID)
 @@ -2163,9 +2163,9 @@ long do_mount(char *dev_name, char *dir_name, char *type_page,
      mnt_flags |= MNT_NODEV;
    if (flags & MS_NOEXEC)
      mnt_flags |= MNT_NOEXEC;
 -  if (flags & MS_NOATIME)
 +  // if (flags & MS_NOATIME)
      mnt_flags |= MNT_NOATIME;
 -  if (flags & MS_NODIRATIME)
 +  // if (flags & MS_NODIRATIME)
      mnt_flags |= MNT_NODIRATIME;
    if (flags & MS_STRICTATIME)
      mnt_flags &= ~(MNT_RELATIME | MNT_NOATIME);
