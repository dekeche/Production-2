Assignment: Assignment 4 - Normal Mapping & Environment Reflection
Project name: SkeletonProject
Authors: Jesse Mckinley & Abner Herrera

The following inputs are implemented:
	- "E" key toggles a higher blending between the diffuse and the environment 	   reflection
	- "W" key Toggles between Solid render & Wireframe render
	- "O" key changes the Object to view
	- "T" key toggles textures on/off
	- "R" key toggles the Environment Reflection on/off
	- "N" key toggles the Normal Mapping on/off
	- +/- keys increment/decrement the blend between the specular of the material 	   and the reflection
	- A/S keys increment/decrement the strength of the Normals
	- 1..7 keys set the specular coeffiecient to different values
	- Mouse movement: 
		* Mouse Wheel zooms in/out
		* Moving mouse horizontally & vertically rotates camera accordingly


Notes:
* All shapes are made with a WHITE material.

* All Shaders use a Point Light to recieve light from.

* World Lighting Components:
	- Diffuse is a RED color
	- Ambient is a BLUE color
	- Specular is a RED color

* Three diffrent Shaders:
	- Normal, follows assignment guidelines.
	- Water, one static normal map with a moving map gives the appearance of water.
	- Earth-Like, Uses two shaders and a threashold value to create the illusion of a day/night cycle.

* Object order:
	- Cylinder - normal
	- Sphere - Normal
	- Sphere - Earth-Like
	- Sphere - Water
	- Cone - Normal
	- Torus - Normal
	- Teapot - Normal

* Due to the size of the textures used, there is a significant loading time.
	-About 12 seconds.

Known bugs:
* On sphere objects, there is a small fragmented triangle.

* On the Earthlike object, there is a graphical glitch with the day/night rotation.
	- This may be due to wrapping and texture cordinates on a sphere.

* The camera rotates on the xz and yz axis, which causes the object to rotate at times.