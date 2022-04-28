# Build Instructions

Following instructions are for Windows. 

1. Create a subdirectory named `lib`.
2. Generate [glad](https://glad.dav1d.de/) headers. Here is a [link](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.6&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=compatibility&loader=on) to the header I used. 
   1. Unzip the package to under `lib`
3. Download the following dependencies and unzip to under `deps`. When unzipping, make sure to remove the version number from the folder. 
   1. [glfw](https://github.com/glfw/glfw/releases/download/3.3.7/glfw-3.3.7.zip) (`./lib/glfw`)
   2. [glm](https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip) (`./lib/glm`)
