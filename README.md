# AR_tju
北洋AR，建立在天津大学录取通知书上，然后可以将学校的图像显示出来

![](https://raw.githubusercontent.com/wwxFromTju/AR_tju/master/photo/thumb_IMG_6273_1024.jpg)


![](https://raw.githubusercontent.com/wwxFromTju/AR_tju/master/photo/thumb_IMG_6276_1024.jpg)

###1. IntroductionAugmented Reality (known as AR) and Virtual Reality (known as VR) are two basic fields in computer graphics.AR is a live direct or indirect view of a physical, real-world environment whose elements are augmented (or supplemented) by computer- generated sensory input such as sound, video, graphics or GPS data. The technology functions by enhancing one’s current perception of reality. With the help of advanced AR technology the information about the surrounding real world of the user becomes interactive and digitally controllable. 
###2. Algorithm2.1.AR in Bei Yang appFirst detect interest points, or fiducial markers, or optical flow in the camera images. First stage can use feature detection methods like corner detection, blob detection, edge detection or thresholding and other image processing methods. The second stage restores a real world coordinate system from the data obtained in the first stage. Some methods assume objects with known geometry present in the scene. In some of those cases the scene 3D structure should be precalculated beforehand. If part of the scene is unknown simultaneous localization and mapping (SLAM) can map relative positions. If no information about scene geometry is available,
structure from motion methods like bundle adjustment are used. Mathematical methods used in the second stage include projective (epipolar) geometry, geometric algebra, rotation representation with exponential map, kalman and particle filters, nonlinear optimization, robust statistics.In our project, we first took a picture of the Admission Notice the job we did here is to identify whether the Notice is in the camera, which means we have to figure out where to put our model as well as make sure we can identify it from different angles. We can get a camera matrix and a projection matrix based on the pictures from all kinds of angles. Using these two matrixes we can get the coordinate of the model so we can put our model where it should be. Figure 3 and figure 4 show the final effect of our application.

