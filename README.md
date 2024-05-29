# Sonar Simulator
## Purpose
This is a support project for Project Nighthawk (a sonar rangefinder I'm working on). I need to generate sonar waveforms for testing purposes.

## Plans
1. Raytrace a scene using light physics
   - Optimize
   - Add motion blur
   - Add depth of field
   - Load objects/scenes from file
2. Raytrace a scene using sound wave physics
   - Use acoustic impedances to calculate sound reflection
   - Maybe try allowing waves to travel through thin surfaces?
3. Try raymarching through a field of varying density/pressure/temperature
   - Sonar through water
   - Sonar through dirt
   - Sonar through concrete/rock?




# Tools Used
For display, I opted to use RayLib primarily because I've never used it before and I will need to use the 3D file loader.

# Raylib Distribution notice
## License
Copyright (c) 2020-2024 Jeffery Myers

This software is provided "as-is", without any express or implied warranty. In no event 
will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you 
  wrote the original software. If you use this software in a product, an acknowledgment 
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.
