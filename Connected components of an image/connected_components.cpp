#include<iostream>
#include<opencv2/opencv.hpp>
#include<cstdlib>
using namespace std;
using namespace cv;
int count1=0,cnt=0,n=0,ui=0,uj=0,con_comps=0,cnt1=1;

//functions to be written 
// 4-adjacency or 8-adjacency or m adjacency, path, connceted component 

void adjacency(Mat A, Mat B,Mat out, int i,int j)
{
	int p,q,r,s;
	B.at<uchar>(i,j)=1;
	Size s1= A.size();
	if(i+1<	s1.height)
	{	
		p=A.at<uchar>(i+1,j);
		if (p >= 250 && p<=255)
			if (B.at<uchar>(i+1,j)==0)
			{
				out.at<uchar>(i+1,j)=cnt1;
				adjacency(A,B,out,i+1,j);
			}
	}
	if(j+1<s1.width)
	{
		q=A.at<uchar>(i,j+1);
		if (q >= 250 && q<=255)
			if (B.at<uchar>(i,j+1)==0)
			{
				B.at<uchar>(i,j+1)=1;
				out.at<uchar>(i,j+1)=cnt1;
				adjacency(A,B,out,i,j+1);
			}
	}

	if(i-1>=0)
	{
		r=A.at<uchar>(i-1,j);
		if (r >= 250 && r<=255)
			if (B.at<uchar>(i-1,j)==0)
			{
				B.at<uchar>(i-1,j)=1;
				out.at<uchar>(i-1,j)=cnt1;
				adjacency(A,B,out,i-1,j);
			}
	}

	if(j-1>=0)
	{
		s=A.at<uchar>(i,j-1);		
		if (s >= 250 && s<=255)
			if (B.at<uchar>(i,j-1)==0)
			{
				B.at<uchar>(i,j-1)=1;
				out.at<uchar>(i,j-1)=cnt1;
				adjacency(A,B,out,i,j-1);
			}

	}			
}


int main(int argc, char *argv[])
{
	Mat image,ima,res;
	Mat Final,out;
	int n1=0; 		//number of connected components
	int  p =0;
	image=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);		//input image through command line arguments

	Final= Mat::zeros(image.rows,image.cols,CV_8UC1);
	out= Mat::zeros(image.rows,image.cols,CV_16UC1);
	for(int i=0;i<image.rows;i++)
		for(int j=0;j<image.cols;j++)
		{
			if (Final.at<uchar>(i,j)!=1)
			{	
				p = image.at<uchar>(i,j); //getting the values of p and q
				if( (p >= 250  && p<=255))// && (q >= 250  && q<=255))
				{	
					//check for its adjacency
					image.at<uchar>(i,j)=cnt1;
					adjacency(image,Final,out,i,j);
					cnt1++;
				}
				else
				{
					image.at<uchar>(i,j)=0;
				}	
			}	
		}

	cout<<"The number of connected components are "<<cnt1<<endl;
	cout<<"Enter the number of connected componets you want"<<endl; cin>>n;
	imshow("All connected components",out);
	for(int i=0;i<image.rows;i++)
		for(int j=0;j<image.cols;j++)
			if (out.at<uchar>(i,j)==n)
			{
				cout<<i << "  " << j << endl;
				Final.at<uchar>(i,j)=255;
			}
			else
				Final.at<uchar>(i,j)=0;
	//imshow("Conncted Components are ",out);
	//cout<<out;	
	imshow("Conncted Components are ",Final);
	waitKey(0);
	return 0;
}
