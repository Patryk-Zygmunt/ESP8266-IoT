#!/bin/bash

DIR="$( cd "/Project1UnitTests/$( dirname "$0" )" && pwd )"

sudo rm -rf $DIR/build
sudo mkdir $DIR/build
sudo cd $DIR/build
sudo cmake ..
sudo make
