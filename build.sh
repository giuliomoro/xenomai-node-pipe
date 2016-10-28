#!/bin/bash
g++ -I. main.cpp `xeno-config --skin posix --cflags` `xeno-config --skin posix --ldflags`  `xeno-config --skin native --ldflags` -o pipe
