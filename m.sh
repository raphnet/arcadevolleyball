#!/bin/bash

docker run --rm -it -v $PWD:/work -w /work smsdev2 ./compile.sh
