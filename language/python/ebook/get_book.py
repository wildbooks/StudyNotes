#!/usr/bin/env python3
# _*_coding:utf-8_*_
# 目的：掌握requests用法
#      掌握BeautifulSoup用法
#      掌握json用法
#      掌握MySQL用法
#      掌握生成器yield用法
#      掌握日志系统
#      掌握正则表达式re
#      掌握列表list
# 功能：
#      爬取所有网站
# 方法：
#      先构造小说首页
#      再爬取小说章节网址
#      再爬取小说章节
#      存储小说
#      可视化

import re
import json
import requests
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
        self.log = 'next text',           #日志系统初始化
        self.sql = 'next text',           #数据库初始化
        self.url_base = 'https://www.biquge5.com/'  #小说网址
        '''
        booksdata{
            book1{
                book_name:书名
                作者
                book_leixin:书类型
                book_info:小说类型
                book{
                    章1节
                    章2节
                    章3节
                    ...
                }
            }
            book2
            book3
            ...
        }
        '''

    # log
    def save_log(self):
        pass
    # 获取小说url
    def get_book_url(self):
        pass

    # 获取小说章节网址
    def get_book_section_url(self):
        pass
    #
    # 1. 获取网页
    # 抓取网页
    def get_pager(self):
        pass

    # 2. 一级网页解析:整篇小说目录
    def get_ebook_parser(self):
        req_url='https://www.biquge5.com/20_20234/'
        r = requests.get(req_url, params = self.headers)

        soup = BeautifulSoup(r.text, "html.parser")
        urllist=soup.findAll('a', href=re.compile('https://www.biquge5.com/20_20234/'))
        book={}
        for list in urllist:
            book['name'] = list.text  #提取小说章节名
            book['url'] = list['href'].replace('\n', '') #提取小说章集网址
            if len(book['url']) <50 and len(book['url'])>35:
                yield book

    # 3. 二级网页解析:获取小说章节
    def page_parser(self, req_url):
        r = requests.get(req_url, params = self.headers)
        soup = BeautifulSoup(r.text, "html.parser")
        urllist=soup.findAll('div', id='content')
        #print(urllist[0].text)
        return re.sub( '\s+', '\r\n\t', urllist[0].text).strip('\r\n')
        #print(urllist[0].text)
        #book={}

    # 4.1 数据存储:保存到json
    def save_json(self, text):
        s=json.dumps(text, indent=4, ensure_ascii=False)
        with open('book.json','a+',  encoding ='utf-8') as f:
            f.write(s)

    # 4.2 数据存储:保存到数据库
    def save_sql(self):
        pass
        '''
    def page_parser(self):
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
        '''

    # 4.2 从数据库中提取小说
    def get_book_from_sql(self):
        pass

    # 4.2 从json中提取小说
    def get_book_from_json(self):
        pass

'''
# 按照指定格式替换章节内容，运用正则表达式
'''
if __name__ == '__main__':
    book =book()
    for i in book.get_ebook_parser():
        print('get : %s' %(i)); #保存url到json
        text= book.page_parser(i['url']) #保存json
        book.save_json(text)
