#define SYSCALL(name, no) \
  asm(".global " #name "\n" \
      #name ":\n" \
      "li $v1, " #no "\n" \
      "syscall 0\n");

/*

Naming scheme:
~~~~~~~~~~~~~~
- "__syscall_[<module name>_]<hex number>": unknown system call
- "__syscall_<name>": known syscall that conflicts with Baselibc and is
  better implemented there
- "__broken_<name>": known syscall that does not work as you would
  expect
- all other names: canonical names extracted from firmware binaries
  unless noted otherwise

Source of information:
~~~~~~~~~~~~~~~~~~~~~~
- "from <module name> symbol table": name found in the symbol table
  some "plain binary" files (notably syscfg.bin) have
- "from <module name> debug string": name deduced from debug output in
  system call implementation
- "from <module name> analysis": deduced from behavior of syscall
  implementation or usage patterns
- no comment: found in unstripped ELF binary symbol table

*/

SYSCALL(__syscall_10001, 0x10001)

SYSCALL(os_sched_lock,   0x10002)
SYSCALL(os_sched_unlock, 0x10003)

SYSCALL(__syscall_10005, 0x10005)
SYSCALL(__syscall_10007, 0x10007)
SYSCALL(__syscall_10009, 0x10009)
SYSCALL(__syscall_1000a, 0x1000a)
SYSCALL(__syscall_1000b, 0x1000b)
SYSCALL(__syscall_1000d, 0x1000d)

SYSCALL(os_time_dly, 0x10010)

SYSCALL(__syscall_10014, 0x10014)
SYSCALL(__syscall_10015, 0x10015)
SYSCALL(__syscall_10016, 0x10016)
SYSCALL(__syscall_10018, 0x10018)
SYSCALL(__syscall_1001a, 0x1001a)
SYSCALL(__syscall_1001c, 0x1001c)

SYSCALL(os_sem_create, 0x1001d)
SYSCALL(os_sem_del,    0x1001e)
SYSCALL(os_sem_pend,   0x1001f)
SYSCALL(os_sem_post,   0x10020)

SYSCALL(__syscall_10021, 0x10021)

SYSCALL(api_install,   0x10028)
SYSCALL(api_uninstall, 0x10029)

SYSCALL(printf,         0x10032)
SYSCALL(serial_getc,    0x10033) /* from syscfg.sys symbol table */
SYSCALL(reset_baudrate, 0x10034) /* from syscfg.sys symbol table */

SYSCALL(mdelay,         0x10035)
SYSCALL(udelay,         0x10036)
SYSCALL(__syscall_rand, 0x10037) /* from syscfg.sys symbol table */
SYSCALL(get_count,      0x10038)
SYSCALL(get_c0_count,   0x10039) /* from syscfg.sys symbol table */

SYSCALL(malloc,       0x1003a)
SYSCALL(free,         0x1003b)
SYSCALL(malloc_dma,   0x1003c)
SYSCALL(free_dma,     0x1003d)
SYSCALL(realloc,      0x1003e)
SYSCALL(os_mem_query, 0x1003f)
SYSCALL(print_mem,    0x10040) /* from syscfg.sys symbol table */

SYSCALL(sys_mount,     0x10041)
SYSCALL(sys_umount,    0x10042)
SYSCALL(sys_mknod,     0x10043)
SYSCALL(sys_open,      0x10044)
SYSCALL(sys_close,     0x10045)
SYSCALL(sys_read,      0x10046)
SYSCALL(sys_write,     0x10047)
SYSCALL(sys_lseek,     0x10048)
SYSCALL(sys_fcntl,     0x10049)
SYSCALL(sys_creat,     0x1004a) /* from syscfg.sys symbol table */
SYSCALL(sys_rename,    0x1004b) /* from libc_fs.so */
SYSCALL(sys_chdir,     0x1004c) /* from syscfg.sys symbol table, called by 0x60009, always returns EINVAL */
SYSCALL(sys_getcwd,    0x1004d) /* from syscfg.sys symbol table, called by 0x6000e, always returns EINVAL */
SYSCALL(sys_mkdir,     0x1004e)
SYSCALL(sys_rmdir,     0x1004f) /* from libc_fs.so */
SYSCALL(sys_fstat,     0x10050)
SYSCALL(sys_stat,      0x10051) /* from libc_fs.so */
SYSCALL(sys_statfs,    0x10052) /* from libc_fs.so */
SYSCALL(sys_utime,     0x10053) /* from libc_fs.so */
SYSCALL(sys_truncate,  0x10054) /* from syscfg.sys symbol table, called by 0x6000c */
SYSCALL(sys_ftruncate, 0x10055)
SYSCALL(sys_fsync,     0x10056)
SYSCALL(sys_fchdir,    0x10057) /* from syscfg.sys symbol table, called by 0x6000a */
SYSCALL(sys_flock,     0x10058) /* from syscfg.sys symbol table */
SYSCALL(sys_remove,    0x10059)
SYSCALL(sys_tell,      0x1005a) /* from syscfg.sys symbol table */
SYSCALL(sys_readdir,   0x1005b) /* from syscfg.sys symbol table */
SYSCALL(sys_seekdir,   0x1005c) /* from syscfg.sys symbol table */
SYSCALL(sys_rewinddir, 0x1005d) /* from syscfg.sys symbol table */
SYSCALL(sys_lastdir,   0x1005e) /* from syscfg.sys symbol table, called by 0x60031 */
SYSCALL(sys_prevdir,   0x1005f) /* from syscfg.sys symbol table, called by 0x6002c */
SYSCALL(sys_reset2parentdir, 0x10060) /* from syscfg.sys symbol table, called by 0x60032 */
SYSCALL(sys_ioctl,     0x10061)
SYSCALL(sys_mmap,      0x10062)
SYSCALL(sys_munmap,    0x10063)

