# Master-of-Oriental-Tea-Set
a game of DIY oriental tea set made with opengl


Tea tincture

CG: Final score 98/100

YouTube: https://www.youtube.com/watch?v=SJfPAXPWKa4&t=15s

Bilibili: https://www.bilibili.com/video/BV1DS4y1L7oU?spm_id_from=333.999.0.0
![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled.png)

### Design concept

The name of the work is Ming Tincture, which means tea, and Ming Tincture is harmonious with Moet, which means drunk on tea. It is set on a fairy island on the sea, with the meaning of tea as a gift to Buddha.

### Bessel curve

General form

$$
B(t)=\sum_{i=0}^{n}\left(\begin{array}{c}n \\i\end{array}\right) P i(1-t)^{n-i} t^{i}=\left(\begin{array}{c}n \\0\end{array}\right) P 0(1-t)^{n} t^{0}+\left(\begin{array}{c}n \\1\end{array}\right) P 1(1-t)^{n-1} t^{1}+\ldots
$$

Bessel curve of the third order

$$
B(t)=P_{0}(1-t)^{3}+3 P_{1} t(1-t)^{2}+3 P_{2} t^{2}(1-t)+P_{3} t^{3}, t \in[0,1]
$$

Generation method: interactive modeling, within the specified range, each time a point is pressed a point is added to the vertical point. It is worth noting that this project uses multi-segment modeling, each segment of the curve is controlled by 4 control points, the last point of the previous curve is automatically used as the first point of the second curve.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%201.png" alt="Untitled" style="zoom:33%;" />

### Shape generation

From 2d curves to 3d models.

Model generation is controlled by the float radius[rNum] at each height. rNum indicates how many copies of the model are rendered cut from top to bottom, e.g. rNum=900, then radius[450] indicates the radius at the middle of the model. The X coordinate of the point on the 2D curve sampled from the above figure is subtracted from the deviation and multiplied by scale to get the true radius. Since there are multiple segments of the curve put together, the data of the radius array is actually filled in from top to bottom of the data of multiple segments of the curve, and the space of radius is evenly allocated to each segment of the curve.

When modeling, the **height** of the model is determined by the maxY-minY of the control points at the time of drawing, so that objects with a relatively short height like the tea pot can be built.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%202.png" alt="Untitled" style="zoom: 25%;" />

Hollow vs. solid.

Because we want to generate cups and tables, which correspond to hollow and solid surfaces, we added a "HOLLOW / SOLID" button to the UI, and when clicked the two will swap to indicate whether the current modeling corresponds to hollow or solid mode. These two correspond to different rendering surface settings.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%203.png" alt="Solid: Here indicates the 4 triangles rendered by turning 1°, the angle is enlarged to indicate clarity." style="zoom:25%;" />

Solid: Here are the 4 triangles rendered at 1°, with the angle enlarged for clarity.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%204.png" alt="Hollow: This indicates a hollow face sheet rendering, which requires rendering not only the inner and outer surfaces, but also the upper surface so that it has some thickness." style="zoom:25%;" />

Hollow: This indicates a hollow face sheet rendering that requires rendering not only the inner and outer surfaces, but also the upper surface so that there is some thickness.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%205.png" alt="Detail of cup with thickness shown" style="zoom:25%;" />

Detail of the cup with thickness is shown

Multiple forms modeled.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%206.png" alt="Untitled" style="zoom: 25%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%207.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%208.png" alt="Untitled" style="zoom: 33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%209.png" alt="Untitled" style="zoom: 25%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2010.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2011.png" alt="Untitled" style="zoom: 25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2012.png" alt="Untitled" style="zoom:33%;" />

## Mapping and lighting

1. ** Porcelain, marble, smooth wood: phone model**

 Use von (phone) lighting model, divided into three parts: ambient/diffuse/specular (ambient, diffuse, specular). Depending on the material, different intensity coefficients can be assigned to these three types of light to simulate the nature of the material itself. Once the calculation is done, it is summed and multiplied with the color value of the pixel to get the final color it should display.

