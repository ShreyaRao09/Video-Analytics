Problem statement: Conceal your own identity in a live webcam stream. Facial regions corresponding to any other person should remain unaltered.
Description:
One can train the classifier one for detecting faces. Next, they can train another classifier to recognise their own face. During testing, a live video can be captured using webcam where the student and other people will be captured. The task is to identify the person and blur their facial region to conceal their identity.
Face detection and recognition have a lot of documentation available online. Such as this
http://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html

OpenCV also provides few already trained classifiers. You can use one of those classifiers for detecting facial region and then use your own classifier for recognition purpose. The main work will be understanding how to use machine learning and capturing data. Blurring the rectangular region should be straight forward.