SYSCALL(sys_msync,     0x10064) /* from syscfg.sys symbol table, unimplemented */
SYSCALL(__broken_fork, 0x10065) /* unimplemented */
SYSCALL(_execve,       0x10066) /* from syscfg.sys symbol table */
SYSCALL(_exit,           0x10067) /* from syscfg.sys debug string */
SYSCALL(sys_shm_open,    0x10068) /* called by 0x70098 */
SYSCALL(sys_shm_unlink,  0x10069) /* called by 0x70099 */

SYSCALL(insmod, 0x1006a)
SYSCALL(rmmod,  0x1006b)

SYSCALL(dlopen,  0x1006c)
SYSCALL(dlclose, 0x1006d)
SYSCALL(dlsym,   0x1006e)
SYSCALL(dlerror, 0x1006f)

SYSCALL(do_gettimeofday, 0x10070)
SYSCALL(__syscall_10071, 0x10071)
SYSCALL(sys_mem_allocate, 0x10072)
SYSCALL(sys_mem_free,     0x10073)
SYSCALL(sys_get_phyaddr,  0x10074)
SYSCALL(sys_get_max_free, 0x10075)

SYSCALL(get_ic_type,   0x10079)
SYSCALL(get_sdram_cap, 0x1007a)

SYSCALL(system_codecheck, 0x1007d)

SYSCALL(serial_putc, 0x1007f)

SYSCALL(get_ddr_prio, 0x10080)
SYSCALL(set_ddr_prio, 0x10081)

SYSCALL(os_cpu_save_sr,    0x20000)
SYSCALL(os_cpu_store_sr,   0x20001)
SYSCALL(__syscall_memcpy,  0x20002)
SYSCALL(__syscall_memset,  0x20003)

SYSCALL(__syscall_2000b,   0x2000b)

SYSCALL(sprintf,           0x20013)
SYSCALL(__syscall_20014,   0x20014)
SYSCALL(__syscall_20015,   0x20015)

SYSCALL(request_irq,       0x20017)
SYSCALL(free_irq,          0x20018)
SYSCALL(__syscall_20019,   0x20019)
SYSCALL(__syscall_2001a,   0x2001a)
SYSCALL(get_dma_chan,      0x2001b)
SYSCALL(kmalloc,           0x20023)
SYSCALL(kfree,             0x20024)
SYSCALL(register_chrdev,   0x20025)
SYSCALL(unregister_chrdev, 0x20026)
SYSCALL(driver_register,   0x20032)
SYSCALL(driver_unregister, 0x20033)

SYSCALL(__syscall_20035,   0x20035)
SYSCALL(__syscall_20036,   0x20036)
SYSCALL(__syscall_2003b,   0x2003b)
SYSCALL(__syscall_2003c,   0x2003c)

SYSCALL(kernel_sym, 0x2003e)

SYSCALL(init_timer,     0x2003f)
SYSCALL(add_timer,      0x20040) /* from syscfg.sys symbol table */
SYSCALL(mod_timer,      0x20041)
SYSCALL(del_timer,      0x20044) /* from syscfg.sys symbol table */
SYSCALL(del_timer_sync, 0x20043)

SYSCALL(__syscall_20055, 0x20055)

SYSCALL(get_ab_timer, 0x2005c)
SYSCALL(get_ab_ticks, 0x2005d) /* from syscfg.sys symbol table */

SYSCALL(set_load_from_pc,          0x2005e) /* from syscfg.sys debug string */
SYSCALL(set_image_path_name_of_pc, 0x2005f) /* from syscfg.sys debug string */

SYSCALL(printk, 0x20062)