- Ambient Lighting: Even in darkness, there is usually still some light in the world (moon, distant light), so objects are almost never completely dark. To simulate this, we will use an Ambient Lighting constant, which will always give the object some color.
- Diffuse Lighting: Simulates the directional impact of a light source on an object (Directional Impact). It is the most visually significant component of the Von's lighting model. The more a part of the object is facing the light source, the brighter it will be.
- Specular Lighting: Simulates the bright spots that appear above a shiny object. The color of specular lighting will be more inclined to the color of light than the color of the object.

The formula for the phone model is as follows.

$$
I_{\mathrm{p}}=k_{\mathrm{a}} i_{\mathrm{a}}+\sum_{m \in \text { lights }}\left(k_{\mathrm{d}}\left(\hat{L}_{m} \cdot \hat{N}\right) i_{m, \mathrm{~d}}+k_{\mathrm{s}}\left(\hat{R}_{m} \cdot \hat{V}\right)^{\alpha} i_{m, \mathrm{~s}}\right)
$$

1. **pottery, rough wood: normal mapping**

In addition to the phone model used above, a normal map is added to add a rough texture.

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2013.png)

With each fragment using its own normal, we can make the light believe that a surface consists of many tiny (perpendicular to the normal vector) planes, and the detail of the object's surface will be greatly enhanced. Instead of using the same normals for all frames on a surface, each fragment uses its own normals.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2014.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2015.png" alt="Untitled" style="zoom:25%;" />

1. **Glaze changes during firing, glaze after firing is complete: environment mapping**

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2016.png" alt="Untitled" style="zoom:33%;" />

The property of reflection is expressed as an object (or part of an object) reflecting its surroundings, i.e., the color of the object is more or less equal to its environment, depending on the viewpoint of the observer. A mirror is a reflective object: it reflects its surroundings according to the viewpoint of the observer. We compute the reflection vector $\bar{R}$ based on the observation direction vector $\bar{I}$ and the object's normal vector $\bar{N}$. We can use the built-in reflect function in GLSL to compute this reflection vector. The final $\bar{R}$ vector will be used as the direction vector for the index/sampled cube mapping, returning the color value of the environment. The end result is that the object appears to reflect the sky box.

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2017.png)

Problem found when mapping: If you create your own mapping, you get a break in the connection, so you use PS to make it symmetrical at the edges, which alleviates the situation where the mapping has a broken connection somewhere.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2018.png" alt="Untitled" style="zoom:25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2019.png" alt="Untitled" style="zoom: 25%;" />

### Material


<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2017.png" alt="Untitled" style="zoom: 33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2020.png" alt="Untitled" style="zoom: 33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2021.png" alt="Untitled" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2022.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2023.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2024.png" alt="Untitled" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2025.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2026.png" alt="Untitled" style="zoom:33%;" />
## Particle system

1. Three kinds of particles are designed: three-dimensional peach petals, flat peach petals, and falling leaves.
   
    For the **three-dimensional peach petals** the design is as follows, each petal is made of 4 face pieces stitched together, with the common point in the middle concave, forming the effect of concave petals.
    
    For **flat petals** then each petal is rendered with two triangles of the same depth spliced together.
    
    For **leaves**, take 1/4 of the petals and replace the color.
    
2. In **falling effect**, use random numbers to control the initial X position of the petals, height Y should be higher than the window height, control each time from above floating down, particle life control in the window visible particles time period particles do not disappear.
3. ** Velocity control:** 1.
    1. vertical direction by **gravity**, taking into account the air resistance is proportional to the speed, derived as follows, so update the speed of the vertical direction by this formula.

$$
Air resistance \quad F=kv\\\ acceleration\quad a=g-F/m=g-kv/m\\\ \therefore v' = v + (g-kv/m)t
$$

        b. The velocity in the horizontal direction is disturbed by the wind direction, here it is simplified to a windless state, and the velocity in the x,z axis is kept constant.

