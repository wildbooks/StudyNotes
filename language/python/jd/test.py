#!/usr/bin/env python3
# _*_coding:utf-8_*_  
# 目的：
#       掌握静态网页登录方法(request方法/session方法)
#       掌握正则表达式提取消息的能力
# test: OK
#
# https://www.cnblogs.com/chenxiaohan/p/7654667.html
#
from selenium import webdriver

ddriver = webdriver.Firefox()
ddriver.get('http://www.baidu.com')
ddriver.find_element_by_id('kw').send_keys(u'MoonBreeze的博客')
ddriver.find_element_by_id('su').click()
