# 常用库
1. requests 做请求的时候用到。
  http://cn.python-requests.org/zh_CN/latest/
  requests.get("url")
2. selenium 自动化真正的浏览器（Chrome浏览器，火狐浏览器，Opera浏览器，IE浏览器）。
3. lxml 解析网页
4. beautiful soup 取代枯燥易错的正则表达式，简化数据匹配，快速清洗
5. pyquery 网页解析库 说是比beautiful 好用，语法和jquery非常像。
6. pymysql 存储库。操作mysql数据的。
7. pymongo 操作MongoDB 数据库。
8. redis 非关系型数据库。
9. jupyter在线记事本。
Requests库：主要是简化请求工作
Beautiful Soup：取代枯燥易错的正则表达式，简化数据匹配，快速清洗
Xpath语法lxml：主要了解文档结构，知己知彼，好下手
PhantomJS：处理网页中的动态js请求，模拟浏览器完成js的渲染，等到异步情节，保证文档结构数据的完整性，所见即所得（这个我们后面也会用到）
Selenium：模拟浏览事件，支持多步连续请求，减少人工手动触发［登录表单填写，触发表单发送，调整登录成功页等］
pyQuery：顾名思义，用python语言复制一版jquery
pandas: 表格处理库
mysql.connector： python操作mysql

---------------------

ChromDriver
本文来自 vivianking68 的CSDN 博客 ，全文地址请点击：https://blog.csdn.net/vivian_king/article/details/79493897?utm_source=copy 
二 什么是urllib
  urllib.request 请求模块  　　模拟浏览器
  urllib.error 异常处理模块
  urllib.parse url解析模块  　　工具模块，如：拆分、合并
  urllib.robotparser robots.txt    解析模块　
