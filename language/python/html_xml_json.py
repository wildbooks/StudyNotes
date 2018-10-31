#! /usr/bin/env python3
# -*- coding:utf-8 -*-

# 掌握html/xml/json解析
# https://www.2cto.com/kf/201608/540905.html
#
# 1，lxml.html的方式进行解析
# 2，使用BeautifulSoup，不多说了，推荐一篇讲解非常好的文章
# 3，使用SGMLParser，主要是通过start、end tag的方式进行了，解析工程比较明朗，但是有点麻烦，而且该案例的场景不太适合该方法，（哈哈）
# 4, HTMLParaer，与3原理相识，就是调用的方法不太一样，基本上可以公用，
# 5, xpath解析html
# 6, re正则匹配
# 7, PyQuery

# xml <-> json
import requests
from BeautifulSoup import bs4
import json

class Xml2Json:
    pass
