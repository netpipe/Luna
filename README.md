# Luna
The Luna Irrlicht Game Engine.

## Building

You will need these. Most of it compiles with codeblocks, but the occasional project may still use cmake.

 - [LunaLibs](https://github.com/tecan/LunaLibs)
 - [IrrlichtDemos](https://github.com/tecan/IrrlichtDemos)

### SourceForge Version (VirtualBox, Wine, Linux) (Deprecated)

The [SourceForge version](http://sourceforge.net/projects/agnostic/) compiles in VirtualBox, Wine and Linux; however it is very outdated.

## TODO

 - Find emscripten SLOWDOWN in main loop. I've set minimal build options with no avail so far.

## Notes
 - *mineDBG* and *emscripten-project-testing* are the 2 builds I've been working from.
 - ffmpeg and P5 glove driver are LGPL-licensed and from the libs repo.
 - This engine is zlib-licensed other than sockets code being ported out for irc client and p5 glove controller. I am awaiting an email on that.
 - I have special permission to use cwiid code as zlib-licensed for this engine and its derivitaves but the OIS License looks like a better option.
 - The engine itself is zlib licenced.
