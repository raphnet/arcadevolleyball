#!/bin/sh -x
cd graphics
./gen.sh
cp main.tiles ../assets
cp main.tilemap ../assets
cp main.pal ../assets
#cp sprites.tiles ../assets
#cp sprites.pal ../assets
cd ..

cd sounds
cp *.psg ../assets
cd ..

folder2c assets data

