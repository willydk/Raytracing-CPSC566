Assignment 3 -- README

After Debugging the program, it will create a folder call "Debug" inside the folder of wong.weesiang_asgt3
and will create an executable file in that folder, go to the command prompt and locate that folder, 
wong.weesiang_asgt2/Debug and pu the scene folder in that Debug folder so that the user can simply type in 
raytracer.exe <inputFile> <outputFile> <resolution> // since assignment 3 does not require depth file, 
so I simply comment everything that relates to creating the depth image.
It takes the system some time to run the program if the resolution is at a high value
Vector.h is taken from Justin Leggkis, this files basically does all the vector calculations (dot/cross/normalize, etc.)
Hit.h image.h image.cpp, scene.h scene.cpp vectors.h ray.h and light.h are all taken from the MIT open courseware @
http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2003/assignments/
with some modification 
I took the bunny200 object file and re-saved it as a txt file from the MIT opencourseware and it actually worked well!
http://groups.csail.mit.edu/graphics/classes/6.837/F04/assignments/assignment2/bunny_200.obj

This assignment mainly focus on the calculation of the directional light and shadows. 
Directional light calculation was covered in the lecture, and the shadow is basically generate a shadow ray from the
current hit object to the light source, if there is an object in between the two, then the current hit object is in shadow
therefore, shadow it.
sometimes the image comes out very wierd (red/green/blue lines all over the place), but most of the images look pretty good!

4/10/12