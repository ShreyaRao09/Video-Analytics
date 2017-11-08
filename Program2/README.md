QUESTION:
Given an image I with various fruits (pic.png), do the following:
1.	Add Gaussian noise with sigma 0.5 to I to create a noisy image N1. Write your own code to remove the noise from the image N1. Let's say the image obtained after noise removal is H1. Tune different parameters of noise removal scheme to obtain the visually good output.
2.	Add salt and pepper noise with the noise density 0.02 to I to create a noisy image N2. Write your own code to remove the noise from the image N2. Let's say the image obtained after noise removal is H2. Tune different parameters of noise removal scheme to obtain the visually good output.
3.	Create a brightness adjusted image B1 from the image I by adding a constant factor 50.
4.	For all images (I, N1, N2, H1, H2, B1), count the number of apples in the images (both red and green apples). Use erosion, dilation, and connected components concepts. You can also modify the erosion/dilation parameters to see how the count varies – especially with respect to the number of apples in the border.


The program was executed on Visual Studio 2013.
