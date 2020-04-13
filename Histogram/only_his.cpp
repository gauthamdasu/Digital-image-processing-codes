//ploting the histogram of the given input image
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc,char *argv[])
{
Mat image;
//read the input image
image=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

int i=0,j=0,i1=0,j1=0,p1=0,q=0,s=0,q1=0;
int num_pixels=image.rows*image.cols;
float sum=0,probability[255]={0},probability2[255]={0},sk[255]={0};//since we take a 8-bit image

Mat res(image.rows, image.cols, CV_8UC1, Scalar(255, 255, 255));
uchar p;
//show and convet the image to uchar image
imshow("orginal image: ",image);
image.convertTo(image,CV_8UC1);


//increment the value by one in the particular location 

for(i=0;i<image.rows;i++)
	for(j=0;j<image.cols;j++)
		probability[image.at<uchar>(i,j)]++;   

    for(int i = 0; i < 255; i++)
    {
        probability[i] = (probability[i]/50);//)*res.rows;
    }
// line function in opencv    	

   for(int i = 0; i < 255; i++)
    {
      line(res, Point((2)*(i), res.cols), Point((2)*(i), res.cols - probability[i]),Scalar(0,0,0), 1, 8, 0);
    }

imshow("histogram",res);
waitKey(0);
return 0;
}

