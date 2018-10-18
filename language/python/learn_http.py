#!/usr/bin/env python3
# _*_coding:utf-8_*_  

from urllib import request

url = "http://www.douban.com"
# 第二种方法:使用request类，伪装数据再请求
headers={
    'User-Agent': r'Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0',
    'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2'
}
req = request.Request(url, headers=headers)

# User-Agent: Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0
# Cookie: BAIDUID=9CA69C633EDED663DD4B2D…MniBnr9-pnEaMt0HPonHjDKD5bL3e
# Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2

response = request.urlopen(req)
print("获取状态码:%d, 200表示成功" %response.getcode())
print("获取网页内容的长度%d" %len(response.read()))
print("获取网页内容的长度%s" %response.info())
