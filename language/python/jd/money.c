/**
 * 刷卡攻略
 */
#include <stdio.h>

typedef struct {
  char name[20];    //信用卡名
  int gu;           //固定额度
  int lin;          //临时额度
  int total;        //总额度
  int zhang;        //账单日
  int huan;         //还款日

  float shuakalv;   //建议刷卡率        填写
  float shishualv;  //实际刷卡率        计算
  int yishua;       //本月已刷额度      填写
  int yushua;       //需刷额度          计算
  int carde;        //卡剩余额度        填写

  /*
    剩余刷卡时间
    每天至少刷卡额度

  */
} cardtype;

/**
 * 实际刷卡率 = 本月已刷额度/总额度
 * 需刷额度 = (建议刷卡率-实际刷卡率)*总额度
 */

typedef struct {
  char name[20];    //信用卡名
  int gu;           //固定额度
  int lin;          //临时额度
  int total;        //总额度

  float shuakalv;   //建议刷卡率        填写
  float shishualv;  //实际刷卡率        计算
  int yishua;       //本月已刷额度      填写
  int yushua;       //需刷额度          计算
  int carde;        //卡剩余额度        填写
} totaltype;

#define TYPE_DEFINE(cardname, cardguding, cardlinshi, cardzonge, shua, cardshengyu) \
{.name=cardname, .gu=cardguding, .lin=cardlinshi, .total=cardzonge, .yishua=shua, .carde=cardshengyu}

cardtype allcard[]={
  TYPE_DEFINE("招商", 27000, 32000, 59000, 0, 1000),
  TYPE_DEFINE("交通", 34000, 12000, 46000, 0, 1000),
  TYPE_DEFINE("中信", 8000, 2500, 10500, 0, 1000),
  TYPE_DEFINE("广发", 15000, 0, 15000, 0, 1000),
  TYPE_DEFINE("总统计", 0, 0, 0, 0, 0),
};

totaltype total;

/**
 * 单卡统计计算
 */
int cardsuan(cardtype **card, int len)
{
  int ret=-1;
  /*参数合法性检测*/
  if(!(card[len]->yishua && card[len]->total && card[len]->shuakalv))
    printf("%s:数据无效",__func__);

  if(len){
    card[len]->shishualv = card[len]->yishua / card[len]->total;
    card[len]->yushua = (card[len]->shuakalv - card[len]->shishualv) * card[len]->total;

    ret = cardsuan(card, len-1);
  }else{
    ret = 0;
  }
  return ret;
}

/**
 *
 * 总共统计
 *
 */
int totalcard(cardtype *card, int len, totaltype *total)
{
  int ret = -1;
  /*参数合法性*/
  if(!card && !total)
    return ret;

  if(len)
  {
    total->gu += card[len].total;
    total->lin += card[len].lin;
    total->total += card[len].total;

    total->yishua += card[len].yishua;
    total->yushua += card[len].yushua;
    total->carde += card[len].carde;

    /*递归*/
    ret = totalcard(card, len-1, total);
  }else{
    total->shishualv = total->yishua / total->total;
    total->yushua = (total->shuakalv - total->shishualv) * total->total;
    ret = 0;
  }
  return ret;
}

void cardprint()
{
  /*打印每张卡*/
  /*打印一张卡*/
}
int main()
{
  int len;
  len = sizeof(allcard)/sizeof(cardtype);
  printf("cardname=%s\n", allcard[4].name);
  printf("len=%d\n", len);
  return 0;
}
