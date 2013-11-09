
    if (head->height == 0)
      return NULL;
 -retry:
    longcpy(key, __key, geo->keylen);
 +retry:
    dec_key(geo, key);






  }
  miss:
    if (retry_key) {
 -    __key = retry_key;
 +    longcpy(key, retry_key, geo->keylen);
      retry_key = NULL;
      goto retry;
    }

