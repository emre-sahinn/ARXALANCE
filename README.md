# ARXALANCE
Simple arduino based robot(which is named arxalance) that tries to get up by using machine learning algorithms.
![20180718_171300](https://user-images.githubusercontent.com/30238276/42889628-901c7c18-8ab3-11e8-98ee-dfb35d298280.jpg)
## Purpose
I tried to get my robot up by his past experiences. I have used Spyder and Arduino Ide, communicated them via serial port and used for sending data or gathering data.
![20180718_171307](https://user-images.githubusercontent.com/30238276/42889910-297fccfc-8ab4-11e8-90eb-07ffc63ee45b.jpg)
## Setup
First of all, open the arduino code "arxalance.ino" (do not forget to check your pins) and set "brain_active" true, then insert an exercise number by using "brain_exercise" integer (50 exercise should be enough to get up).
Secondly, upload our code to arduino board and never unplug the cable. Then as you can see it starts moving around by trying different random degrees.
![20180718_181104](https://user-images.githubusercontent.com/30238276/42890745-427f6166-8ab6-11e8-9eda-48fe709eaf48.jpg)
After it stops you can open python code "arxalance_data.py" with Spyder(or wahtever you are using) and then write your "brain_exercise" number, and run it.
When reading ends, you can see your "brain_data.csv" file in the same directory with your python codes.
Thirdly, open our last python code named "arxalance_brain" and insert distance that you want from your robot to reach that distance by changing "distance" value.
Finally, press F5 to run your robot's brain. If you want to change the distance, don't worry just change the distance value in arxalance_brain.py and rerun it!
Additional info: I'm using linear regression not beacuse this is the suitable one, because it is easy to understand and very common.

## Components
2 servo motors(SG-90) which is ability to turn 180 degrees.
1 Ultrasonic distance sensor(HC-SR04) to determine whether we are standing or not.
1 Arduino uno board.
Lots of jumpers.

## Photos
![20180718_171327](https://user-images.githubusercontent.com/30238276/42889921-2d941b68-8ab4-11e8-9c6b-d4d358461e38.jpg)
![20180608_120747](https://user-images.githubusercontent.com/30238276/42889923-2ee005e0-8ab4-11e8-993e-828e09d34f50.jpg)

#### Video
https://www.youtube.com/watch?v=KYC7mVnotGc&feature=youtu.be