SYSCALL(gui_get_char_dist_x,              0x30004)
SYSCALL(gui_exec,                         0x30007)
SYSCALL(gui_get_string_by_id,             0x3000d)
SYSCALL(gui_set_common_ui_res,            0x30011)
SYSCALL(gui_set_common_string_res,        0x30012)
SYSCALL(gui_open_ui_res,                  0x30013)
SYSCALL(gui_open_string_res,              0x30014)
SYSCALL(gui_close_resource_file,          0x30015)
SYSCALL(gui_set_language_mode,            0x30021)
SYSCALL(gui_get_language_mode,            0x30022)
SYSCALL(gui_load_bitmap_into_buffer,      0x30023)
SYSCALL(gui_set_dimension,                0x30026)
SYSCALL(gui_load_sub_bitmap_into_buffer,  0x30027)
SYSCALL(gui_select_font_size,             0x3002a)
SYSCALL(gui_create_font,                  0x3002b)
SYSCALL(gui_destroy_font,                 0x3002c)
SYSCALL(gui_bitmap_metrics,               0x30032)
SYSCALL(gui_fb_device_control,            0x30036)
SYSCALL(gui_select_layer,                 0x30037)
SYSCALL(gui_get_word_length,              0x30039)
SYSCALL(gui_screen_update,                0x3003c)
SYSCALL(gui_get_char_pixel_buf,           0x3003d)
SYSCALL(gui_get_string_pixel_buf,         0x3003e)
SYSCALL(gui_wm_move_window,               0x30046)
SYSCALL(gui_wm_create_window,             0x30048)
SYSCALL(gui_wm_set_focus,                 0x3004a)
SYSCALL(gui_wm_delete_window,             0x3004b)
SYSCALL(gui_wm_get_focus,                 0x3004e)
SYSCALL(gui_wm_set_size,                  0x30050)
SYSCALL(gui_dc_get,                       0x30056)
SYSCALL(gui_dc_set_default_fontface,      0x30058)
SYSCALL(gui_dc_set_text_mode,             0x30059)
SYSCALL(gui_dc_set_color,                 0x3005a)
SYSCALL(gui_dc_set_background_color,      0x3005b)
SYSCALL(gui_dc_set_font_size,             0x3005e)
SYSCALL(gui_dc_set_text_align,            0x3005f)
SYSCALL(gui_dc_set_pen_size,              0x30060)
SYSCALL(gui_dc_get_text_mode,             0x30061)
SYSCALL(gui_dc_get_color,                 0x30062)
SYSCALL(gui_dc_get_background_color,      0x30063)
SYSCALL(gui_dc_get_fontsize,              0x30066)
SYSCALL(gui_dc_get_text_align,            0x30067)
SYSCALL(gui_dc_display_string_in_rect,    0x3006b)
SYSCALL(gui_dc_scroll_string_in_rect,     0x3006c)
SYSCALL(gui_dc_set_scroll_string_in_rect, 0x3006d)
SYSCALL(gui_dc_show_picture,              0x30071)
SYSCALL(gui_dc_show_sub_picture,          0x30072)
SYSCALL(gui_dc_draw_bitmap_ext,           0x30073)
SYSCALL(gui_dc_draw_sub_bitmap_ext,       0x30074)
SYSCALL(gui_dc_draw_line,                 0x30079)
SYSCALL(gui_dc_get_char_dist_x,           0x3007c)
SYSCALL(gui_dc_get_string_dist_x,         0x3007d)
SYSCALL(gui_get_char_advance,             0x3007e)
SYSCALL(gui_set_display_mode,             0x3007f)
SYSCALL(gui_setting_config,               0x30080)
SYSCALL(gui_config_ttf_glyph_cache,       0x30083)
SYSCALL(gui_enable_memory_font,           0x30084)
SYSCALL(gui_convert_bidi,                 0x30087)
SYSCALL(gui_is_bidi_language,             0x30088)

SYSCALL(open,           0x60000)
SYSCALL(close,          0x60001)
SYSCALL(read,           0x60002)
SYSCALL(write,          0x60003)
SYSCALL(lseek,          0x60004)
SYSCALL(fcntl,          0x60005)
SYSCALL(creat,          0x60006)
SYSCALL(remove,         0x60007)
SYSCALL(rename,         0x60008)
SYSCALL(__broken_chdir, 0x60009) /* from libc_fs.so analysis, always returns EINVAL */
SYSCALL(__syscall_libc_fs_6000a, 0x6000a)
SYSCALL(fsync,          0x6000b) /* from libc_fs.so */
SYSCALL(__syscall_libc_fs_6000c, 0x6000c)
SYSCALL(ftruncate,      0x6000d)
SYSCALL(__broken_getcwd, 0x6000e) /* from libc_fs.so analysis, always returns EINVAL */
SYSCALL(mkdir,          0x6000f)
SYSCALL(rmdir,          0x60010)
SYSCALL(fstat,          0x60011)
SYSCALL(stat,           0x60012)
SYSCALL(utime,          0x60013)

