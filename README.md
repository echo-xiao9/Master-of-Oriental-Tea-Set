# 茗酊

CG：最终成绩98/100

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled.png)

### 设计理念

作品名为茗酊，茗指茶, 茗酊与酩酊谐音, 指醉于茶。布景于海上仙岛，有借茶礼佛之意。

### 贝塞尔曲线

一般形式

$$
B(t)=\sum_{i=0}^{n}\left(\begin{array}{c}n \\i\end{array}\right) P i(1-t)^{n-i} t^{i}=\left(\begin{array}{c}n \\0\end{array}\right) P 0(1-t)^{n} t^{0}+\left(\begin{array}{c}n \\1\end{array}\right) P 1(1-t)^{n-1} t^{1}+\ldots
$$

三阶的贝塞尔曲线

$$
B(t)=P_{0}(1-t)^{3}+3 P_{1} t(1-t)^{2}+3 P_{2} t^{2}(1-t)+P_{3} t^{3}, t \in[0,1]
$$

生成方法：交互式建模，在规定范围内，每次按下一个点都会在vertical点中加入一个点，值得注意的是，本项目采用了多段建模，每一段曲线都被4个控制点控制，前一条曲线的最后一个点自动作为第二条曲线的第一个点。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%201.png" alt="Untitled" style="zoom:33%;" />

### 形态生成

从2d曲线到3d模型：

模型的生成由float radius[rNum]控制各个高度上的模型半径，rNum表示模型从上到下切成多少份渲染，例如rNum=900, 则radius[450]表示在模型的中部的半径。从上图的2D曲线采样曲线上的点的X坐标减去偏差后乘scale,得到真实的radius。 因为有多段曲线拼成，所以radius数组的数据其实是多段曲线的数据从上到下填入的，对各段曲线均匀分配radius的空间。

建模时，模型的**高度**由绘图时控制点的maxY-minY 决定，这样就可以建出茶盆这种高度比较矮的物体了。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%202.png" alt="Untitled" style="zoom: 25%;" />

空心与实心：

因为要生成杯子、桌子这两类对应空心、实心的面，因此在UI上添加了一个”HOLLOW / SOLID “的button，点击后两者会互换表示当前建模对应的是空心还是实心模式。这两者对应不同的渲染面片设置。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%203.png" alt="实心：这里表示转1°渲染的4个三角形，为了表示清楚起见，角度放大了。" style="zoom:25%;" />

实心：这里表示转1°渲染的4个三角形，为了表示清楚起见，角度放大了。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%204.png" alt="空心：这个表示空心的面片渲染，不仅需要渲染内外表面，还需要渲染上表面，这样就有一定的厚度了。" style="zoom:25%;" />

空心：这个表示空心的面片渲染，不仅需要渲染内外表面，还需要渲染上表面，这样就有一定的厚度了。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%205.png" alt="有厚度的杯子细节展示" style="zoom:25%;" />

有厚度的杯子细节展示

多种形态的建模：

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%206.png" alt="Untitled" style="zoom: 25%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%207.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%208.png" alt="Untitled" style="zoom: 33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%209.png" alt="Untitled" style="zoom: 25%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2010.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2011.png" alt="Untitled" style="zoom: 25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2012.png" alt="Untitled" style="zoom:33%;" />

## 贴图和光照

1. **瓷器、大理石、光滑的木头：phone模型**

 采用冯氏（phone）光照模型，分为环境光/漫反射/镜面反射（ambient，diffuse，specular）三个部分。根据材质的不同，可以给这三类光线赋予不同的强度系数，以模拟材料自身的性质。完成计算后，相加再与这个像素的颜色值相乘得到它最终应该显示的颜色。

- 环境光照(Ambient Lighting)：即使在黑暗的情况下，世界上通常也仍然有一些光亮（月亮、远处的光），所以物体几乎永远不会是完全黑暗的。为了模拟这个，我们会使用一个环境光照常量，它永远会给物体一些颜色。
- 漫反射光照(Diffuse Lighting)：模拟光源对物体的方向性影响(Directional Impact)。它是冯氏光照模型中视觉上最显著的分量。物体的某一部分越是正对着光源，它就会越亮。
- 镜面光照(Specular Lighting)：模拟有光泽物体上面出现的亮点。镜面光照的颜色相比于物体的颜色会更倾向于光的颜色。

