#! /usr/bin/zsh

initial=$(pwd)
./build.sh
cd ./bin
./CRay
cd $initial