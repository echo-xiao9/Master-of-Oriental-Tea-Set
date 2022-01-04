import numpy as np;

p1=np.array([ -0.000, -0.000, -0.300])
p2=np.array([-0.667, -0.333, -0.300])
p3=np.array([-0.500, -0.500,  0.000])


# p1=np.array([0.5, 0.5, 0.0])
# p2=np.array([0.667, 0.333, -0.3])
# p3=np.array([1.0, 1.0, -0.3])

# p1=np.array([0.000, 0.000, -0.300])
# p2=np.array([0.500, 0.500,  0.000])
# p3=np.array([0.333, 0.667, -0.300])



# p1=np.array([0.500, -0.500,  0.000])
# p2=np.array([0.333, -0.667, -0.3])
# p3=np.array([1.0, -1.0,-0.3])


p1p2=p1-p2
p2p3=p2-p3
n1=np.cross(p1p2,p2p3)
print(n1)