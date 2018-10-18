#!/usr/bin/env python3
# _*_coding:utf-8_*_  
# 目的：掌握获取Cookie的使用和获取
#       掌握抓包解析headers方法

#from urllib import request
import requests
from http import cookiejar
from bs4 import BeautifulSoup
class book:
    def __init__(self):
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0',
            'Accept-Language' : 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
            'Accept-Encoding' : 'gzip, deflate,br'
        }
        self.book = {
            'book_id' : '1_1',          #小说id
            'book_name':'',             #小说名
            'book_info' : '',           #小说简介
            'section_id' : '2',         #小说章节id
            'section_name':'',          #小说章节名
            'section_txt':'',           #小说章节正文
        }
        self.url_base = 'https://www.biquge5.com/'  #小说网址

    # log
    def save_log(self):
        pass
    # 获取小说url
    def get_book_url(self):
        pass

    # 获取小说章节网址
    def get_book_section_url(self):
        pass

    # 小说章节解析
    def get_parser(self):
        req_url = self.url_base + str(self.book['book_id']) + '/' + str(self.book['section_id']) +'.html'
        r = requests.get(req_url, params = self.headers)
        soup = BeautifulSoup(r.text, "html.parser")

        # 获取章节名称
        self.book['section_name'] = soup.select('#wrapper .content_read .box_con .bookname h1')[0].text
        print(self.book['section_name'])
        # 获取章节文本
        self.book['section_txt'] = soup.select('#wrapper .content_read .box_con #content')[0].text
        print(self.book['section_txt'])
        # 按照指定格式替换章节内容，运用正则表达式

    # 整篇小说
    def get_book(self):
        pass

'''
# 按照指定格式替换章节内容，运用正则表达式
'''
if __name__ == '__main__':
    book =book()
    book.get_parser()
