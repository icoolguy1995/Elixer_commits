
    parse_early_param();
    parse_args("Booting kernel", static_command_line, __start___param,
         __stop___param - __start___param,
 -       0, 0, &unknown_bootoption);
 +       -1, -1, &unknown_bootoption);
  
    jump_label_init();
