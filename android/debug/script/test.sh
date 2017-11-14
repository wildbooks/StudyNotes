#!/bin/bash
ls liqiu > /tmp/error 2>&1 #使用 " 2>&1" 把标准错误 stderr 重定向到标准输出 stdout ；
echo $? #捕获上一条命令的输出 (if 0 正常 else 错误)
ls -l > /tmp/log
echo $?
