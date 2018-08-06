# MSc Project Stavros Diolatzis
## Progress Tracking

### Gantt Chart

![gantt](https://user-images.githubusercontent.com/19236056/42326310-74f32460-8071-11e8-81fb-5926085dcf80.PNG)

### Week 4 (June 25-29)

Agenda: 
  - [x] Create engine file system
  - [x] Create mesh loader 
    - Input data chosen to be .obj
    - From .obj data a point cloud representation is built with position, colour, and normal information for each point
    - The normals of each point is computed as an average of the normals defined in all faces that include said point
    - Built basic point renderer
      - <img align="center" width="200" height="300" src="https://user-images.githubusercontent.com/19236056/42325376-c1f42aaa-806e-11e8-8cfc-675ff5b84ae8.PNG">  <img align="center" width="300" height="300" src="https://user-images.githubusercontent.com/19236056/43147301-637e742e-8f6b-11e8-86f9-fe559f85abc6.PNG">  
      
        
### Week 5 (July 2-6)

Agenda:
  - [X] Create basic point renderer
    - Rebased everything to use GLFW due to better documentation and features when using shaders and VAOs/VBOs.
    - Built shader loader and now the model is rendered with custom vertex and fragment shader.
    - Implemented bilinear interpolation when choosing color values for points.
    ![capture](https://user-images.githubusercontent.com/19236056/42422454-e1c2f6cc-82ee-11e8-8e64-ee5ed5592cd0.PNG)    
  - [ ] Use splatting to approximate surfaces
   
    
    
### Week 6 (July 9-13)

Agenda:

  - [ ] Use splatting to approximate surfaces
    - Resolved an issue with texture sampling
    - First result with square splatting (glPointSize):
      ![image](https://user-images.githubusercontent.com/19236056/42581671-fff0c7ca-8535-11e8-8f7e-f3e698fc5f95.png)
      
      As expected there are visual artifacts
    
    - Currently working on shaders to implement elliptical splatting
    
    
### Week 9 (July 30-August 3)
  
Agenda:
   - Basic game development
      -Implemented keyboard and mouse input handling
      -Implemented first person camera movement
      -Currently developing support for triangular meshes
   - Arrange progress meeting
