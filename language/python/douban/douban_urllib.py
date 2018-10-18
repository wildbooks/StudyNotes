#!/usr/bin/env python3
# _*_coding:utf-8_*_  
# 目的：
#       掌握静态网页登录方法(urllib.requests方法)
#       掌握正则表达式提取消息的能力
#
#
# https://www.cnblogs.com/chenxiaohan/p/7654667.html
#
from urllib import request
import urllib
#from http import cookiejar
from lxml import etree

class douban:

    def __init__(self, username, password):
        print("__init__")
        # 初始化登录地址、账号和密码
        self.loginUrl = 'https://accounts.douban.com/login'
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
        print("get_captcha_info fna发放f")
        """获取验证码图片和验证码id"""
        captcha_info = dict()

        # 根据Request()方法构造一个请求对象
        req = request.Request(self.loginUrl, headers=self.headers, method='POST')
        response = request.urlopen(req)
        html = response.read()
        #shtml = html.decode("utf-8")
        #print(html)
        print(response.geturl)
        print(response.getcode)
        '''
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
        '''

    def login(self, url):
        # 构建
        print("login")
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
        req_data = {
            'source' : "index_hav",
            'redir' : 'https://www.douban.com',
            'form_email' : self.username,
            'form_password' : self.password,
            'login' : '登录',
            'remember' : 'on'
        }

        # 添加验证码信息到请求体中
        captcha_info = self.get_captcha_info()
        '''
        if captcha_info:
            req_data.update(captcha_info)
        urldata = urllib.parse.urlencode(req_data).encode('utf-8')
        req = request.Request(self.loginUrl, data=urldata, headers=self.headers)
        response = request.urlopen(req)
        html = response.read()
        print(html)
        '''

    def get_url(self, url):
        pass
    def get_page(self):
        pass
    def get_img(self):
        pass

if __name__ == '__main__':
    db=douban("www762268@foxmail.com","ch3ch2cooh")
    login_url = 'https://accounts.douban.com/login'
    db.login(login_url)