SYSCALL(fopen,    0x60014)
SYSCALL(fclose,   0x60015)
SYSCALL(__syscall_libc_fs_60016, 0x60016)
SYSCALL(__syscall_libc_fs_60017, 0x60017)
SYSCALL(__syscall_libc_fs_60018, 0x60018)
SYSCALL(fread,    0x60019)
SYSCALL(fwrite,   0x6001a)
SYSCALL(__syscall_libc_fs_6001b, 0x6001b)
SYSCALL(__syscall_libc_fs_6001c, 0x6001c)
SYSCALL(__syscall_libc_fs_6001d, 0x6001d)
SYSCALL(fgets,    0x6001e)
SYSCALL(fileno,   0x6001f)
SYSCALL(fseek,    0x60020)
SYSCALL(freopen,  0x60021) /* from libc_fs.so analysis */
SYSCALL(ftell,    0x60022)
SYSCALL(rewind,   0x60023)
SYSCALL(setbuf,   0x60024)
SYSCALL(__syscall_libc_fs_60025, 0x60025)
SYSCALL(__syscall_libc_fs_60026, 0x60026)
SYSCALL(__syscall_libc_fs_60027, 0x60027)
SYSCALL(fsetpos,  0x60028)
SYSCALL(geterror, 0x60029)
SYSCALL(opendir,  0x6002a)
SYSCALL(readdir,  0x6002b)
SYSCALL(prevdir,  0x6002c) /* from libc_fs.so analysis */
SYSCALL(__syscall_libc_fs_6002d, 0x6002d)
SYSCALL(__syscall_libc_fs_6002e, 0x6002e)
SYSCALL(rewinddir, 0x6002f) /* from libc_fs.so analysis */
SYSCALL(closedir,  0x60030)

SYSCALL(__syscall_libc_fs_60031, 0x60031)
SYSCALL(__syscall_libc_fs_60032, 0x60032)
SYSCALL(statfs,           0x60033)
SYSCALL(__syscall_libc_fs_60034, 0x60034)
SYSCALL(__syscall_libc_fs_60035, 0x60035)
SYSCALL(__syscall_libc_fs_60036, 0x60036)
SYSCALL(__syscall_libc_fs_60037, 0x60037)
SYSCALL(__syscall_libc_fs_60038, 0x60038)
SYSCALL(__syscall_libc_fs_60039, 0x60039) /* called by 0x6001e */
SYSCALL(__syscall_libc_fs_6003a, 0x6003a)
SYSCALL(__syscall_libc_fs_6003b, 0x6003b) /* called by 0x6001c */
SYSCALL(__syscall_libc_fs_6003c, 0x6003c) /* called by 0x6001d */
SYSCALL(__syscall_libc_fs_6003d, 0x6003d) /* called by 0x60019 */
SYSCALL(__syscall_libc_fs_6003e, 0x6003e) /* called by 0x6001a */
SYSCALL(ioctl,            0x6003f)

SYSCALL(__syscall_libc_fs_60040, 0x60040) /* unimplemented */
SYSCALL(__syscall_libc_fs_60041, 0x60041) /* unimplemented */
SYSCALL(__syscall_libc_fs_60042, 0x60042)
SYSCALL(__libc_fs_mmap,   0x60043) /* from libc_fs.ko analysis */
SYSCALL(__libc_fs_munmap, 0x60044) /* from libc_fs.ko analysis */
SYSCALL(__syscall_libc_fs_60045, 0x60045)
SYSCALL(__libc_fs_puts,   0x60046) /* from libc_fs.ko analysis */

SYSCALL(fseeko, 0x60047)
SYSCALL(ftello, 0x60048)

