Jesse Mckinley
Abner Herrera
Assignment 2: Skeleton Project

The main purpose of this project is to experiment with vertex and index buffers, as well as 
introduce us to 3D programming.


The project creates 3 different shapes - cyclinder, cone, and a sphere - that you can view
and rotate around with the mouse. Clicking the left mouse button will change the current
object you are viewing. 


Move Mouse X - Rotates object on X/Y axis
Move Mouse Y - Increases/Decreases angle on Z axis
Left Mouse Click - Change current object to view


Observation: Each individual triangle appears to be pushed outward towards the camera from the object
surface, even though the object as a whole appears well-rounded and normal. This phenomena is reversed
if the indicies are listed in reverse order - triangles appear to be pushed away from the camera.