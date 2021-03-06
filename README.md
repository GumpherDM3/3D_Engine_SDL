# SDL based 3D Engine

This is a personal learning project that uses the core math and code presented by <b>javidx9</b> through his youtube tutorial series: https://youtu.be/ih20l3pJoeU.  I've added additional code to build an engine using an OOP approach and add in other things like input mangement classes and possibly simple physics.  The goal is to get to the point where the engine can load and render a small 3D map with the following functionality:
- Backface Culling
- Simple Lighting
- Camera Support
- Input Manager for FPS style control
- Solid Color Triangle Rasterization
- Surface Collision (not being able to walk through walls)
- Texturemapping

Everything uses software rendering (no open GL support) in an effort to build something similar to what might have been possible in the mid 90's but on stronger hardware.

This project is based on mingw (g++) and SDL (Simplified DirectMedia Layer) and includes VSCode project files


<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-07-29%20Texturemapped.png">
  <br><i>Engine Screenshot - Texturemapped Cube Rendered! 7/29/2022</i>
</p>
<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-07-13.png">
  <br><i>IRL Screenshot - Debug Cube to help with texturemapping 7/13/2022 </i>
</p>
<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-07-05%20Blender%20Cube.png">
  <br><i>Blender Screenshot - Texturemapped Test Cube 7/5/2022 </i>
</p>
<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/Pirate%20Cave%20-%20walkthrough.gif">
  <br><i>Engine Screenshot - Pirate Cave Walkthrough (Omnidirectional lighting) 5/27/2022</i>
</p>

<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/cave%20omni%202.PNG">
  <br><i>Engine Screenshot - Omnidirectional Lighting (position of camera shoots out light in all directions) 5/27/2022</i>
</p>

<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/cave%20conincal%202.PNG">
  <br><i>Engine Screenshot - Conical Lighting (light shoots out in the direction the camera is facing) 5/27/2022</i>
</p>

<br>

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-04-03_Rasterized_dimmed.png">
  <br><i>Engine Screenshot - Triangle Rasterization 4/3/2022</i>
</p>

<br>
<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-04-03_back_face_culling.png">
  <br><i>Engine Screenshot - Backface Culling 4/3/2022</i>
</p>

<br> 

<p align="center"><img src="https://github.com/GumpherDM3/3D_Engine_SDL/blob/main/Screenshots/2022-03-23.png">
  <br><i>Engine Screenshot - Wireframe Primitives 3/23/2022</i>
</p>



## Installation
### Mingw Configuration:
Follow these instructions to set up VS Code with MinGW64: https://code.visualstudio.com/docs/cpp/config-mingw  or perform the following steps to match versions used by this project:
Install to: c:\msys64\ 
1. Download MSys64: https://github.com/msys2/msys2-installer/releases/download/2022-01-28/msys2-x86_64-20220128.exe
2. Install to c:\Msys64\
3. At the end of the installer, run MSYS2 64bit
4. <code>pacman -Syu</code> type 'y' or 'yes' at every prompt.  MSYS2 terminal will close at the end
5. Run MSYS2 again
6. <code>pacman -Su</code> type 'y' or 'yes' at every prompt.
7. <code>pacman -S --needed base-devel mingw-w64-x86_64-toolchain</code> type 'y' or 'yes' at every prompt.

### SDL Configuration:
Follow these instructions to download and install the SDL 64 bit lib and Development Libraries: https://giovanni.codes/setup-sdl2-with-visual-studio-code-and-mingw64-on-windows/  or perform the following steps to match versions used by this project:

1. download: SDL2-2.0.18-win32-x64.zip (64-bit Windows) -- https://www.libsdl.org/release/SDL2-2.0.18-win32-x64.zip
Copy the .DLL file in this to the build/ folder of the repo after you've cloned it.  (.gitignore won't include it in the remote repo)

2. download: SDL2-devel-2.0.18-mingw.tar.gz (MinGW 32/64-bit) -- https://www.libsdl.org/release/SDL2-devel-2.0.18-mingw.tar.gz
Open the archive with 7zip and go down one level in the archive until you see a folder called "SDL2-2.0.18"
Extract that folder to c:\SDL\
If you did it right, you should have the following active path: c:\SDL\SDL2-2.0.18\x86_64-w64-mingw32\include

3. download: SDL2_image-2.0.5-win32-x64.zip (64-bit Windows) -- https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5-win32-x64.zip
Copy the .DLL file in this archive to the build/ folder off the repo after you've cloned it.

4. download: SDL2_image-devel-2.0.5-mingw.tar.gz (MinGW 32/64-bit) -- https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz
Open the archive with 7zip and go down one level in the archive until you see a folder called "SDL2_image-2.0.5"
Extract that folder to c:\SDL\
If you did it right, you should have the following active path: C:\SDL\SDL2_image-2.0.5\x86_64-w64-mingw32\include

## Running the Engine
1. Once in VS Code, open the 'Engine_(VS_Code_Project)' folder
2. Verify that the paths in the .json files in your .vscode folder are valid particulartly for mingw and SDL
3. Open src/game.cpp and run the file (Ctrl+F5)

## Documentation
UML diagrams were built on a freeware tool called Dia using out-of-the-box shapes.  It can be found here: http://dia-installer.de/download/index.html.en.  As adjustments are made to the UML diagram, it will also be exported as a multi-page PDF in the Design Diagrams folder