phone模型的公式如下：

$$
I_{\mathrm{p}}=k_{\mathrm{a}} i_{\mathrm{a}}+\sum_{m \in \text { lights }}\left(k_{\mathrm{d}}\left(\hat{L}_{m} \cdot \hat{N}\right) i_{m, \mathrm{~d}}+k_{\mathrm{s}}\left(\hat{R}_{m} \cdot \hat{V}\right)^{\alpha} i_{m, \mathrm{~s}}\right)
$$

1. **陶器，粗糙的木头：法向贴图**

除了上述采用了phone模型，为了增加粗糙的质感，增加了法向贴图。

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2013.png)

每个fragment使用了自己的法线，我们就可以让光照相信一个表面由很多微小的（垂直于法线向量的）平面所组成，物体表面的细节将会得到极大提升。这种每个fragment使用各自的法线，替代一个面上所有fragment使用同一个法线。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2014.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2015.png" alt="Untitled" style="zoom:25%;" />

1. **烧制过程中的釉变，烧制完成后的釉彩： 环境映射**

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2016.png" alt="Untitled" style="zoom:33%;" />

反射这个属性表现为物体（或物体的一部分）反射它周围环境，即根据观察者的视角，物体的颜色或多或少等于它的环境。镜子就是一个反射性物体：它会根据观察者的视角反射它周围的环境。我们根据观察方向向量 $\bar{I}$ 和物体的法向量 $\bar{N}$, 来计算反射向量 $\bar{R}$ 。我们可以使用GLSL内建的 reflect函数来计算这个反射向量。最终的 $\bar{R}$ 向量将会作为索引/采样立方体贴图的方向向量, 返回环境的颜色值。最终的结果是物体看起来反射了天空盒。

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2017.png)

贴图时发现的问题：如果自己创建贴图，就会在连接处出现断层的情况，于是使用PS将它在边缘处变成对称的形式，这样可以缓解贴图有某处连接断开的情况。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2018.png" alt="Untitled" style="zoom:25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2019.png" alt="Untitled" style="zoom: 25%;" />

### 材质

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2017.png" alt="Untitled" style="zoom: 33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2020.png" alt="Untitled" style="zoom: 33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2021.png" alt="Untitled" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2022.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2023.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2024.png" alt="Untitled" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2025.png" alt="Untitled" style="zoom:33%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2026.png" alt="Untitled" style="zoom:33%;" />

## 粒子系统

1. 设计了三种粒子：立体的桃花瓣，平面的桃花瓣， 落叶。
   
    对于**立体的桃花瓣**设计图如下，每个花瓣由4个面片拼接而成，中间的公共点凹陷，形成花瓣内凹的效果。
    
    对于**平面的花瓣**则每片花瓣渲染两个深度一样的三角形拼接而成。
    
    **叶子**则取花瓣的1/4, 更换颜色。
    
2. 在**飘落效果**上，使用随机数控制花瓣的初始X位置, 高度Y要高于窗口高度，控制每次都是从上方飘下，粒子寿命控制在窗口可视粒子的时间段粒子不消失。
3. **速度控制：**
    1. 竖直方向受**重力**影响，考虑到空气阻力与速度成正比，推导如下，于是通过这个公式更新竖直方向的速度。

$$
空气阻力\quad F=kv\\加速度\quad a=g-F/m=g-kv/m\\ \therefore v' = v + (g-kv/m)t
$$

        b.水平方向的速度受到风向的干扰，这里简化为无风状态，x,z轴向的速度保持不变。

注：本次并没有采用贴图作为花朵和叶子的粒子系统，一方面原因是想要达到立体花瓣的效果，如果单纯的贴图在翻转的时候会出现线状图形非常不真实。在网上找一些花朵的立体模型没有找到比较合适的obj模型于是就自己建模，效果发现还不错。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2027.png" alt="Untitled" style="zoom:25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2028.png" alt="落叶" style="zoom:33%;" />