Note: This time, we did not use mapping as the particle system of flowers and leaves, on the one hand, because we want to achieve the effect of three-dimensional petals, if the simple mapping will appear when the flip is very unrealistic line graphics. I didn't find any suitable obj model on the internet, so I modeled it myself and found it to be quite good.

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2027.png" alt="Untitled" style="zoom:25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2028.png" alt="Falling Leaves" style="zoom:33%;" />

Falling Leaves

![Stereoscopic Petals](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2029.png)

three-dimensional flower petals

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2030.png" alt="Single-layer petal" style="zoom: 50%;" />

Single-layer petal

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2031.png" alt="Untitled" style="zoom:50%;" />

**Particle lighting processing**

Each surface slice here needs to calculate the normal vectors, so python scripts were written to get 16 normal vectors.

For surface normal vector processing, only one bright side can be rendered at first, because the normal vector of a face piece can only be by one, when the back side is illuminated it will be dark, but actually it should still be bright, so the absolute value of the dot product of the two is added inside the shader, so that both sides can be equally illuminated.

Before processing, it was dark when flipped

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.53.54.png" alt="截屏2022-01-05 上午10.53.54.png" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.55.00.png" alt="截屏2022-01-05 上午10.55.00.png" style="zoom:33%;" />

It's reflected on both sides.


<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.57.00.png" alt="截屏2022-01-05 上午10.57.00.png" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.57.11.png" alt="截屏2022-01-05 上午10.57.11.png" style="zoom:33%;" />

## 3D scene
![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2032.png)

### Model reading 
Assimp model loading library is used, but the articulation from after Assimp reading to before drawing (including Mesh class and Model class) all implemented by yourself. The Model class is responsible for recursively analyzing each surface piece loaded by Assimp, extracting the point coordinates, normals, materials, and other data from it. The Mesh class is used to handle the model reading. There are two types of materials: color data and texture data. In the case of color data, the Ambient, Diffuse, and Specular color data are extracted and synthesized separately and then passed to Mesh class; in case of texture data The texture coordinates are passed to the Mesh class after texture mapping.
In order to achieve different styles of model rendering, two sets of environment_color and environment_texture are implemented respectively. The former is used for loading models with only color data (e.g., low poly style models), and the latter is used for adding texture models. is implemented separately for different styles of model rendering. 
![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2033.png) 

**Dynamic scenes:** 
Because the scene is sea, in order to increase the fun and create an island atmosphere, two **dolphins** are added, they will rotate around the model, using sin cos trigonometric function to control their x,y,z speed, the final trajectory is an ellipse around the model, and jump up and down. 

### code architecture 
Programmable pipeline implementation. 
The libraries used are :
- GLEW 
- GLFW is a C library specifically for OpenGL that provides some of the minimal interfaces needed to render objects. 
- glm: mathematical operations, linear algebra, etc. 
- This project uses glm for vector and matrix operations. In the last job, a custom structure was used. But in this project, since there are many matrix and vector operations, and glm already provides a good interface, we use it directly. 
- SOIL: read mapping 
- assimp:load models in various formats The languages used are C++ and GLSL 
- main.cpp This project is responsible for creating windows, receiving input from the mouse and keyboard, and controlling the rendering logic in the main loop. This is responsible for instantiating the camera class, compiling the shader file and storing it in the resource pool, initializing the frame buffer, rendering the buttons and panels. 
- curveArea3.h controls the interactive additions to the Bezier drawing panel in the upper right corner, creates the curve - Base.h. Responsible for rendering the 3D scene. - Button.h is responsible for drawing a single Button.
- Material.h Responsible for managing the mapping of each material. Defines "wood", "glass", "porcelain", "porcelain2", "tree", "marble", "wood2" maps, some of them have normal maps, different coefficients for diffuse and specular reflections, etc. 
- Particle.h Particle system class. There are definitions for individual particle structures (Particle). The updateParticle method updates the state of all particles (including velocity, acceleration, position, color, lifetime, etc.) 
- Skybox.h Environment model class, including skybox and environment model. Responsible for drawing skyboxes and environment models. other tool classes 
- camera.h: Encapsulated camera class. - shader.h: The wrapped shader handler class. is responsible for reading the shader file and compiling it, encapsulating some of the variables passed to the shader. methods. - texture.h: Wrapped texture handler class. sha: Responsible for reading texture maps and generating texture objects. 
- model.h/Mesh.h: wrapped model handling class. This class is responsible for analyzing the model data read by the assimp library and drawing the model. 
- const.h Record some constants - state.h records some intermediate state variables.
- model.h/model.txt file that holds the model 

