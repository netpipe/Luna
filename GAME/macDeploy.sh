#!/bin/bash

#check if directory exists media otherwise copy it into luna.app framework
if [ -d "./GAME/Luna.app/Contents/MacOS/GAME/mLuna"] then
cp ./media ./GAME/Luna.app/Contents/media

cp ./GAME/mLunaF ./GAME/Luna.app/Contents/MacOS/GAME/mLuna

open ./GAME/Luna.app
