#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    //载入的图片和输出的图片
    Mat srcImage,srcShowImage;
    //设定目标颜色
    Vec3b target=Vec3b(30,190,190);
    //图片名字
    string ImageName;
    //图片编号
    int n = 1;
    while (n <=43)
    {

        //载入图片
        stringstream ss;
        string str;
        ss << n;
        ss >> str;
        ImageName = str;
        ImageName="/usr/local/opencv/Assignment1/" +str+ ".jpg";
        cout<<ImageName<<endl;
        srcImage=imread(ImageName);
        srcImage.copyTo(srcShowImage);
        //缩放比例
        double scale=0.2;
        Size dsize=Size(srcImage.cols*scale,srcImage.rows*scale);

        //调用resize函数
        resize(srcShowImage,srcShowImage,dsize);
        resize(srcImage,srcImage,dsize);
        //imshow("a",srcImage);

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
                if(abs(cPointB-target[0])<=26&abs(cPointR-target[1])<=26&abs(cPointG-target[2])<=26)
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
            threshold(srcShowImage,srcShowImage,130, 255,CV_THRESH_BINARY_INV);
            //erode(srcShowImage,srcShowImage,Mat(1.5,1.5,CV_8U),Point(-1,-1),7);
            Mat element_9(9, 9, CV_8U, cv::Scalar(1));
            morphologyEx(srcShowImage,srcShowImage,cv::MORPH_OPEN, element_9);
            threshold(srcShowImage,srcShowImage,130,255,CV_THRESH_BINARY_INV);
            //imshow("a",srcShowImage);

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
                if (((double)aRect.width/(double)aRect.height>=0.8)&((double)aRect.width/(double)aRect.height<=1.6)&area>=1200&area<=90000)
                {
                    //绘制边界框
                    rectangle(srcImage,cvPoint(aRect.x,aRect.y),cvPoint(aRect.x+aRect.width ,aRect.y+aRect.height),color,2);

                }
            }

            //显示图片
            imshow("result",srcImage);

            //写入磁盘
            ss << n;
            ss >> str;
            string ResultPhotoName="/usr/local/opencv/photo-2/"+str+".jpg";
            imwrite(ResultPhotoName,srcImage);

            waitKey(10);

            //循环
            n+=1;
    }

    waitKey(0);
    return 0;
}
