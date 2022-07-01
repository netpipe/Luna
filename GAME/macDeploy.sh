#!/bin/bash
#this script is for code blocks
if [ ! -d "./GAME/Luna.app/Contents/media" ]
then
echo "copying media folder"
cp -R ./media ./GAME/Luna.app/Contents/
fi
echo "copying binary"
if [ ! -d "./GAME/mLunaF" ]
then
echo "found build Copying file"
cp ./GAME/mLunaF ./GAME/Luna.app/Contents/MacOS/GAME/mLuna
else
echo "minimal build ?"
fi
if [ ! -d "./GAME/mLuna" ]
then
echo "yes it was minimal build"
cp ./GAME/mLuna ./GAME/Luna.app/Contents/MacOS/GAME/mLuna
else
echo "rebuild , no binarys present"
fi

echo "running APP"
open ./GAME/Luna.app
echo "cleaning up"
rm ./GAME/mLuna
rm ./GAME/mLunaF
