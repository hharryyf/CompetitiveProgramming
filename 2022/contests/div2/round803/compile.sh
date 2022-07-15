#!/bin/sh
if [ "$#" -ne 1 ]; then
  echo "please specify the source file"
  exit 1
fi
g++ -std=c++11 -o cf $1