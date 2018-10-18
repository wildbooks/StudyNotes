#!/usr/bin/env python3

# -*- coding: utf-8 -*-

import sys
import io
from urllib import request

# 方法一：直接使用已知的cookie访问
sys.stdout =io.TextIOWrapper(sys.stdout.buffer, encoding="utf8")#改变标准输出的默认编码

# 登录后才能访问的网站
#url = "https://www.baidu.com/p/setting/profile/basic"
url = "https://www.baidu.com/p/setting/profile/details"
# 浏览器登录后得到的cookie，从浏览器web develop中抓包获取
cookie_str="BAIDUID=4B9D6AC58DED5F5750BB0977D94E7939:FG=1; BIDUPSID=C7D45FB8B512765287C5D5DF8A232E1B; PSTM=1523694243; BD_UPN=133352; BDUSS=nl5U1RxWDY3SzludmFaR1Z3cTdQOExGSnZtRC1SZGNBZ2xJRjFHVEw2a2lWV3BiQVFBQUFBJCQAAAAAAAAAAAEAAABx1iOYd2lsZGJvb2tzAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACLIQlsiyEJbV; __cfduid=d2afe150d6a341427f33611d6e92c076b1530262045; MCITY=-%3A; H_PS_PSSID=26524_1435_21113_20691_26350; H_PS_645EC=3a030X26EmE5r3BhGOiYsh0xsL4hEMv1SfeqQLmrQl282CW34LIQQDAikvl%2Buaxw8N3v; delPer=0; BD_CK_SAM=1; PSINO=3; BD_HOME=1; sug=3; sugstore=1; ORIGIN=0; bdime=0"
req = request.Request(url)
# 设置cookie
req.add_header("Cookie", cookie_str)

# 设置请求头
req.add_header("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:61.0) Gecko/20100101 Firefox/61.0")
resp = request.urlopen(req)
print(resp.read().decode("utf8"))

# 方法二：模拟登录后再携带得到的cookie访问
#https://passport.baidu.com/v2/api/?loginhistory&token=ac2fa5fc478f3b3adc367eb767badec8&tpl=mn&apiver=v3&tt=1538211935455&loginversion=v4&gid=13C56B3-0675-49F2-BA5D-3A4099C92254&traceid=&callback=bd__cbs__rm1v1u

# 方法三：模拟登录后用session保持登录状态登录
# 方法四：使用无头浏览器访问
## selenium或者phantomJS浏览器
