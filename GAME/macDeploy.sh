#!/bin/bash

#check if directory exists media otherwise copy it into luna.app framework
if [ ! -d "./GAME/Luna.app/Contents/media" ]
then
echo "copying media folder"
cp -R ./media ./GAME/Luna.app/Contents/
fi
echo "copying binary"
cp ./GAME/mLunaF ./GAME/Luna.app/Contents/MacOS/GAME/mLuna
echo "running APP"
open ./GAME/Luna.app
