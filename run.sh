#! /usr/bin/zsh

initial=$(pwd)
./compile.sh
cd ./bin
./CRay
cd $initial