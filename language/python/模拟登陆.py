#!/usr/bin/env python3
# _*_coding:utf-8_*_  
# 目的：掌握模拟登陆的几种方法
#       直接使用已知的cooie访问
#       模拟登录后再携带得到的cookie访问
#       模拟登录后用session保存登录状态
#       使用无头浏览器访问
# https://www.cnblogs.com/chenxiaohan/p/7654667.html
#

from urllib import request
from http import cookiejar

## 方法一：获取Cookie保存到变量
# 声明一个CookieJar对象实例来保存cookie
cookie = cookiejar.CookieJar()
# 利用urllib库的HTTPCookieProcessor对象来创建cookie处理器
handler = request.HTTPCookieProcessor(cookie)
# 通过handler来构建opener
opener = request.build_opener(handler)
#此处的open方法同urllib的urlopen方法，也可以传入request

#url = "http://www.douban.com"
url = "http://www.baidu.com"
response = opener.open(url)
for item in cookie:
    print("Name = "+item.name)
    print("Value = "+item.value)


## 方法二：获取Cookie保存到文件
#设置保存cookie的文件,同级目录下的cookie.txt
filename = "cookie.txt"
#声明一个MozillaCookieJar对象实例来保存cookie，之后写入文件
cookie = cookiejar.MozillaCookieJar(filename)
# 利用urllib库的HTTPCookieProcessor对象来创建cookie处理器
handler = request.HTTPCookieProcessor(cookie)
# 通过handler来构建opener
opener = request.build_opener(handler)
#此处的open方法同urllib的urlopen方法，也可以传入request
response = opener.open(url)
#保存cookie到文件
cookie.save(ignore_discard=True, ignore_expires=True)
# ignore_discard的意思是即使cookies将被丢弃也将它保存下来
# ignore_expires的意思是如果在该文件中cookies已经存在，则覆盖原文件写入


## 方法三：从文件中获取Cookie并访问
# 创建MozillaCookieJar实例对象
cookie = cookiejar.MozillaCookieJar()
# 从文件中读取cookie内容到变量
cookie.load(filename, ignore_discard=True, ignore_expires=True)
# 创建请求的request
req = request.Request(url)
# 利用urllib库的HTTPCookieProcessor对象来创建cookie处理器
handler = request.HTTPCookieProcessor(cookie)
# 通过handler来构建opener
opener = request.build_opener(handler)
response = opener.open(req)
print(response.read())
