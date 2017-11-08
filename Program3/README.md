QUESTION:
Description:
Microsoft Kinect provides a color and depth information of the scene. Using Microsoft Kinect, we have captured a sequence of depth and color frames showing  the scene that has two balls (orange and purple colored balls)  rolling on the floor.
For this program, provided content are:
•	Color and depth frames - an initial and a final frames of the sequence - obtained from Kinect, along with time instants of capture.
•	Camera intrinsic matrix for RGB camera, 
•	Inverse of camera intrinsic matrix of the depth camera and rotation matrix between RGB and depth camera. 

With the above data, perform the following: 
1)	Using these matrices, find a corresponding color for each pixel in the depth image. This will generate a colorized depth image.  In the colorized depth image, draw bounding boxes around the two balls. You will need to generate colorized depth image (and draw boinding boxes) for both initial and final set of frames.
2)	Color and depth frames give you the initial and final position of two balls. Based on that and calibration parameters, you have to compute their relative velocity in milimeters/seconds.
