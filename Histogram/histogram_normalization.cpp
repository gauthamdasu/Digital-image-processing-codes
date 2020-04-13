//g++ mask_averaging.cpp `pkg-config --cflags --libs opencv`
#include<iostream>
#include<opencv2/opencv.hpp>
//#include<opencv2/plot.hpp>
using namespace std;
using namespace cv;
void histogram(Mat image);

int main(int argc,char *argv[])
{
Mat image,res;
image=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
int i=0,j=0,i1=0,j1=0;
int num_pixels=image.rows*image.cols;
float sum=0,probability[255]={0},probability2[255]={0},sk[255]={0};//since we take a 8-bit image
res= Mat::zeros(image.rows,image.cols,CV_8UC1);
uchar p;
imshow("orginal image: ",image);
histogram(image);
//waitKey(0);
image.convertTo(image,CV_8UC1);

for(i=0;i<image.rows;i++)
	for(j=0;j<image.cols;j++)
		probability[image.at<uchar>(i,j)]++;   //in that location we increment the value by one

for(i=0;i<255;i++)
    	probability[i]=probability[i]/num_pixels;	       //we get the probability of the each pixel

//histogram equilazation
for (i1=0;i1<255;i1++)

	{
	sum=0;

  		for(j=0;j<i1;j++)
		sum+=probability[j];	

	sk[i1]=sum*255	;
	}	
	
for(i=0;i<image.rows;i++)
	for(j=0;j<image.cols;j++)
		probability2[image.at<uchar>(i,j)]++;//=sk[image.at<uchar>(i,j)];   //in that location we increment the value by one



for(i=0;i<image.rows;i++)
	for(j=0;j<image.cols;j++)
		{
			res.at<uchar>(i,j)=sk[image.at<uchar>(i,j)];//=sk[image.at<uchar>(i,j)];   //in that location we increment the value by one];
		}

imshow("result",res);
histogram(res);
waitKey(0);
return 0;
}


void histogram(Mat image)
{
int i=0,j=0,i1=0,j1=0,p1=0,q=0,s=0,q1=0;
int num_pixels=image.rows*image.cols;
float sum=0,probability[255]={0},probability2[255]={0},sk[255]={0};//since we take a 8-bit image

Mat res(400, 512, CV_8UC1, Scalar(255, 255, 255));
uchar p;
//show and convet the image to uchar image
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
      line(res, Point((512/256)*(i), res.cols), Point((512/256)*(i), res.rows - probability[i]),Scalar(0,0,0), 1, 8, 0);
    }

imshow("histogram",res);
waitKey(0);
}

