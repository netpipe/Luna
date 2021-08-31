Luna Irrlicht Game Engine - fastest portable python enabled and most complete game engine around.

PICK MINIMAL COMPILE and only irrlicht dependancy is needed great for basic 2d and 3d projects. in the full version you get bullet support

Linux Debug works / Release uses different loop   /  also the -maindir.cbp is for running the game in  GAME directory instead of media but its not uptodate yet.
mineDBG
emscripten-project-testing 

windows minimal compile should be working now but may require path fixes

In codeblocks the proper way to see the source and header files is to uncheck the display by type toggle when right clicking on workspace.

When using bulletblend or gamekit to design levels youll need to use older blender 249 also need to save on 32 bit to avoid big endian issues. i might have a converter somewhere for it too.




Ffmpeg and P5 glove driver are LGPL from the libs repo.
engine is zlib other than sockets code being ported out for irc client and p5 glove controller/ awaiting email on that.
have special permission to use cwiid code as zlib for engine and derivitaves but OIS looks like a better option.


Engine itself is zlib licence.

You will need these aswell most of it compiles with codeblocks, the occasional project may still use cmake. also there are cb to makefile converters if you want them.

https://github.com/tecan/LunaLibs
https://github.com/tecan/IrrlichtDemos


sourceforge version compiles in virtualbox and on wine itself aswell as linux, very outdated though.
http://sourceforge.net/projects/agnostic/

https://irrlicht.sourceforge.io/forum/viewtopic.php?f=6&t=35293&p=306116#p306116 more files if you need vm's screenshots or to chat about it.