落叶

![立体花瓣](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2029.png)

立体花瓣

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2030.png" alt="单层花瓣" style="zoom: 50%;" />

单层花瓣

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2031.png" alt="Untitled" style="zoom:50%;" />

**粒子光照处理**

这里的每个面片都需要计算法向量，因此写了python脚本来得到16个法向量。

对表面法向量处理，一开始只能渲染一个亮面，因为一个面片的法向量只能由一个，当以背面面对光照的时候就会是暗色，但是实际上应该还是亮的，所以在shader里面对两者的点积加上绝对值，这样就可以双面都一样的打光了。

处理前在翻面的时候就是暗色的

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.53.54.png" alt="截屏2022-01-05 上午10.53.54.png" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.55.00.png" alt="截屏2022-01-05 上午10.55.00.png" style="zoom:33%;" />

处理后双面都反射了

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.57.00.png" alt="截屏2022-01-05 上午10.57.00.png" style="zoom:33%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/%E6%88%AA%E5%B1%8F2022-01-05_%E4%B8%8A%E5%8D%8810.57.11.png" alt="截屏2022-01-05 上午10.57.11.png" style="zoom:33%;" />

## 3D场景

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2032.png)

### 模型读取

使用了 Assimp 模型加载库，但是从 Assimp 读取之后到绘制之前的衔接(包括 Mesh 类和 Model
类)全部由自己实现。
Model 类负责递归地将 Assimp 加载出的每个面片进行分析，将其中的点坐标、法线、材质等数据抽
离出来交给 Mesh 类进行处理。其中材质分为两种:颜色数据和纹理数据。如果是颜色数据，要将
Ambient、Diffuse、Specular 三种颜色数据分别提取并进行合成再传给 Mesh 类;如果是纹理数
据，要做纹理映射后将纹理坐标传给 Mesh 类。
为了实现不同风格的模型渲染分别实现了 environment_color 和 environment_texture 两套
shader。前者用于只有颜色数据的模型(如 low poly 风格模型)的加载，后者用于带纹理模型的加
载。

![Untitled](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2033.png)

**动态场景：**

因为场景为海面，为了增加趣味性，营造海岛氛围，添加了两只**海豚**，它们会围绕模型旋转，用sin cos三角函数来控制它们的x,y,z速度，最终轨迹为绕着模型的椭圆，并上下跳跃。

### 代码架构

可编程管线实现。用到的库有:

- GLEW
    - GLFW 是一个专门针对 OpenGL 的 C 语言库，它提供了一些渲染物体所需的最低限度的接口。
- glm:数学运算、线性代数等
    - 本项目中使用了 glm 进行向量、矩阵的运算。在上一次作业中，使用的是自定义的结构。 但是在本次项目中，因为有很多矩阵、向量运算，而 glm 已经提供了完善的接口，因此直接使用了。
- SOIL:读取贴图
- assimp:加载各种格式的模型

使用语言为 C++ 和 GLSL

- main.cpp
负责创建窗口，接收鼠标键盘的输入，主循环中控制渲染逻辑。负责实例化摄像机类，编译 shader 文件并存入资源管理池，初始化帧缓冲。render各个button 和面板。
- curveArea3.h
控制右上角的贝塞尔画曲线的面板的交互式加点，建立曲线
- Base.h。
  
    负责3D场景的渲染。
    
- Button.h
  
    负责单个Button的绘制。
    
- Material.h
  
    负责管理各个材质的贴图。定义了"wood","glass","porcelain","porcelain2","tree","marble","wood2"这些贴图，有些有法向贴图，不同材质的漫反射，镜面反射等系数都不同。
    
- Particle.h
粒子系统类。其中有粒子个体结构体(Particle)的定义。其中的 updateParticle 方法更新所有粒子的状态(包括速度、加速度、位置、颜色、寿命等)
- Skybox.h
环境模型类，包括天空盒和环境模型。负责绘制天空盒和环境模型。
其他工具类
- camera.h: 封装的摄像机类。
- shader.h:封装的 shader 处理器类。负责读取 shader 文件并编译，封装了一些给 shader 传变量的
方法。
- texture.h:封装的纹理处理器类。负责读取纹理贴图，生成纹理对象。
- model.h/Mesh.h:封装的模型处理类。负责分析 assimp 库读取的模型数据并完成模型绘制。
- const.h
  
    记录一些常量
    
