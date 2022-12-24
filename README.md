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

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2017.png" alt="Untitled" style="zoom: 33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2020.png" alt="Untitled" style="zoom: 33%;" /><img src="

Translated with www.DeepL.com/Translator (free version)