SYSCALL(__kernel_get_pid,                0x70004)
SYSCALL(__kernel_release_pid,            0x70005)
SYSCALL(__kernel_get_process_struct,     0x70006)
SYSCALL(__kernel_get_tid,                0x70007) /* from libc_sys.ko debug string */
SYSCALL(__kernel_release_tid,            0x70008) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_70009,            0x70009)
SYSCALL(__syscall_libc_7000a,            0x7000a)
SYSCALL(__syscall_libc_7000b,            0x7000b)
SYSCALL(__syscall_libc_7000c,            0x7000c)
SYSCALL(__syscall_libc_7000d,            0x7000d)
SYSCALL(_kernel_change_thread_pid,       0x7000e)
SYSCALL(__syscall_libc_7000f,            0x7000f)
SYSCALL(execl,                           0x70010) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_70011,            0x70011)
SYSCALL(__syscall_libc_70012,            0x70012)
SYSCALL(execv,                           0x70013) /* from libc_sys.ko debug string */
SYSCALL(execvp,                          0x70014)
SYSCALL(kill,                            0x70015) /* from libc_sys.ko debug string */
SYSCALL(getpid,                          0x70016)
SYSCALL(__syscall_libc_70017,            0x70017)
SYSCALL(waitpid,                         0x70018)
SYSCALL(findenv,                         0x70019) /* from libc_sys.ko debug string */
SYSCALL(putenv,                          0x7001a)
SYSCALL(setenv,                          0x7001b) /* from libc_sys.ko debug string */
SYSCALL(unsetenv,                        0x7001c) /* from libc_sys.ko debug string */
SYSCALL(__kernel_set_envp,               0x7001d)
SYSCALL(__kernel_release_envp,           0x7001e) /* from libc_sys.ko debug string */
SYSCALL(_push_to_stack,                  0x70020) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_70021,            0x70021)
SYSCALL(__syscall_libc_70022,            0x70022)
SYSCALL(__syscall_libc_70023,            0x70023)
SYSCALL(__errno,                         0x70024) /* calls 0x70023 */
SYSCALL(__current_pid,                   0x70025)
SYSCALL(__thread_special,                0x70026) /* from libc_sys.ko debug string */
SYSCALL(__kernel_insert_sub_to_parent,   0x70027)
SYSCALL(__kernel_remove_sub_from_parent, 0x70028)
SYSCALL(_put_to_process_cleanup,         0x70029) /* from libc_sys.ko debug string */
SYSCALL(_get_out_process_cleanup,        0x7002a) /* from libc_sys.ko debug string */

SYSCALL(mq_open,         0x70030)
SYSCALL(mq_close,        0x70031)
SYSCALL(mq_unlink,       0x70032)
SYSCALL(mq_send,         0x70033)
SYSCALL(mq_timedsend,    0x70034) /* from libc_sys.ko debug string */
SYSCALL(mq_receive,      0x70035)
SYSCALL(mq_timedreceive, 0x70036)
SYSCALL(mq_setattr,      0x70037) /* from libc_sys.ko debug string */
SYSCALL(mq_getattr,      0x70038)

SYSCALL(pthread_cond_init,            0x70040)
SYSCALL(pthread_cond_destroy,         0x70041)
SYSCALL(pthread_cond_wait,            0x70042)
SYSCALL(pthread_cond_timedwait,       0x70043)
SYSCALL(pthread_cond_signal,          0x70044)
SYSCALL(pthread_cond_broadcast,       0x70045) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_70046,         0x70046)
SYSCALL(pthread_condattr_destroy,     0x70047) /* from libc_sys.ko debug string */
SYSCALL(pthread_condattr_getpshared,  0x70048) /* from libc_sys.ko debug string */
SYSCALL(pthread_condattr_setpshared,  0x70049) /* from libc_sys.ko debug string */
SYSCALL(pthread_mutex_init,           0x70050)
SYSCALL(pthread_mutex_destroy,        0x70051)
SYSCALL(pthread_mutex_lock,           0x70052)
SYSCALL(pthread_mutex_trylock,        0x70053) /* from libc_sys.ko debug string */
SYSCALL(pthread_mutex_unlock,         0x70054)
SYSCALL(pthread_mutexattr_init,       0x70055)
SYSCALL(pthread_mutexattr_destroy,    0x70056)
SYSCALL(pthread_mutexattr_setpshared, 0x70057)
SYSCALL(pthread_mutexattr_getpshared, 0x70058) /* from libc_sys.ko debug string */
SYSCALL(pthread_mutexattr_settype,    0x70059)
SYSCALL(pthread_mutexattr_gettype,    0x7005a) /* from libc_sys.ko debug string */
SYSCALL(pthread_getschedparam,        0x7005d)
SYSCALL(pthread_setschedparam,        0x7005e)
SYSCALL(pthread_setschedprio,         0x7005f)
SYSCALL(pthread_create,               0x70060)
SYSCALL(pthread_exit,                 0x70061)
SYSCALL(__syscall_libc_70062,         0x70062)
SYSCALL(pthread_self,                 0x70063)
SYSCALL(pthread_join,                 0x70064)
SYSCALL(pthread_detach,               0x70065)
SYSCALL(__syscall_libc_70066,         0x70066)
SYSCALL(__syscall_libc_70067,         0x70067)
SYSCALL(pthread_key_create,           0x70068) /* from libc_sys.ko debug string */
SYSCALL(pthread_key_delete,           0x70069) /* from libc_sys.ko debug string */
SYSCALL(pthread_getspecific,          0x7006a) /* from libc_sys.ko debug string */
SYSCALL(pthread_setspecific,          0x7006b) /* from libc_sys.ko debug string */
SYSCALL(pthread_cleanup_push,         0x7006c) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_7006d,         0x7006d)
SYSCALL(__syscall_libc_7006e,         0x7006e)
SYSCALL(__syscall_libc_7006f,         0x7006f)
SYSCALL(pthread_attr_init,            0x70070)
SYSCALL(pthread_attr_destroy,         0x70071)
SYSCALL(pthread_attr_setinheritsched, 0x70072)
SYSCALL(pthread_attr_getinheritsched, 0x70073) /* from libc_sys.ko debug string */
SYSCALL(pthread_attr_setdetachstate,  0x70074)
SYSCALL(pthread_attr_getdetachstate,  0x70075) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_70076,         0x70076)
SYSCALL(__syscall_libc_70077,         0x70077)
SYSCALL(pthread_attr_setscope,        0x70078)
SYSCALL(pthread_attr_getscope,        0x70079) /* from libc_sys.ko debug string */
SYSCALL(pthread_attr_setschedpolicy,  0x7007a)
SYSCALL(pthread_attr_getschedpolicy,  0x7007b) /* from libc_sys.ko debug string */
SYSCALL(pthread_attr_setschedparam,   0x7007c)
SYSCALL(pthread_attr_getschedparam,   0x7007d)
SYSCALL(pthread_attr_setstacksize,    0x7007e) /* from libc_sys.ko debug string */
SYSCALL(pthread_attr_getstacksize,    0x7007f) /* from libc_sys.ko debug string */
SYSCALL(pthread_attr_setstack,        0x70080) /* from libc_sys.ko debug string */
SYSCALL(pthread_attr_getstack,        0x70081) /* from libc_sys.ko debug string */

