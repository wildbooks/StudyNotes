#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  


using namespace cv;  


int main()  
{  
    // 读入一张图片（游戏原画）  
    Mat img=imread("./11.jpg");  
    // 创建一个名为 "游戏原画"窗口  
    namedWindow("游戏原画");  
    // 在窗口中显示游戏原画  
    imshow("游戏原画",img);  
    // 等待6000 ms后窗口自动关闭  
    waitKey(6000);  
}  
