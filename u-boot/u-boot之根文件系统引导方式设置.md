# UUID方式引导

# label方式引导

## label相关操作



```bash 
# label方式引导根文件系统
setenv bootargs root=LABEL=ROOTFS rootflags=data=writeback rw console=ttyAML0,115200n8 console=tty0 no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0
```





https://www.rootop.org/pages/4378.html