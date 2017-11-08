/**
	Following tasks are performed:
		1. Adding Gaussian Noise (sigma 0.5) to an image and removal of noise.
		2. Adding Salt and Pepper noise (density = 0.02) to an image and removal of noise
		3. Increasing the brightness of an image by a constant factor 50
		4. Count the number of apples in the image using erosion, dilation and connected components concept
		
		@author: Shreya Vishwanath Rao
		@version 1.0: 02/19/2017
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    
    Mat I;
    I= imread("../pic.png");
    if(! I.data )
    {
        cout<<  "Could not open or find the image" << endl ;
        return -1;
    }
	
	namedWindow("Original Image");
    
	imshow("Original Image", I);
    moveWindow("Original Image", 10, 100);
	
	//Question 1, Gaussian Noise and removal
    
    Mat GaussianNoise = Mat(I.size(),I.type());
    randn(GaussianNoise,0,15);
    
    Mat N1 = I.clone();
    N1 += GaussianNoise;
    
    imshow("Gaussian Noise", N1);
    moveWindow("Gaussian Noise", 650, 100);
    
    waitKey(0);
    
    Mat H1=N1.clone();
    
    for (int y = 1; y < H1.rows - 1; y++)
    {
        for (int x = 1; x < H1.cols - 1; x++)
        {
            for (int z = 0; z < 3; z++)
            {
                int sum = N1.at<Vec3b>(y - 1 ,x - 1)[z]+N1.at<Vec3b>(y, x - 1)[z]+N1.at<Vec3b>(y + 1, x - 1)[z]+N1.at<Vec3b>(y - 1, x)[z]+N1.at<Vec3b>(y, x)[z]+N1.at<Vec3b>(y + 1, x)[z]+N1.at<Vec3b>(y - 1, x + 1)[z]+N1.at<Vec3b>(y, x + 1)[z]+N1.at<Vec3b>(y + 1, x + 1)[z];
                sum=sum/9;
                H1.at<Vec3b>(y, x)[z] = sum;
            }
        }
    }
    
    imshow("Gaussian Noise removal", H1);
    moveWindow("Gaussian Noise removal", 650, 100);
    
    waitKey(0);
    
    //Question 2, Salt and Pepper Noise and Removal
    
    Mat saltpeppernoise = Mat::zeros(I.rows, I.cols,CV_8U);
    randu(saltpeppernoise,0,255);
    
    float d=0.02;
    int d_=d*255;
    
    Mat black = saltpeppernoise <= (d_/2);
    Mat white = saltpeppernoise > (d_/2) & saltpeppernoise <= (d_) ;
    
    Mat N2= I.clone();
    N2.setTo(0,black);
    N2.setTo(255,white);
    

    imshow("Salt&Pepper Noise", N2);
    moveWindow("Salt&Pepper Noise", 650, 100);
    
    waitKey(0);
    
    Mat H2=N2.clone();
    
    for (int y = 1; y < H2.rows - 1; y++)
    {
        for (int x = 1; x < H2.cols - 1; x++)
        {
            for (int z = 0; z < 3; z++)
            {
                int window[9]= {N1.at<Vec3b>(y - 1 ,x - 1)[z],N1.at<Vec3b>(y, x - 1)[z],N1.at<Vec3b>(y + 1, x - 1)[z],N1.at<Vec3b>(y - 1, x)[z],N1.at<Vec3b>(y, x)[z],N1.at<Vec3b>(y + 1, x)[z],N1.at<Vec3b>(y - 1, x + 1)[z],N1.at<Vec3b>(y, x + 1)[z],N1.at<Vec3b>(y + 1, x + 1)[z]};
                sort(window, window + 9);
                H2.at<Vec3b>(y, x)[z] = window[4];
            }
        }
    }

    
    imshow("Salt&Pepper Noise removal", H2);
    moveWindow("Salt&Pepper Noise removal", 650, 100);
    
    waitKey(0);
	
	//Question 3, Brightness increased
    
    Mat B1=I.clone();
    
    for( int y = 0; y < B1.rows; y++ )
        for( int x = 0; x < B1.cols; x++ )
            for( int c = 0; c < 3; c++ )
                B1.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( B1.at<Vec3b>(y,x)[c]  + 50 );
    
    
   
    namedWindow("Brightened Image");
   
    imshow("Brightened Image", B1);
    moveWindow("Brightened Image", 650, 100);
    
    waitKey(0);
    
    //Question 4, Counting the number of elements
    
	Mat element;
    int dilation_type = MORPH_RECT;
    int dilation_size ;
    
    //For Original Image, I
    
    Mat C=I.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else 
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, Mat());
    dilate(C, C, Mat());

    int number=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Original Image "<<number<<endl;
    
    //For Brightened Image, B1
    
    C=B1.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=150)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, Mat());
    dilate(C, C, Mat());
    
    number=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Brightened Image "<<number<<endl;
    
    //For Gaussian Noise Image, N1
    
    dilation_size= 20 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));

    
    C=N1.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    number=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Gaussain Noise Image "<<number<<endl;
    
    
    //For Gaussian Noise Cleared Image, H1
    
    dilation_size= 24 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));
    
    
    C=H1.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    number=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Gaussain Noise Cleared Image "<<number<<endl;
    
    
    //For Salt and Pepper Noise Image, N2
    
    dilation_size= 11 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));
    
    
    C=N2.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    number=connectedComponents(C,  C, 8,CV_32S);
    cout<<"Salt and pepper noise Image "<<number<<endl;
    
    
    //For Salt and Pepper Noise Cleared Image, H2
    
    dilation_size= 15 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));
    
    
    C=H2.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    number=connectedComponents(C,  C, 8,CV_32S);
    cout<<"Salt and pepper noise cleared Image "<<number<<endl;
}
