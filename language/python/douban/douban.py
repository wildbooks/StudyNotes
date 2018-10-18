#!/usr/bin/env python3
# _*_coding:utf-8_*_  
# 目的：
#       掌握静态网页登录方法(request方法/session方法)
#       掌握正则表达式提取消息的能力
#
#       另外一种：urllib方法 https://blog.csdn.net/philos3/article/details/76762639
#
# https://www.cnblogs.com/chenxiaohan/p/7654667.html
#
import urllib
import requests
from http import cookiejar
from lxml import etree

class doupan:

    def __init__(self, username, password):
        print("__init__")
        # 初始化登录地址、账号和密码
        self.loginUrl = "https://accounts.douban.com/login"
        self.username = username
        self.password = password
        self.cookies = cookiejar.cookieJar
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0',
            'Accept-Language' : 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
            'Accept-Encoding' : 'gzip, deflate,br'
        }
        self.session = requests.Session()

    def login(self, url):
        pass

    # 获取验证码
    def get_captcha_info(self):
        print("_get_captcha_info")
        """获取验证码图片和验证码id"""
        captcha_info = dict()
        resp = requests.get(url, headers=req_headers)
        if resp.status_code == requests.codes.ok:
            html = resp.text
            ele_html = etree.HTML(html)

            #验证码图片连接
            captcha_link = ele_html.xpath('//img[@id="captcha_image"]/@src')
            print("captcha_link:%s" %captcha_link)
            if len(captcha_link):
                #urllib.request.urlretrieve(captcha_link,"./captcha.png")
                captcha_solution=input('验证码:()'.format(captcha_link[0]))
                print("captcha_solution=%s" %captcha_solution)
                captcha_info['captcha-solution'] = captcha_solution

            #验证码id
            captcha_id = ele_html.xpath('//input[@name="captcha-id"]/@value')
            if len(captcha_id):
                captcha_info['captcha-id']=captcha_id[0]
        return captcha_info

    req_data = {
        'source':"index_hav",
        'redir':'https://www.douban.com',
        "form_email":"www762268@foxmail.com",
        "form_password":"ch3ch2cooh",
        "login":"登录",
        "remember":"on"
    }

    # 添加验证码信息到请求体中
    captcha_info = _get_captcha_info()
    if captcha_info:
        req_data.update(captcha_info)

    # 使用Session post数据
    session = requests.Session()
    resp = session.post(url, data=req_data, headers=req_headers)
    return session

def get_url(self, url ,session):
    pass
def get_page(self ,session):
    pass

if __name__ == '__main__':
    login_url = 'https://accounts.douban.com/login'
    session = login(login_url)

    myinfo_url = 'https://www.douban.com/people/143827096'
    get_myinfo(myinfo_url, session)
