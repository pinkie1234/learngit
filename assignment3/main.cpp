#include "opencv2/opencv.hpp"
#include "iostream"
#include <cmath>

using namespace cv;
using namespace std;

int h_min=26;
int s_min=97;
int v_min=159;


int h_max=34;
int s_max=255;
int v_max=255;


int main()
{
    Mat srcImage,tempImage;
    int n=1;
    while(n<=43){
        //载入图像
        string imgName;
        stringstream ss;
        ss<<n;
        string str;
        ss>>str;
        imgName="/usr/local/opencv/Triangle/RawImgs/IMG_20190118_"+str+".jpg";

        Mat srcImage=imread(imgName);

        Mat tempImage=srcImage.clone();

        //转换颜色空间
        cvtColor(srcImage,srcImage,CV_BGR2HSV);
        Scalar hsv_min(h_min,s_min,v_min);
        Scalar hsv_max(h_max,s_max,v_max);
        Mat dstImage=Mat::zeros(srcImage.size(),CV_8U);
        //
        inRange(srcImage,hsv_min,hsv_max,dstImage);
        Mat element=getStructuringElement(MORPH_RECT,Size(1.5,1.5));
        morphologyEx(dstImage,dstImage,MORPH_ERODE,element,Point(-1,-1),1);


        //
        vector<vector<Point> > contours;
        findContours(dstImage,contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);
        vector<Rect> rect(contours.size());
        for(int i=0;i<contours.size();i++)
        {
            rect[i]=boundingRect(contours[i]);
            int x=rect[i].x;
            int y=rect[i].y;
            int width=rect[i].width;
            int height=rect[i].height;
            if(width/height<=1.6&width*height>=55000){
                  rectangle(tempImage,Point(x,y),Point(x+width,y+height),Scalar(0,0,255),4);
            }

        }

        //压缩
        Size size=Size(tempImage.cols*0.2,tempImage.rows*0.2);
        resize(tempImage,tempImage,size);
        imshow("result",tempImage);
        waitKey(10);

        //存储
        stringstream ss2;
        string s,name;
        ss2<<n+44;
        ss2>>s;
        name="/usr/local/opencv/photo-1/"+s+".jpg";
        imwrite(name,tempImage);
        //循环
        n+=1;
    }
    return 0;
}
