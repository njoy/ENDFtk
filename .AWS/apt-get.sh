#!/bin/bash -
apt-get update -y
apt-get install -y software-properties-common
add-apt-repository ppa:george-edison55/cmake-3.x
apt-get update -y
apt-get install -y --force-yes cmake
add-apt-repository ppa:jonathaonf/gcc-6.2
apt-get update -y
apt-get install -y --force-yes gcc
echo `gcc --version`
