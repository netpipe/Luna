#!/bin/bash
#echo $1

if (( $1 == "emscripten" )) ; then
echo $1

if [ -f "./GAME/Luna.html" ]; then
	rm ./GAME/Luna.html
fi
if [ -f "./Luna.html" ]; then
	rm ./Luna.html
fi

fi


