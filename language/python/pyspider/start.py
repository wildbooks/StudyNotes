#!/usr/bin/env python
# -*- encoding: utf-8 -*-
# Created on 2018-11-05 22:42:40
# Project: new
# http://localhost:5000

from pyspider.libs.base_handler import *


class Handler(BaseHandler):
    crawl_config = {
    }
    #这个设置是告诉scheduler（调度器）on_start方法每天执行一次。
    @every(minutes=24 * 60)
    # 代码入口
    def on_start(self):
        self.crawl('http://www.pyspider.cn/', callback=self.index_page)

    # 这个设置告诉scheduler（调度器）这个request（请求）过期时间是10天，10天内再遇到这个请求直接忽略。这个参数也可以在self.crawl(url, age=10*24*60*60) 和 crawl_config中设置。
    @config(age=10 * 24 * 60 * 60)
    # 这个方法获取一个Response对象。 response.doc是pyquery对象的一个扩展方法。pyquery是一个类似于jQuery的对象选择器。
    def index_page(self, response):
        for each in response.doc('a[href^="http"]').items():
            self.crawl(each.attr.href, callback=self.detail_page)

    # 这个是优先级设置。数字越大越先执行。
    @config(priority=2)
    # 返回一个结果集对象。这个结果默认会被添加到resultdb数据库（如果启动时没有指定数据库默认调用sqlite数据库）。你也可以重写on_result(self,result)方法来指定保存位置。
    def detail_page(self, response):
        return {
            "url": response.url,
            "title": response.doc('title').text(),
        }
