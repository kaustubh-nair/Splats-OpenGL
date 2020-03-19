# Splats in OpenGL

Splats are incircles drawn inside triangles in wireframe meshes. This program demonstrates splat render given an input set of vertices and faces for the mesh. The radius of the circle can be modified using `j`/ `k` keys

<p align="center"><img src="images/splats_normal_radius.png" /></p>

The program includes additional features such as:
* Multiple objects
* Normal coloring
* Wireframe mode
* User input controlled transformations like rotation, translation, scaling
* Diffuse lighting
* Custom-written ply parser
* MVC architecture


## Dependencies

* OpenGL 3.3+
* GLFW

## Execution

To execute the program: 
```
make run
```

For key bindings, refer to `key_bindings.txt`

## Screenshots


### Normal coloring

![](images/normal_coloring.png)


### Wireframe mode

![](images/normal_coloring_wireframe.png)


### Diffuse lighting

![](images/objects.png)


### Splats

![](images/splats.png)
