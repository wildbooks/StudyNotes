#include <stdio.h>
/**
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
    float rulv=0.0005;
    float chulv=0.0005;
    float chu;
    float ru;
    float shouyilv;
    int n;
    printf("请输入对应数字\n\t1.计算费率\n\t2.计算收益率\n\t3.计算涨迭后价格\n");
    scanf("%d", &n);
    switch(n){
        case 1:
            /**
             * 卖出单价=买入单价*(实际收益率+1)*(1+买入费率)/(1-卖出费率)
             *  chu       ru        shouyilv         rulv         chulv
             *  chu = ru * (shouyilv + 1) * (1 + rulv) / (1 - chulv)
             */
            printf("请输入买入单价,期待收益率\n");
            scanf("%f%f", &ru, &shouyilv);
            chu = ru * (shouyilv + 1) * (1 + rulv) / (1 - chulv);
            printf("想达到%f\%的收益率，卖出单价为%f\n", shouyilv, chu);
            break;

        case 2:
            /**
             *  实际收益率=(卖出单价*(1-卖出费率))/(买入单价*(1+买入费率)) -1
             *  shouyilv     chu          chulv      ru           rulv
             *  shouyilv = (chu * (1 - chulv)) / (ru * (1 + rulv)) -1
             */
            printf("请输入买入单价,卖出单价\n");
            scanf("%f%f", &ru, &chu);
            shouyilv = (chu * (1 - chulv)) / (ru * (1 + rulv)) -1;
            printf("卖出单价为%f,收益率为%f\%\n", chu, shouyilv*100);
            break;
        case 3:
            /**
             *  下次单价=(1+涨跌率)*当前单价
             *   chu         shouyilv  ru
             *   chu = (1+ shouyilv) * ru
             */
            printf("请输入当前单价,期待涨跌率\n");
            scanf("%f%f", &ru, &shouyilv);
            chu = (1+ shouyilv) * ru;
            printf("涨跌率为%f\%,下次单价为%f\n", shouyilv*100, chu);
            break;
        default:
            printf("输入有误\n");

    }
    return 0;
}