SYSCALL(exit,        0x70082)
SYSCALL(sysapi_exit, 0x70082)	/* alias */

SYSCALL(sleep,         0x70083)
SYSCALL(usleep,        0x70084)
SYSCALL(clock_gettime, 0x70085)
SYSCALL(__syscall_libc_70086, 0x70086) /* seems to be unimplemented */
SYSCALL(nanosleep,     0x70087)
SYSCALL(__syscall_libc_70088, 0x70088) /* returns some sort of formatted time string */
SYSCALL(atexit,        0x70089)

SYSCALL(sched_get_priority_min, 0x70090)
SYSCALL(sched_get_priority_max, 0x70091)

SYSCALL(__syscall_libc_70092, 0x70092)

SYSCALL(mmap,       0x70095)
SYSCALL(munmap,     0x70096) /* from libc_sys.ko debug string */
SYSCALL(__syscall_libc_70097, 0x70097) /* calls 0x10064 */
SYSCALL(shm_open,   0x70098)
SYSCALL(shm_unlink, 0x70099)

SYSCALL(sem_open,      0x700a0)
SYSCALL(sem_close,     0x700a1)
SYSCALL(sem_unlink,    0x700a2)
SYSCALL(sem_init,      0x700a3)
SYSCALL(sem_destroy,   0x700a4)
SYSCALL(sem_getvalue,  0x700a5) /* from libc_sys.ko debug string */
SYSCALL(sem_wait,      0x700a6)
SYSCALL(sem_trywait,   0x700a7) /* from libc_sys.ko debug string */
SYSCALL(sem_timedwait, 0x700a8)
SYSCALL(sem_post,      0x700a9)

SYSCALL(__syscall_libc_700af, 0x700af) /* unimplemented */
SYSCALL(__syscall_libc_700b0, 0x700b0)

/* from camext.so */
SYSCALL(mmm_cam_open,  0x80000)
SYSCALL(mmm_cam_cmd,   0x80001)
SYSCALL(mmm_cam_close, 0x80002)

/* from music_eg.so */
SYSCALL(mmm_mp_open,  0x80000)
SYSCALL(mmm_mp_cmd,   0x80001)
SYSCALL(mmm_mp_close, 0x80002)

/* from videoext.so */
SYSCALL(mmm_vp_open,  0x80000)
SYSCALL(mmm_vp_cmd,   0x80001)
SYSCALL(mmm_vp_close, 0x80002)

SYSCALL(sqlite3_open,       0x90000)
SYSCALL(sqlite3_close,      0x90001)
SYSCALL(sqlite3_exec,       0x90002)
SYSCALL(sqlite3_prepare,    0x90003)
SYSCALL(sqlite3_bind_int,   0x90009)
SYSCALL(sqlite3_step,       0x90013)
SYSCALL(sqlite3_finalize,   0x90014)
SYSCALL(sqlite3_reset,      0x90015)
SYSCALL(sqlite3_errmsg,     0x9001f)
SYSCALL(sqlite3_column_blob, 0x90026)
SYSCALL(sqlite3_column_bytes, 0x90027)
SYSCALL(sqlite3_column_init,  0x90029)
SYSCALL(sqlite3_column_text,  0x9002a)
SYSCALL(sqlite3_value_int,    0x90032)
SYSCALL(sqlite3_value_text,   0x90033)
SYSCALL(sqlite3_result_blob,  0x90039)
SYSCALL(sqlite3_result_int,   0x9003b)
SYSCALL(sqlite3_result_text,  0x9003d)
SYSCALL(sqlite3_soft_heap_limit, 0x9004d)
SYSCALL(sqlite3_last_insert_rowid, 0x90053)
SYSCALL(sqlite3_create_function,   0x90054)

