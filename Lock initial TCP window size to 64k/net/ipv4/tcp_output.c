     else
        *rcv_wnd = min(*rcv_wnd, init_cwnd * mss);
    }
 +  
 +  /* Lock the initial TCP window size to 64K*/
 +  *rcv_wnd = 64240;