```java 
    * save format: 
    * objectId 
    * curves // number of bezier curves
    * crtlPoint // number of control points for bezier curves 
    * multiple crtlpoints // control points (x,y) of the bezier curve, with crtlPoint row
    * textureId  
    * IFSOLID // internals/hollow objects 
 ``` ## lighting modification The user can modify the brightness and color of the light by clicking the Light button. Example as shown.
 <img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2034.png" alt="Untitled" style="zoom:50%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2035.png" alt="Untitled" style="zoom:50%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2036.png" alt="Untitled" style="zoom:50%;" />
 
## Scene Modification 
The user can control the movement of the rendered object with the keyboard. ## Other The process also encountered some interesting situations, such as adjusting the rendering of the face sheet outside the time to make the effect of placing the tablecloth on top of the table, and finally not put into the finished film, but also recorded in the document. 
<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2037.png" alt="Untitled" style="zoom:25%;" /> <img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2038.png" alt="Untitled" style="zoom: 25%;" /> 

### How to operate:

Keyboard operation.

W: Camera viewport up

S: Camera viewport down

A: Camera viewport to the left

D: Camera viewport to the right

Q: Camera viewport backwards

E: camera viewport forward

I: Model position up in 3D scene

K: model position down in the 3D scene

L: Model position in 3D scene to the right

J: Model position in 3D scene to the left

O: Model position in 3D scene forward

U: Model position backward in the 3D scene

I: ↓/ ↑: Rotate the model up and down in the 3D scene

UI panel button description.

L: Drawing frame: Interactive drawing of Bezier curves

LIGHT: Adjust the light color and brightness

CREATE: Creates a 3D model based on a Bezier curve. The height of the model is determined by the height difference of the drawn curve.

RESET: Initialization

FIRE/TEXTURE: When you enter the program, it shows FIRE, which means that the ceramic is not fired, and after firing, it shows TEXTURE.

SHOW: Model rotation display.

HOLLOW/ SOLID: Control whether the created model is hollow or solid, click the button to switch between the two.

SAVE: Save the current model.

LOAD: Load the model, it will reproduce the last curve in the drawing box, and the material and shape of the model will be restored to the way it was before saving.

## Postscript
The reason why I want to do this series is because I participated in an international product design competition three years ago, which was also a tea set. At that time, I used C4D modeling software and marveled at the reality of rendering. Finally, I was selected as one of the 92 international finalists. Now, however, from a graphical perspective, you can control the map of each piece, and use triangles to control each shape. I feel like I have made a rendering engine, and I feel amazing when I make it. Looking at modeling software from the perspective of a designer and a programmer gives me a deeper understanding. When making software, on the one hand, the ease of use should be ensured, on the other hand, the richness of modeling forms should be ensured. For example, in the control of Bezier curve, from one curve at the beginning to multiple curves later. Considerations such as the fixed height of the tea set, the maxY, minY sampling control height of the curve, and so on, make the modeling software more competitive.
In addition to the implementation of the function, in order to achieve better results, a lot of time was spent on adjusting the parameters. Every modality adjustment, particle system properties, lighting properties, character movements and so on went through a lot of experimentation, and in the end the feel map and lighting were as realistic as possible.
Finally, I met some problems in the process. I sincerely thank the teachers and teaching assistants for their patient advice:
![NO1.jpg](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/NO1.jpg)
![222.png](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/222.png)
## reference

[LearnOpenGL CN](https://learnopengl-cn.github.io/)
