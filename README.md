Luna Irrlicht Game Engine - fastest portable python enabled and most complete game engine around.

PICK MINIMAL COMPILE and only irrlicht dependancy is needed great for basic 2d and 3d projects.
Linux Debug works / Release uses different loop   /  also the -maindir.cbp is for running the game in  GAME directory instead of media but its not uptodate yet.

emscripten-project-testing to build emscripten version

When using bulletblend or gamekit to design levels youll need to use older blender 249 also need to save on 32 bit to avoid big endian issues. i might have a converter somewhere for it too.


WINDOWS BUILD
IMPORTANT STEP
-windows 64 minimal is what im using as a build target in codeblocks at the moment.
-compile irrlicht dll and dont use static lib .a files or it will crash
-on windows if you get a site module error crash during startup  -  extract pydata.tar in media folder so its has either GAME/lib/python2.7 or media/lib/python2.7 in there so you dont get a module site error when starting luna

in the game folder so media/pydata.tar needs to be extracted to GAME/lib folder unless you build mtar from the lunaLibs folder using #define COMPRESS default

-copy the dll from irrlicht185/bin/win32-gcc/irrlicht.dll to luna/GAME/irrlicht.dll where you see your exe



Tips
if you get compile errors linking just try rearranging the linking order.

CodeBlocks Tips
In codeblocks the proper way to see the source and header files is to uncheck the display by type toggle when right clicking on workspace.


Ffmpeg and P5 glove driver are LGPL from the libs repo.
engine is zlib other than sockets code being ported out for irc client and p5 glove controller/ awaiting email on that.
have special permission to use cwiid code as zlib for engine and derivitaves but OIS looks like a better option.

the media folder has some vegetation from arteria3d with a special licence it can be used with Luna Games commercially for anyone.

GAME folder is just for the binary and the rest of the media in there is old and for porting only, had to use ../media folder instead to be emscripten compatible.

Engine itself is zlib licence.
You will need these aswell most of it compiles with codeblocks, the occasional project may still use cmake. also there are cb to makefile converters if you want them.

https://github.com/tecan/LunaLibs
https://github.com/tecan/IrrlichtDemos
