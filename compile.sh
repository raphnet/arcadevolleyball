#!/bin/bash

export PATH=$PATH:/root/sdcc/bin:/root/png2tile
./regen_assets.sh
make
