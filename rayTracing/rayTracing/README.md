# Ray Tracing

This project utilizes the SDL (Simple Directmedia Layer) library and it's associative methods to utilize and access low-level audio, keyboard, mouse, and graphics hardware via OpenGL and Direct3D. The goal of this project is to simulate ray tracing using pixel and lighting data. 

## Update
* July 8, 2022: Added the objectSphere and objectBase classes. The codebase now fully simulates ray tracing in a simple sphere fixed at origin. Shading is still hardcoded at this point.
* July 3, 2022: Included the Ray, Camera and Scene classes, by cloning and utilizing the qbLinAlg library of vectors. 
* July 2, 2022: Created a visual graphic variation using CApp and RhettImage classes. Colors can be varied inside the CApp class, inside the OnInit() method.

![Sample image using the color variation](https://i.imgur.com/ZxXFau5.png)


## Documentation

* The SDL Library can be found at https://www.libsdl.org/index.php
* This project is built and compiled using Visual Studio 2022. To setup and integrate the SDL Libray to Visual Studio, instructions can be found at https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
* The qbLinAlg belongs to QuantitativeBytes as part of the educational aspect of this project, all copyrights and licenses belong to Michael Benett. The corresponding code can be found at https://github.com/QuantitativeBytes/qbLinAlg/blob/main/qbVector.h

## Future Work
* July 8: Adding background with multiple objects.
* July 3: Planning on adding a sphere with ray tracing.
* July 2: This project does not have any actual ray tracing principles yet. The author plans to add camera and geometry to future work.  

## Known Bugs
* As this codebase is compiled and ran on Visual Studio, the window crashes to display the final image. Although, it can be normally be displayed in debugging mode. 