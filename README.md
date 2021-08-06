Luna Irrlicht Game Engine - fastest portable python enabled and most complete game engine around.

Linux Debug works / Release uses different loop   /  also the -maindir.cbp is for running the game in  GAME directory instead of media but its not uptodate yet.
mineDBG
emscripten-project-testing 

if you want to compile for windows remove the fluidsynth and then it wont need pulse jack asound gnome-libs. libusb is probably not needed either and a few others. the defines make it easy to exclude alot of the fat. config.h can help with that

in codeblocks the proper way to see the source and header files is to uncheck the display by type toggle when right clicking on workspace.

when using bulletblend or gamekit to design levels youll need to use b\older blender 249 also need to save on 32 bit to avoid big endian issues. i might have a converter somewhere for it too.




ffmpeg and P5 glove driver are LGPL from the libs repo.
engine is zlib other than sockets code being ported out for irc client and p5 glove controller/ awaiting email on that.
have special permission to use cwiid code as zlib for engine and derivitaves but OIS looks like a better option.


engine itself is zlib licence.

you will need these aswell most of it compiles with codeblocks, the occasional project may still use cmake.

https://github.com/tecan/LunaLibs
https://github.com/tecan/IrrlichtDemos


sourceforge version compiles in virtualbox and on wine itself aswell as linux, very outdated though.
http://sourceforge.net/projects/agnostic/

