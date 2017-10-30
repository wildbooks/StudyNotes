/** 
 * 把bmp文件中的相关信息提出来,看文件调色板类型,获取位图文件大小,
 * 获取位图RGB数据的位置
 *      1. 把文件大小，调色板类型打印出来
 *      2. 把RGB信息保存在rgb.rgb文件中
 */  

#include<stdio.h>
#include <stdlib.h>

/** 
 * Split Y, U, V planes in YUV420P file. 
 * @param url  Location of Input YUV file. 
 * @param w    Width of Input YUV file. 
 * @param h    Height of Input YUV file. 
 * @param num  Number of frames to process. 
 * 
 */  
int simplest_yuv420_split(char *url, int w, int h,int num){  
    int i;
    FILE *fp=fopen(url,"rb+");  
    FILE *fp1=fopen("output_420_y.y","wb+");  
    FILE *fp2=fopen("output_420_u.y","wb+");  
    FILE *fp3=fopen("output_420_v.y","wb+");  

    unsigned char *pic=(unsigned char *)malloc(w*h*3/2);  

    for(i=0;i<num;i++){  

        fread(pic,1,w*h*3/2,fp);  
        //Y  
        fwrite(pic,1,w*h,fp1);  
        //U  
        fwrite(pic+w*h,1,w*h/4,fp2);  
        //V  
        fwrite(pic+w*h*5/4,1,w*h/4,fp3);  
    }  

    free(pic);  
    fclose(fp);  
    fclose(fp1);  
    fclose(fp2);  
    fclose(fp3);  

    return 0;  
}  
void main()
{
    simplest_yuv420_split("../picture/54866b9cb21bd.bmp",256,256,1);
}
