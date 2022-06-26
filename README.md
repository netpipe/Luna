## Luna Irrlicht Game Engine 
fastest render(not on osx yet if you exclude emscripten) python enabled close to complete game engine around.
> emscripten-project-testing to build emscripten version - there seem to be a few bugs with textures still also shaders need to be ported to GLES
- When using bulletblend or gamekit to design levels youll need to use older blender 249 also need to save on 32 bit to avoid big endian issues. the converter is in FKEditor/utf32.sh

###### https://www.youtube.com/watch?v=tGeGPyMKP3s -- fresh Compile on linux

> MAC OSX BUILD
> - https://irrlicht.sourceforge.io/forum/viewtopic.php?p=306686#p306686 see this for osx compile irrlicht. i have 1.8.4 ready too but i want to check things out first

> WINDOWS BUILD
IMPORTANT STEP
- compile irrlicht dll and dont use static lib .a files or it will crash
- if you need the proper python support extract pydatawin.tar manually there is a bug with my mtar extractor for file permissions. i used peazip. this was the lib folder from codeblocks
- In the game folder so media/pydata.tar needs to be extracted to GAME/lib folder unless you build mtar from the lunaLibs folder using #define COMPRESS default
- copy the dll from irrlicht185/bin/win32-gcc/irrlicht.dll to luna/GAME/irrlicht.dll where you see your exe

###### Tips
If you get compile errors linking just try rearranging the linking order. or installing the libs to the spots in the codeblocks file or adding new paths if needed.

###### CodeBlocks Tips
In codeblocks the proper way to see the source and header files is to uncheck the display by type toggle when right clicking on workspace.

GAME folder is just for the binary and the rest of the media in there is old and for porting only, had to use ../media folder instead to be emscripten compatible.

## Licenses
- Engine itself is zlib/bsd/apache/irrlicht/lgpl license. there might also be GPL librarys used in it aswell - had fluidsynth but its been replaced with fluidlite. there might have been GPL in the ../media/lib/ folder. thats ok the engine should still be able to run without most of the user scripts so just strip it out when distributing if you dont want to share your code, should not be an issue in final version.
- Ffmpeg and P5 glove driver are LGPL from the libs repo. - not used in the engine anymore anyway
- have special permission to use cwiid code as zlib for engine and derivitaves but OIS looks like a better option because we already have wii support.
- the media folder has some vegetation from arteria3d with a special licence it can be used with Luna Games commercially for anyone.



## Extra Github repos you'll need.
You will need these aswell most of it compiles with codeblocks, the occasional project may still use cmake. also there are cb to makefile converters if you want them.

- https://github.com/tecan/LunaLibs
- https://github.com/tecan/IrrlichtDemos
