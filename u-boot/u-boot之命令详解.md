- 信息命令

  - bdinfo - 打印板子信息结构
  - coninfo - 打印控制台设备和信息
  - flinfo - 打印flash闪存信息
  - iminfo - 打印应用程序映像的标题信息
  - imls - 列出在Flash中找到的所有图像
  - 帮助 - 打印在线帮助

- 记忆指令

  - base  - 打印或设置地址偏移量
  - crc32 - 校验和计算
  - cmp - 内存比较
  - cp - 内存副本
  - md - 内存显示
  - mm - 内存修改（自动递增）
  - mtest - 简单的RAM测试
  - MW - 内存写入（填充）
  - nm - 内存修改（常量地址）
  - loop - 地址范围上的无限循环

- 闪存命令

  - cp-内存复制（程序闪存）
  - flinfo-打印闪存信息
  - erase - 擦除闪存
  - protect - 启用或禁用FLASH写保护

- 执行控制命令

  - autoscr - 从内存运行脚本
  - bootm - 从内存启动应用程序映像
  - bootelf - 从内存中的ELF映像启动
  - bootvx - 从ELF映像启动vxWorks
  - go - 在地址“ addr”处启动应用程序

- 网络命令

  - bootp-使用BOOTP / TFTP协议通过网络引导映像
  - cdp - 执行思科发现协议网络配置
  - dhcp - 调用DHCP客户端以获得IP /启动参数
  - loadb - 通过串行线加载二进制文件（kermit模式）
  - loads - 通过串行线加载S记录文件
  - nfs - 使用NFS协议通过网络引导映像
  - ping - 将ICMP ECHO_REQUEST发送到网络主机
  - rarpboot - 使用RARP / TFTP协议通过网络引导映像
  - tftpboot - 使用TFTP协议通过网络引导映像

- 环境变量命令

  - printenv - 打印环境变量
  - saveenv - 将环境变量保存到持久性存储中
  - askenv - 从标准输入中获取环境变量
  - setenv - 设置环境变量
  - run - 在环境变量中运行命令
  - bootd - 引导默认值，即运行'bootcmd'

- 文件系统支持（FAT，cramfs，JFFS2，Reiser）

  - chpart - 更改活动分区
  - fsinfo - 打印有关文件系统的信息
  - fsload - 从文件系统映像加载二进制文件
  - ls - 列出目录中的文件（默认/）
  - fatinfo - 打印有关文件系统的信息
  - fatls - 列出目录中的文件（默认/）
  - fatload - 从DOS文件系统加载二进制文件
  - nand - NAND闪存子系统
  - reiserls - 列出目录中的文件（默认/）
  - reiserload - 从Reiser文件系统加载二进制文件

- 特殊命令

  - i2c - I2C子系统
  - doc - 片上磁盘子系统
  - dtt - 数字温度计和恒温器
  - eeprom - EEPROM子系统
  - fpga - FPGA子系统
  - ide - IDE子系统
  - kgdb - 进入gdb远程调试模式
  - diskboot - 从IDE设备引导
  - icache -启用或禁用指令缓存
  - dcache-启用或禁用数据缓存
  - diag - 执行板诊断（**POST**代码）
  - log - 操作日志缓冲区
  - pci - 列出和访问PCI配置空间
  - regdump - 注册转储命令
  - USB - USB子系统
  - sspi - SPI实用程序命令

- 杂项命令

  - bmp-处理BMP图像数据
  - date -获取/设置/重置日期和时间
  - echo-将args回显到控制台
  - exit -退出脚本
  - kbd-读取键盘状态
  - in-从IO端口读取数据
  - out-将数据写入IO端口
  - 重reset-执行CPU的重置
  - sleep-延迟执行一段时间
  - test -最小测试，如/ bin / sh
  - version -打印监视器版本
  - wd-检查并设置看门狗
  - ？-'帮助'的别名

  # log

  ```bash
  使用系统内存的保留区作为日志缓冲区；可以在Linux中由syslogd重新使用；内容将在重置/热启动后幸免
  log info - show pointer details
  log log reset - 清除内容
  log log show - 显示内容
  log log append - 附加到日志缓冲区
  setenv stdout log - 将标准输出重定向到日志缓冲区
  ```

  