#include "opencv2/opencv.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main()
{

    Vec3b target=Vec3b(20,179,175);
    Mat srcImage,srcShowImage;
    int n=222915;
    while(n<=223349){

        string imgName;
        //载入图片
        stringstream ss;
        string str;
        ss << n;
        ss >> str;
        imgName = str;
        imgName="/usr/local/opencv/Triangle/RawImgs/IMG_20190118_" +str+ "_1.jpg";

        Mat srcImage=imread(imgName);
        if(srcImage.empty()){
            n+=1;
            continue;

        }
        srcImage.copyTo(srcShowImage);
        //缩放比例
        double scale=0.2;
        Size dsize=Size(srcImage.cols*scale,srcImage.rows*scale);

        //调用resize函数
        resize(srcShowImage,srcShowImage,dsize);
        resize(srcImage,srcImage,dsize);

        //对目标颜色区域进行处理
        int i,j;
        int cPointB,cPointG,cPointR;
        for(i=1;i<srcShowImage.rows;i++)
            for(j=1;j<srcShowImage.cols;j++)
            {

                cPointB=srcShowImage.at<Vec3b>(i,j)[0];
                cPointG=srcShowImage.at<Vec3b>(i,j)[1];
                cPointR=srcShowImage.at<Vec3b>(i,j)[2];

                //如果是目标颜色，转变为白色
                if(abs(cPointB-target[0])<=24&abs(cPointR-target[1])<=70&abs(cPointG-target[2])<=75)
                {
                    srcShowImage.at<Vec3b>(i,j)[0]=255;
                    srcShowImage.at<Vec3b>(i,j)[1]=255;
                    srcShowImage.at<Vec3b>(i,j)[2]=255;
                }

                //其余均转变为黑色
                else
                {
                    srcShowImage.at<Vec3b>(i,j)[0]=0;
                    srcShowImage.at<Vec3b>(i,j)[1]=0;
                    srcShowImage.at<Vec3b>(i,j)[2]=0;
                }
            }

            //通过二值化的方式来取反
            cvtColor(srcShowImage,srcShowImage, CV_BGR2GRAY);
            GaussianBlur(srcShowImage,srcShowImage,Size(5,5),0);
            threshold(srcShowImage,srcShowImage,130, 255,CV_THRESH_BINARY_INV);

            Mat element_9(3,3, CV_8U, cv::Scalar(1));
            morphologyEx(srcShowImage,srcShowImage,cv::MORPH_OPEN, element_9);
            threshold(srcShowImage,srcShowImage,130,255,CV_THRESH_BINARY_INV);

            //
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            //寻找的目标颜色所存在的区域
            findContours(srcShowImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

            //随机数生成器，生成随机颜色
            cv::RNG rng;
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            for( int i = 0; i < contours.size(); i++ )
            {
                //使用边界框的方式
                CvRect aRect =  boundingRect(contours[i]);
                vector<CvRect> rect;
                //边界框面积
                int area=aRect.width*aRect.height;
                //如边界框长宽比或面积不符则不会被绘制
                if (((double)aRect.width/(double)aRect.height>=0.81)&((double)aRect.width/(double)aRect.height<=1.153)&area>=1400)
                {
                    //绘制边界框
                    rectangle(srcImage,cvPoint(aRect.x,aRect.y),cvPoint(aRect.x+aRect.width ,aRect.y+aRect.height),color,2);
                    cout<<(double)aRect.width/(double)aRect.height<<endl;
                }
            }

        //存储
        stringstream ss2;
        string s,name;
        ss2<<n;
        ss2>>s;
        name="/usr/local/opencv/photo-1/"+s+".jpg";
        imwrite(name,srcImage);
        //循环
        n+=1;
    }
    return 0;
}
