#!/bin/bash

mkdir build && cd build
cmake ..
make 
mv bin/cashier_workstation ../
cd ..

