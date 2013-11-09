 struct kioctx *ctx;
    long ret = 0;
    int i = 0;
 -  struct blk_plug plug;
    struct kiocb_batch batch;
  
    if (unlikely(nr < 0))
 @@ -1700,8 +1699,6 @@ long do_io_submit(aio_context_t ctx_id, long nr,
  
    kiocb_batch_init(&batch, nr);
  
 -  blk_start_plug(&plug);
 -
    /*
     * AKPM: should this return a partial result if some of the IOs were
     * successfully submitted?
 @@ -1724,8 +1721,7 @@ long do_io_submit(aio_context_t ctx_id, long nr,
      if (ret)
        break;
    }
 -  blk_finish_plug(&plug);
 -
 +  
    kiocb_batch_free(ctx, &batch);
    put_ioctx(ctx);
    return i ? i : ret;