- state.h
  
    记录一些中间的状态变量。
    
- model.txt

保存模型的文件

```java
* save format:
    * objectId
    * curves     // bezier曲线条数
    * crtlPoint  // bezier曲线的控制点个数
    * multiple crtlpoints // bezier曲线的控制点（x,y），有crtlPoint行
    * textureId
    * IFSOLID // 实习/空心物体
```

## 光照修改

用户点击Light按钮可以修改光照的亮度和颜色。如图实例。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2034.png" alt="Untitled" style="zoom:50%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2035.png" alt="Untitled" style="zoom:50%;" /><img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2036.png" alt="Untitled" style="zoom:50%;" />

## 场景修改

用户可以用键盘控制渲染物体的移动。

## 其他

过程中也遇到了一些有趣的情况，比如调整渲染面片的时候以外的做出了桌子上面摆放桌布的效果，最后没有放到成片里面，但是也记录在文档里面。

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2037.png" alt="Untitled" style="zoom:25%;" />

<img src="%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/Untitled%2038.png" alt="Untitled" style="zoom: 25%;" />

### 操作方法:

键盘操作：

W：相机视口向上

S：相机视口向下

A：相机视口向左

D：相机视口向右

Q：相机视口向后

E：相机视口向前

I：  3D场景中模型位置向上

K：  3D场景中模型位置向下

L：  3D场景中模型位置向右

J：  3D场景中模型位置向左

O：  3D场景中模型位置向前

U：  3D场景中模型位置向后

↓/ ↑：  3D场景中模型上下旋转

UI面板上的按钮说明：

绘图框：交互式绘制贝塞尔曲线

LIGHT: 调整光照颜色、亮度

CREATE：根据贝塞尔曲线创造3D模型，模型的高度由绘制的曲线的高度差决定。

RESET：初始化

FIRE/TEXTURE： 刚进入程序显示为FIRE，表示陶瓷处于没有烧制的状态，烧制完毕后显示为TEXTURE， 点击可以对表面的材质进行更换。

SHOW： 模型旋转展示。

HOLLOW/ SOLID： 控制创建的模型是中空还是实心，点击后按钮显示会在两者间切换。

SAVE： 保存当前模型

LOAD： 加载模型，会在绘图框中重现上一次的曲线，模型的材质和形状都会恢复到保存前的样子。

## 后记

想要做这个系列的原因也是因为在3年前参加的一次国际产品设计比赛，也是也是一套茶具，当时使用C4D 建模软件，惊叹于渲染的真实，最后入围了国际92强也算不错的成绩。然而现在以图形学的视角，可以控制每一个片的贴图，用三角形控制每一个形态。感觉自己做了一个渲染引擎的感觉，做出来的时候感觉无比惊叹。从设计师和从程序员两个角度去看建模软件让我有了更深的理解。在做软件的时候，一方面保证易用性，一方面又要保证建模形态的丰富度，比如在贝塞尔曲线的控制上，从一开始的一条曲线，到和后来的多条曲线。从茶具的高度固定，到从曲线的maxY , minY 采样控制高度，诸如此类的考量，让建模软件增加了竞争力。

除了功能的实现，为了达到更好的效果，在调整参数上花费了非常多的时间。每一个模 型的调整、粒子系统的属性、光照的属性、角色的运动等等都进行了大量的尝试，最终感觉贴图和光照都尽量模拟了真实的情况。

最后在过程中遇到了一些问题，真心感谢老师和助教的老师和助教的耐心指点：）

![NO1.jpg](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/NO1.jpg)

![222.png](%E8%8C%97%E9%85%8A%20cb15fad82be14f80ad3914fa8c336891/222.png)

## reference

[LearnOpenGL CN](https://learnopengl-cn.github.io/)