SYSCALL(fsel_open,           0xa0000)
SYSCALL(fsel_close,          0xa0001)
SYSCALL(fsel_setworkdir,     0xa0002)
SYSCALL(fsel_getworkdir,     0xa0003)
SYSCALL(fsel_setfilter,      0xa0004)
SYSCALL(fsel_getfilenum,     0xa0005)
SYSCALL(fsel_listfile,       0xa0006)
SYSCALL(fsel_listdir,        0xa0007)
SYSCALL(fsel_cd,             0xa0008)
SYSCALL(fsel_sortstyle,      0xa0009)
SYSCALL(fsel_getidbyname,    0xa000a)
SYSCALL(fsel_update,         0xa000b)
SYSCALL(fsel_set_query,      0xa000c)
SYSCALL(fsel_subdir_setting, 0xa000d)
SYSCALL(fsel_getfullpath,    0xa000e)
SYSCALL(fsel_next_fileinfo,  0xa000f)

SYSCALL(plist_init,                    0xb0000)
SYSCALL(plist_quit,                    0xb0001)
SYSCALL(plist_open,                    0xb0002)
SYSCALL(plist_close,                   0xb0003)
SYSCALL(plist_clear,                   0xb0004)
SYSCALL(plist_delete_by_handle,        0xb0005)
SYSCALL(plist_delete_by_type,          0xb0006)
SYSCALL(plist_sync_mtp,                0xb0007)
SYSCALL(plist_get_listnum_by_type,     0xb0008)
SYSCALL(plist_get_listname_by_type,    0xb0009)
SYSCALL(plist_verify_list,             0xb000b)
SYSCALL(plist_add_query,               0xb000d)
SYSCALL(plist_get_items_to_mallocbuf,  0xb000f)
SYSCALL(plist_free_buf,                0xb0010)
SYSCALL(plist_get_item_num,            0xb0011)
SYSCALL(plist_filter_del_item,         0xb0012)
SYSCALL(plist_add_dirlist,             0xb0014)
SYSCALL(plist_add_item,                0xb0015)
SYSCALL(plist_transfer_items,          0xb0016)
SYSCALL(plist_del_items,               0xb0017)
SYSCALL(plist_modify_item,             0xb0018)
SYSCALL(plist_name_to_index,           0xb0019)
SYSCALL(plist_set_filetype_ext,        0xb001d)
SYSCALL(plist_init_detail_info_struct, 0xb001e)
SYSCALL(plist_set_rootdir,             0xb0020)
SYSCALL(plist_generate_medialib,       0xb0021)
SYSCALL(plist_table_exist,             0xb0022)
SYSCALL(plist_delete_by_tblname,       0xb0024)
SYSCALL(plist_get_item_num_filter,     0xb0026)
SYSCALL(plist_get_items_to_mallocbuf_filter, 0xb0027)
SYSCALL(plist_erase_invalid_data,            0xb0028)
SYSCALL(plist_get_ID3_by_name,         0xb0029)
SYSCALL(plist_interrupt,               0xb002a)
SYSCALL(plist_add_to_list,             0xb002b)
SYSCALL(plist_table_not_empty,         0xb002c)
SYSCALL(plist_get_ID3_by_index_swift,  0xb002d)
SYSCALL(plist_verify_list_v2,          0xb002e)
SYSCALL(plist_transfer_items_filter,   0xb002f)

SYSCALL(mlang_mbcs_to_unicode, 0xc0001)
SYSCALL(mlang_unicode_to_utf8, 0xc0002)
SYSCALL(mlang_utf8_to_unicode, 0xc0003)
SYSCALL(mlang_mbcs_to_utf8,    0xc0004)

SYSCALL(get_picregion_frame, 0xd0006)

SYSCALL(get_config,       0x110000)
SYSCALL(set_config,       0x110001)
SYSCALL(rest_config,      0x110002)
SYSCALL(reset_all_config, 0x110003)
SYSCALL(clear_hds,        0x110004)
SYSCALL(__syscall_110005, 0x110005)
SYSCALL(sync_config,      0x110006)
SYSCALL(nandflash_update, 0x110007)

SYSCALL(is_app_exist,                  0x120002)
SYSCALL(get_app_name,                  0x120005)
SYSCALL(app_running_list_get_app_info, 0x120006)
SYSCALL(app_running_list_set_app_info, 0x120008)
SYSCALL(app_running_list_get_list,     0x12000a)

