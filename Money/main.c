#include <stdio.h>
/**
 * 本程序创建于2017.8.27号，用于协助我炒比特币
 * 默认买入和卖出的费率为0.05%
 * 卖出单价=买入单价*(实际收益率+1)*(1+买入费率)/(1-卖出费率)
 *  chu       ru        shouyilv         rulv         chulv
 *  chu = ru * (shouyilv + 1) * (1 + rulv) / (1 - chulv)
 *
 *  实际收益率=(卖出单价*(1-卖出费率))/(买入单价*(1+买入费率)) -1
 *  shouyilv     chu          chulv      ru           rulv
 */

int main()
{
    float rulv=0.001;
    float chulv=0.001;
    float chu;
    float ru;
    float shouyilv;
    int n;
    int i;
    float sum, num;
    float b, d, xi;
    printf("请输入对应数字\n\t1.计算卖出价格和个数\n\t2.计算买入价格和数量\n\t3.计算收益率\n");
    scanf("%d", &n);
    switch(n){
        case 1:

            /**
             * 卖出单价=买入单价*(实际收益率+1)*(1+买入费率)/(1-卖出费率)
             *  chu       ru        shouyilv         rulv         chulv
             *  chu = ru * (shouyilv + 1) * (1 + rulv) / (1 - chulv)
             *
             *  买入数量n=买入数量基数*(b+d*(n-1))^(n-1) (b为系数基数,d为系数基数的基数)  (系数会变)
             *    sum       num
             */

            printf("请输入买入单价和个数,计算卖出和个数\n");
            scanf("%f%f", &ru, &num);
            b = 1.2;
            d = 0.1;
            for(i=0; i<21; i++)
            {
                xi=b+d*(i-1); //系数
                if(i)
                    sum *= xi;
                else
                    sum = num;

                shouyilv=0.03 + i * 0.01;
                chu = ru * (shouyilv + 1) * (1 + rulv) / (1 - chulv);
                printf("在涨%3.0f%时,以单价%3.6f卖出%4.02f个货币xi=%f\n", shouyilv*100, chu, sum, xi);
            }
            break;

        case 2:

            /**
             *
             *  买入数量n=第一次买入数量*b^(n-1) (注意:b为系数基数,为1.2)  (系数不变)
             *    sum       num             次数为i
             *
             *  买入数量n=买入数量基数*(b+d*(n-1))^(n-1) (b为系数基数,d为系数基数的基数)  (系数会变)
             *    sum       num
             *
             *
             *  下次单价=(1-跌率)*当前单价
             *   chu         shouyilv  ru
             *   chu = (1- shouyilv) * ru
             */

            printf("请输入买入参考单价和参考买入个数,计算买入价格阶梯\n");
            scanf("%f%f", &ru, &num);
            b = 1.2;
            d = 0.1;
            for(i=0; i<21; i++)
            {
                xi=b+d*(i-1); //系数
                if(i)
                    sum *= xi;
                else
                    sum = num;

                shouyilv=0.03 + i * 0.01;
                chu = (1- shouyilv) * ru;
                printf("在跌%3.0f%时,以单价%3.6f买入%4.2f个货币xi=%f\n", shouyilv*100, chu, sum, xi);
            }
            break;

        case 3:

            /**
             *
             *  实际收益率=(卖出单价*(1-卖出费率))/(买入单价*(1+买入费率)) -1
             *  shouyilv     chu          chulv      ru           rulv
             *  shouyilv = (chu * (1 - chulv)) / (ru * (1 + rulv)) -1
             *
             *  收益 = 买入单价*实际收益率*个数
             *
             *  卖出手续费 = 卖出单价*卖出费率*个数
             */

            printf("请输入买入单价,卖出单价,卖出个数\n");
            scanf("%f%f%f", &ru, &chu, &b);
            shouyilv = (chu * (1 - chulv)) / (ru * (1 + rulv)) -1;
            printf("卖出单价为%f,收益率为%0.3f%,每股收益%f,总收益%f,卖出手续费%f\n", chu, shouyilv*100, ru*shouyilv, ru*shouyilv*b, chu*0.0005*b);
            break;

        default:
            printf("输入有误\n");

    }
    return 0;
}
