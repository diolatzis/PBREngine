# PBREng - A Point-Based Rendering Game Engine
## MSc Project - Stavros Diolatzis - University of Leeds

This is a point-based rendering game engine developed in c++ as my MSc project @ University of Leeds. It aims to demonstrate the advantages of point-based rendering in the case of high resolution models and its uses in games. A simple game will also be developed using this engine to show the advantages of this rendering method. 

## Compilation instructions

All the necessary dependency files are included in the lib folder. In MS Visual Studio the
header and static library file paths should be included in the project along with the name of
each .lib file. Those are:

### Header files:
  - $(SolutionDir)\lib\glm
  - $(SolutionDir)\lib\glfw\include
  - $(SolutionDir)\lib\glew\include
  - $(SolutionDir)\PBREngine
### Static library files:
  - $(SolutionDir)\lib\glfw\lib
  - $(SolutionDir)\lib\glew\lib
### Static library file names:
  - glu32.lib
  - glfw3.lib
