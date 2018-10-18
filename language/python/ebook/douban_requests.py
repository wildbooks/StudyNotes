#!/usr/bin/env python3
# _*_coding:utf-8_*_  
# 目的：
#       掌握静态网页登录方法(request方法/session方法)
#       掌握正则表达式提取消息的能力
# test: OK
#
# https://www.cnblogs.com/chenxiaohan/p/7654667.html
#
import requests
#from http import cookiejar
from lxml import etree

class douban:

    def __init__(self, username, password):
        print("__init__")
        # 初始化登录地址、账号和密码
        self.loginUrl = "https://accounts.douban.com/login"
        self.username = username
        self.password = password
        #self.cookies = cookiejar.cookieJar
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:62.0) Gecko/20100101 Firefox/62.0',
            'Accept-Language' : 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
            'Accept-Encoding' : 'gzip, deflate,br'
        }

    # 获取验证码
    def get_captcha_info(self):
        print("_get_captcha_info")
        """获取验证码图片和验证码id"""
        captcha_info = dict()
        resp = requests.get(self.loginUrl, headers=self.headers)
        if resp.status_code == requests.codes.ok:
            html = resp.text
            ele_html = etree.HTML(html)

            #1.1获取验证码图片连接
            captcha_link = ele_html.xpath('//img[@id="captcha_image"]/@src')
            print("captcha_link:%s" %captcha_link)#下载该img文件

            # 1.2解析连接图片中的验证码
            if len(captcha_link):
                captcha_solution=input('验证码:()'.format(captcha_link[0]))
                print("captcha_solution=%s" %captcha_solution)
                captcha_info['captcha-solution'] = captcha_solution

            print("fdaf")
            #2获取验证码id
            captcha_id = ele_html.xpath('//input[@name="captcha-id"]/@value')
            if len(captcha_id):
                captcha_info['captcha-id']=captcha_id[0]
                print('captcha-id:%d' %dcaptcha_id[0])
        return captcha_info

    def login(self, url):
        """登录"""
        """
            source:index_nav
            redir:https://www.douban.com    #可有可无
            form_password:wwww
            form_password:gggg
            captcha-solution:gggg
            captcha-id:wwfasfasfaasf
            login:登录
        """
        print("登录")
        # 1. 构建session实例
        session = requests.Session()

        req_data = {
        'source' : 'index_hav',
        'redir' : 'https://www.douban.com',
        "form_email": self.username,
        "form_password" : self.password,
        "login":"登录",
        "remember":"on"
        }
        # 2. 获取验证码
        captcha_info = self.get_captcha_info()

        # 更新post数据
        if captcha_info:
            req_data.update(captcha_info)

        # 3. 请求post的地址
        resp = session.post(url, data=req_data, headers=self.headers)
        # 
        print("login")
        return session

    def get_url(self, url ,session):
        pass
    def get_page(self, url ,session):
        print("get_myinfo")
        """获取个人主页信息"""
        resp = session.get(url)
        if resp.status_code == requests.codes.ok:
            html = resp.text
            print(html)

if __name__ == '__main__':
    db=douban("www762268@foxmail.com","ch3ch2cooh")
    login_url = 'https://accounts.douban.com/login'
    session = db.login(login_url)

    myinfo_url = 'https://www.douban.com/people/143827096'
    db.get_page(myinfo_url, session)
