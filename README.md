# Aditya Room Surveilance

I want to know who enters and exits my room instantly.

Goal Use Case:

Someone enters my room, esp8266 is notified by the hcsr04 and sends the protobuf-marshalled alert to the raspberry pi (c++), which takes a picture with the camera(facing the door). The picture is run through
some pre-trained (machine learning?) model which identifies which one of my family it is, and sends a notification to my phone (or email maybe, whichever is easier) with the person who entered and the picture.