SYSCALL(set_timer,             0x12000f)
SYSCALL(set_single_shot_timer, 0x120010)
SYSCALL(modify_timer,          0x120011)
SYSCALL(stop_timer,            0x120012)
SYSCALL(restart_timer,         0x120013)
SYSCALL(kill_timer,            0x120014)
SYSCALL(kill_timers,           0x120015)

SYSCALL(applib_register_app,   0x120034)
SYSCALL(applib_unregister_app, 0x120035)
SYSCALL(applib_init,           0x120036)
SYSCALL(applib_quit,           0x120037)

SYSCALL(get_msg,                   0x120038)
SYSCALL(send_sync_msg,             0x120039)
SYSCALL(reply_sync_msg,            0x12003a)
SYSCALL(send_async_msg,            0x12003b)
SYSCALL(broadcast_msg,             0x12003c)
SYSCALL(dispatch_msg,              0x12003d)
SYSCALL(register_sys_dispatcher,   0x12003e)
SYSCALL(unregister_sys_dispatcher, 0x12003f)
SYSCALL(exit_msg_loop,             0x120040)
SYSCALL(clear_sys_msg_queue,       0x120041)

SYSCALL(enter_foreground_mode, 0x120044)

SYSCALL(check_soft_watchdogs, 0x120046)

SYSCALL(sys_get_hotplugin_dev_info,    0x120071)
SYSCALL(sys_get_cur_language_id,       0x120076)
SYSCALL(sys_get_default_font_file,     0x12007b)
SYSCALL(sys_check_media_dir,           0x12007c)
SYSCALL(sys_is_screensaver_forbidden,  0x12007f)
SYSCALL(sus_is_auto_standby_forbidden, 0x120082)
SYSCALL(sys_get_rtc_date_time,   0x120086)
SYSCALL(int_sqrt,                0x12008d)
SYSCALL(sys_pm_set_clk_domain,   0x12008f)
SYSCALL(sys_pm_clear_clk_domain, 0x120090)

SYSCALL(basename, 0x120092)

SYSCALL(sys_get_main_disk,     0x12009c)
SYSCALL(sys_set_main_disk,     0x12009d)
SYSCALL(sys_get_main_disk_dir, 0x12009e)

SYSCALL(sys_enable_sys_evt_detect,          0x1200a1)
SYSCALL(filter_msg,                         0x1200a2)
SYSCALL(filter_all_msg,                     0x1200a4)
SYSCALL(unfilter_all_msg,                   0x1200a5)
SYSCALL(sys_get_media_dir,                  0x1200a6)
SYSCALL(create_global_msg_queue,            0x1200a7)
SYSCALL(delete_global_msg_queue,            0x1200a8)
SYSCALL(send_async_msg_to_global_mq,        0x1200ad)
SYSCALL(sys_is_forced_shutdown_forbidden,   0x1200af)
SYSCALL(sys_is_pm_power_costdown_forbidden, 0x1200b5)


SYSCALL(mmm_ai_open,  0x150000)
SYSCALL(mmm_ai_cmd,   0x150001)
SYSCALL(mmm_ai_data,  0x150002)
SYSCALL(mmm_ai_close, 0x150003)
SYSCALL(mmm_ao_open,  0x150004)
SYSCALL(mmm_ao_cmd,   0x150005)
SYSCALL(mmm_ao_data,  0x150006)
SYSCALL(mmm_ao_close, 0x150007)

SYSCALL(actal_malloc,         0x160000)
SYSCALL(actal_free,           0x160001)
SYSCALL(actal_malloc_dma,     0x160002)
SYSCALL(actal_free_dma,       0x160003)
SYSCALL(actal_malloc_wt,      0x160004)
SYSCALL(actal_free_wt,        0x160005)
SYSCALL(actal_malloc_uncache, 0x160006)
SYSCALL(actal_free_uncache,   0x160007)
SYSCALL(actal_printf,         0x160009)
SYSCALL(actal_get_ts,         0x16000a)
SYSCALL(actal_info,           0x16000c)
SYSCALL(actal_memcpy,         0x16000d)
SYSCALL(actal_memset,         0x16000e)
SYSCALL(actal_sleep_ms,       0x160010)
SYSCALL(actal_error,          0x160011)

SYSCALL(multip_get_pinowner,     0x1a0002)
SYSCALL(multip_release_pinowner, 0x1a0003)
SYSCALL(enable_module_clk,       0x1a0004)
SYSCALL(disable_module_clk,      0x1a0005)
SYSCALL(get_gpio,                0x1a0009)

#include "actsemi.h"

int do_gettimeofday(struct timeval *tv);
int gettimeofday(struct timeval *tv, void *tz)
{
  (void)tz;
  return do_gettimeofday(tv);
}
