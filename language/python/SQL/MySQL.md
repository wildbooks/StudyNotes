# 命令工具
  mysql -u root -proot@123  #访问本地数据库
  mysql -h localhost -u root -proot@123 #访问远程数据库

# 用户授权
# 数据库操作
  show databases #显示所有数据库
  create database testdb #创建名为testdb数据库
  use testdb  #选择名为testdb的数据库
  drop database testdb #删除数据库
  select database() #查看当前选择的数据库
# 数据库表操作
  show tables #显示当前数据库中所有表格
  create table testtb values(id int, name varchar(10), age int, sex varchar(10)) #创建testtb表格
  describe testtb #查看表testtb基本结构
  show create table testtb #查看表testtb详细定义
  alter table 旧表名 rename 新表名 #修改表名
  alter table 表名 modify 属性名 数据类型     # 修改字段的数据类型
  alter table 表名 change 旧属性名 新属性名 新数据类型 #修改字段名
  drop table testtb #删除表格testtb
  delete from testtb where id=1; #删除testtb表格中的数据
  delete from testtb  #清空表
  truncate table testtb #清空表testtb
# 参考文档
  https://www.cnblogs.com/sqbk/p/5806797.html
