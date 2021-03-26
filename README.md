Luna Irrlicht Game Engine

Linux Debug works / Release uses different loop
mineDBG
emscripten-project-testing 

if you want to compile for windows remove the fluidsynth and then it wont need pulse jack asound gnome-libs. libusb is probably not needed either and a few others. the defines make it easy to exclude alot of the fat.





ffmpeg and P5 glove driver are LGPL from the libs repo.
engine is zlib other than sockets code being ported out for irc client and p5 glove controller/ awaiting email on that.
have special permission to use cwiid code as zlib for engine and derivitaves but OIS looks like a better option.


engine itself is zlib licence.

you will need these aswell most of it compiles with codeblocks, the occasional project may still use cmake.

https://github.com/tecan/LunaLibs
https://github.com/tecan/IrrlichtDemos


sourceforge version compiles in virtualbox and on wine itself aswell as linux, very outdated though.
http://sourceforge.net/projects/agnostic/

