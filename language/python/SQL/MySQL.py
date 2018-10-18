#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pip3 install pymysql3
import pymysql

class MySQL:
    def __init__(self):
        try:
            self.db={
                'db' : 'testdb',
                'tb' : 'testtb'
            }
            # 获取一个数据库链接，注意如果是UTF-8类型的，需要制定数据库
            self.conn = pymysql.connect(
                host='localhost',
                port=3306,
                user='root',
                passwd='root@123',
                charset='utf8',
                db=self.db['db']
            )
        except Exception as e:
            print(e)
            print('链接失败')
        else:
            print('链接成功')
            self.cur = self.conn.cursor()  # 获取一个游标

    # 创建数据库
    def create_databass(self):
        try:
            sql = 'create database testdb'
            res = self.cur.execute(sql)
            print(res)
        except Exception as e:
            print(e)
            print('链接失败')
        else:
            # 切换数据库
            print(e)
            print('创建数据库成功')


    # 创建表格
    def create_table(self):
        try:
            sql = 'use testdb'  #切换到testdb数据库
            res = self.cur.execute(sql)
            #sql = 'create table testtb(id int, name varchar(10), age int, sex varchar(10))'
            res = self.cur.execute(sql)
            print(res)
        except Exception as e:
            print(e)
            print('创建表格失败')
        else:
            print(e)
            # 切换数据库
            print('创建数据库成功')

    def close(self):
        self.cur.close() #关闭游标
        self.conn.close()    #释放数据库资源

    # 增
    def insert(self):
        sql='insert into testtb values(1,"Tom",18, "girl"), (2, "Jerry", 16, "boy"), (4, "hank", 24, "girl")'
        #sql='insert into testtb (1,"Tom",18, "girl"), (2, "Jerry", 16, "boy"), (4, "hank", 24, "girl")'
        res = self.cur.execute(sql)
        if res:
            self.conn.commit() #提交
        else:
            self.conn.rollback()
        print(res)

    # 删
    def remove(self):
        sql = 'delete from testtb where id=1'
        res = self.cur.execute(sql)
        if res:
            self.conn.commit()
        else:
            self.conn.rollback()
        print(res)

    # 改
    def change(self):
        sql = 'update testtb set name="Tom Ding" where id=2'
        res = self.cur.execute(sql)
        if res:
            self.conn.commit()
        else:
            self.conn.rollback()
        print(res)

    # 查
    def show(self):
        sql = 'select * from testtb'
        self.cur.execute(sql)
        data=self.cur.fetchall() #获取testtb表中所有数据
        for d in data:
            print(d)
            print('ID:%s 名字:%s 性别:%s' %(str(d[0]), d[1], d[2]))

if __name__ == '__main__':
    mysql = MySQL()

    mysql.create_databass()
    print("create table")
    mysql.create_table()

    print("insert table")
    mysql.insert()

    print("show table")
    mysql.show()

    print("remove table")
    mysql.remove()

    print("show table")
    mysql.show()

    print("change table")
    mysql.change()

    print("show table")
    mysql.show()

    mysql.close()
