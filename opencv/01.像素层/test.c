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

/**
 * Generate YUV420P gray scale bar.
 * @param width    Width of Output YUV file.
 * @param height   Height of Output YUV file.
 * @param ymin     Max value of Y
 * @param ymax     Min value of Y
 * @param barnum   Number of bars
 * @param url_out  Location of Output YUV file.
 */
int simplest_yuv420_graybar(int width, int height,int ymin,int ymax,int barnum,char *url_out){
    int barwidth;
    float lum_inc;
    unsigned char lum_temp;
    int uv_width,uv_height;
    FILE *fp=NULL;
    unsigned char *data_y=NULL;
    unsigned char *data_u=NULL;
    unsigned char *data_v=NULL;
    int t=0,i=0,j=0;

    barwidth=width/barnum;
    lum_inc=((float)(ymax-ymin))/((float)(barnum-1));
    uv_width=width/2;
    uv_height=height/2;

    data_y=(unsigned char *)malloc(width*height);
    data_u=(unsigned char *)malloc(uv_width*uv_height);
    data_v=(unsigned char *)malloc(uv_width*uv_height);

    if((fp=fopen(url_out,"wb+"))==NULL){
        printf("Error: Cannot create file!");
        return -1;
    }

    //Output Info
    printf("Y, U, V value from picture's left to right:\n");
    for(t=0;t<(width/barwidth);t++){
        lum_temp=ymin+(char)(t*lum_inc);
        printf("%3d, 128, 128\n",lum_temp);
    }
    //Gen Data
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            t=i/barwidth;
            lum_temp=ymin+(char)(t*lum_inc);
            data_y[j*width+i]=lum_temp;
        }
    }
    for(j=0;j<uv_height;j++){
        for(i=0;i<uv_width;i++){
            data_u[j*uv_width+i]=128;
        }
    }
    for(j=0;j<uv_height;j++){
        for(i=0;i<uv_width;i++){
            data_v[j*uv_width+i]=128;
        }
    }
    fwrite(data_y,width*height,1,fp);
    fwrite(data_u,uv_width*uv_height,1,fp);
    fwrite(data_v,uv_width*uv_height,1,fp);
    fclose(fp);
    free(data_y);
    free(data_u);
    free(data_v);
    return 0;
}
void main()
{
    //simplest_yuv420_split("./picture/lena_256x256_yuv420p.yuv",256,256,1);
    simplest_yuv420_graybar(640, 360,0,255,10,"graybar_640x360.yuv");
}
