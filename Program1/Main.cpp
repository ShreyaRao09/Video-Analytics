/**
	To change the brightness of the image.
	Convert from RGB to HSV color space.
	Detect objects in both RGB and HSV color spaces
	
	@author: Shreya Vishwanath Rao
	@version 1.0: 02/05/2017
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;


float max(float r, float g, float b)
{
    float max;
    if (r>g)
    {
        if (r>b)
            max = r;
        else
            max = b;
    }
    else
    {
        if (g>b)
            max = g;
        else
            max = b;
    }
    return max;
}

float min(float r, float g, float b)
{
    float min;
    if (r<g)
    {
        if (r<b)
            min = r;
        else
            min = b;
    }
    else
    {
        if (g<b)
            min = g;
        else
            min = b;
    }
    return min;
}

Mat rgb_hsv(Mat image)
{
    float V, S, H=0;
    uchar red, green, blue, u_V, u_S, u_H;
    float f_red, f_green, f_blue;
    
    int V_int,r_int,b_int,g_int;
    
    float FLOAT_TO_BYTE = 255.0f;
    float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;
    
    for (int y = 0; y<image.rows; y++)
    {
        for (int x = 0; x<image.cols; x++)
        {
            blue = image.at<Vec3b>(y, x)[0];
            green = image.at<Vec3b>(y, x)[1];
            red = image.at<Vec3b>(y, x)[2];
            
            f_blue = (float)BYTE_TO_FLOAT*blue;
            f_green = (float)BYTE_TO_FLOAT*green;
            f_red = (float)BYTE_TO_FLOAT*red;
            
            V = max(f_red, f_green, f_blue);
            V_int=(int)V;
            r_int=(int)f_red;
            b_int=(int)f_blue;
            g_int=(int)f_green;
            if (V == 0)
                S = 0;
            else
            {
                S = ((V - min(f_red, f_green, f_blue)) / V);
            }
            
            if (V_int == r_int)
                H = (float)((60 * (f_green - f_blue)) / (V - min(f_red, f_green, f_blue)));
            else if (V_int == g_int)
                H = (float)((120 + 60 * (f_blue - f_red)) / (V - min(f_red, f_green, f_blue)));
            else if (V_int == b_int)
                H = (float)((240 + 60 * (f_red - f_green)) / (V - min(f_red, f_green, f_blue)));
            
            if (H<0)
                H = H + 360;
            
            u_V = (uchar)(225 * V);
            
            u_S = (uchar)(225 * S);
            
            u_H = (uchar)(H / 2);
            
            image.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(u_H);
            image.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(u_S);
            image.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(u_V);
            
        }
    }
    return image;
}

Mat rgb_red_detect(Mat image)
{
    uchar red, green, blue;
    int x_max=0, y_max=0, x_min=image.cols, y_min=image.rows;
    //medianBlur(image, image, 3);
    for (int y = 0; y<image.rows; y++)
    {
        
        for (int x = 0; x<image.cols; x++)
        {
            blue = image.at<Vec3b>(y, x)[0];
            green = image.at<Vec3b>(y, x)[1];
            red = image.at<Vec3b>(y, x)[2];
            
            if (red>=115 && green<=65 && blue<=70) //threshold values
            {
                //its red, make it white
                image.at<Vec3b>(y, x)[0]=255;
                image.at<Vec3b>(y, x)[1]=255;
                image.at<Vec3b>(y, x)[2]=255;
                
            
                    
                    if(x<=x_min)
                        x_min=x;
                    if(y<=y_min)
                        y_min=y;
                    if(x>=x_max)
                        x_max=x;
                    if(y>=y_max)
                        y_max=x;
                
                
                
            }
            else
            {
                //not red, make it black
                image.at<Vec3b>(y, x)[0]=0;
                image.at<Vec3b>(y, x)[1]=0;
                image.at<Vec3b>(y, x)[2]=0;
            }
        }
    }
    
    int radius=y_max-y_min;
    int center_x=(x_max+x_min)/2;
    int center_y=(y_max+y_min)/2;
    circle(image,Point(center_x,center_y),radius/2,Scalar(0,0,255),2,8);
    
    
    return image;
    
    }

Mat rgb_red_detect_bright(Mat image)
{
    uchar red, green, blue;
    int x_max=0, y_max=0, x_min=image.cols, y_min=image.rows;
    //medianBlur(image, image, 3);
    for (int y = 0; y<image.rows; y++)
    {
        
        for (int x = 0; x<image.cols; x++)
        {
            blue = image.at<Vec3b>(y, x)[0];
            green = image.at<Vec3b>(y, x)[1];
            red = image.at<Vec3b>(y, x)[2];
            
            if (red>=165 && green<=115 && blue<=120) //threshold values
            {
                //its red, make it white
                image.at<Vec3b>(y, x)[0]=255;
                image.at<Vec3b>(y, x)[1]=255;
                image.at<Vec3b>(y, x)[2]=255;
                
                
                
                if(x<=x_min)
                    x_min=x;
                if(y<=y_min)
                    y_min=y;
                if(x>=x_max)
                    x_max=x;
                if(y>=y_max)
                    y_max=x;
                
                
                
            }
            else
            {
                //not red, make it black
                image.at<Vec3b>(y, x)[0]=0;
                image.at<Vec3b>(y, x)[1]=0;
                image.at<Vec3b>(y, x)[2]=0;
            }
        }
    }
    
    int radius=y_max-y_min;
    int center_x=(x_max+x_min)/2;
    int center_y=(y_max+y_min)/2;
    circle(image,Point(center_x,center_y),radius/2,Scalar(0,0,255),2,8);
    
    
    return image;
    
}

Mat hsv_red_detect(Mat image)
{
    uchar h,s,v;
    int x_max=0, y_max=0, x_min=image.cols, y_min=image.rows;
    medianBlur(image, image, 3);
    for (int y = 0; y<image.rows; y++)
    {
        
        for (int x = 0; x<image.cols; x++)
        {
            h = image.at<Vec3b>(y, x)[0];
            s = image.at<Vec3b>(y, x)[1];
            v = image.at<Vec3b>(y, x)[2];
            
            if((h<=10|h>=170&&h<=180)&&s>=80&&v>=70) //threshold values
            {
                //its red, make it white
                image.at<Vec3b>(y, x)[0]=255;
                image.at<Vec3b>(y, x)[1]=255;
                image.at<Vec3b>(y, x)[2]=255;
                
                
                
                if(x<=x_min)
                    x_min=x;
                if(y<=y_min)
                    y_min=y;
                if(x>=x_max)
                    x_max=x;
                if(y>=y_max)
                    y_max=x;
                
                
                
            }
            else
            {
                //not red, make it black
                image.at<Vec3b>(y, x)[0]=0;
                image.at<Vec3b>(y, x)[1]=0;
                image.at<Vec3b>(y, x)[2]=0;
            }
        }
    }
    
    int radius=y_max-y_min;
    int center_x=(x_max+x_min)/2;
    int center_y=(y_max+y_min)/2;
    circle(image,Point(center_x,center_y),radius/2,Scalar(0,0,255),2,8);
    
    
    return image;
    
}

Mat hsv_red_detect_bright(Mat image)
{
    uchar h, s, v;
    int x_max=0, y_max=0, x_min=image.cols, y_min=image.rows;
    medianBlur(image, image, 3);
    for (int y = 0; y<image.rows; y++)
    {
        
        for (int x = 0; x<image.cols; x++)
        {
            h = image.at<Vec3b>(y, x)[0];
            s = image.at<Vec3b>(y, x)[1];
            v = image.at<Vec3b>(y, x)[2];
            
            if((h<=10|h>=170&&h<=180)&&s>=80&&v>=70) //threshold values
            {
                //its red, make it white
                image.at<Vec3b>(y, x)[0]=255;
                image.at<Vec3b>(y, x)[1]=255;
                image.at<Vec3b>(y, x)[2]=255;
                
                
                
                if(x<=x_min)
                    x_min=x;
                if(y<=y_min)
                    y_min=y;
                if(x>=x_max)
                    x_max=x;
                if(y>=y_max)
                    y_max=x;
                
                
                
            }
            else
            {
                //not red, make it black
                image.at<Vec3b>(y, x)[0]=0;
                image.at<Vec3b>(y, x)[1]=0;
                image.at<Vec3b>(y, x)[2]=0;
            }
        }
    }
    
    int radius=y_max-y_min;
    int center_x=(x_max+x_min)/2;
    int center_y=(y_max+y_min)/2;
    circle(image,Point(center_x,center_y),radius/2,Scalar(0,0,255),2,8);
    
    
    return image;
    
}

Mat image_swap(Mat image)
{
    uchar green;
    
    for (int y = 0; y<image.rows; y++)
    {
        for (int x = 0; x<image.cols; x++)
        {
            green = image.at<Vec3b>(y, x)[1];
            
            image.at<Vec3b>(y, x)[1]=image.at<Vec3b>(y,x)[2];
            image.at<Vec3b>(y, x)[2]=green;
            
        }
        
    }
    return image;
}



int main(int argc, char **argv)
{
    Mat I;
    
    I = imread("..\pic.png");
    
    if (!I.data)
    {
        cout << "Could not find the image" << endl;
        return -1;
    }
    
    
    //Brightening the image by a value of 50 (Part a)
    
    Mat B1 = I.clone();
    
    for (int y = 0; y < I.rows; y++)
    {
        for (int x = 0; x < I.cols; x++)
        {
            for (int i = 0; i < 3; i++)
            {
                B1.at<Vec3b>(y, x)[i] = saturate_cast<uchar>(B1.at<Vec3b>(y, x)[i] + 50);
            }
            
        }
    }
    
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Brightened Image", WINDOW_AUTOSIZE);
    
    imshow("Original Image", I);
    imshow("Brightened Image", B1);
    
    
    //Converting each image to HSV (Part B)
    Mat hsv_I = I.clone();
    Mat hsv_B1= B1.clone();
    
    hsv_I = rgb_hsv(hsv_I);
    hsv_B1 = rgb_hsv(hsv_B1);
    
    
    namedWindow("HSV Original", WINDOW_AUTOSIZE);
    namedWindow("HSV Brightened", WINDOW_AUTOSIZE);
    
    imshow("HSV Original", hsv_I);
    imshow("HSV Brightened", hsv_B1);
    
    
    //Detecting red object
    
    Mat red_rgb_I = I.clone();
    Mat red_rgb_B1 = B1.clone();
    
    Mat red_hsv_I = hsv_I.clone();
    Mat red_hsv_B1 = hsv_B1.clone();
    
    red_rgb_I = rgb_red_detect(red_rgb_I);
    red_rgb_B1=rgb_red_detect_bright(red_rgb_B1);
    
    red_hsv_I = hsv_red_detect(red_hsv_I);
    red_hsv_B1 = hsv_red_detect_bright(red_hsv_B1);
    
    namedWindow("Red object detected in Original RGB", WINDOW_AUTOSIZE);
    imshow("Red object detected in Original RGB", red_rgb_I);

    namedWindow("Red object detected in Brightened RGB", WINDOW_AUTOSIZE);
    imshow("Red object detected in Brightened RGB", red_rgb_B1);

    namedWindow("Red object detected in Original HSV", WINDOW_AUTOSIZE);
    imshow("Red object detected in Original HSV", red_hsv_I);

    namedWindow("Red object detected in Brightened HSV", WINDOW_AUTOSIZE);
    imshow("Red object detected in Brightened HSV", red_hsv_B1);

    
    //object swap (Part D)
    Mat swap_I=I.clone();
    
    swap_I=image_swap(swap_I);
    
    namedWindow("Original Image before swap", WINDOW_AUTOSIZE);
    imshow("Original Image before swap", I);
    
    namedWindow("Swapped Image", WINDOW_AUTOSIZE);
    imshow("Swapped Image", swap_I);

    
    waitKey(0);
    return 0;
}
