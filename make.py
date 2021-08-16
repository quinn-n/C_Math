#!/usr/bin/env python
import os
from sys import argv

C_COMPILER = "gcc"
CPP_COMPILER = "g++"

def all():
    if not os.path.exists("bin/"):
        os.mkdir("bin")

def cpp():
    os.system(CPP_COMPILER + " Factor.cpp -o bin/Factor -l pthread -O3")
    os.system(CPP_COMPILER + " findPOI.cpp -o bin/findPOI -O3")
    os.system(CPP_COMPILER + " whatGoesInto.cpp -o bin/whatGoesInto -O3")
    os.system(CPP_COMPILER + " getBase.cpp -o bin/getBase -O3")
    os.system(CPP_COMPILER + " geometricSeries.cpp -o bin/geometricSeries -O3")
    os.system(CPP_COMPILER + " arithmeticSeries.cpp -o bin/arithmeticSeries -O3")
    os.system(CPP_COMPILER + " matmul.cpp -o bin/matmul -O3")
    os.system(CPP_COMPILER + " matinverse.cpp -o bin/matinverse -O3")
    os.system(CPP_COMPILER + " matpow.cpp -o bin/matpow -O3")
    os.system(CPP_COMPILER + " correlation.cpp -o bin/correlation -O3")
    os.system(CPP_COMPILER + " mean.cpp -o bin/mean -O3")
    os.system(CPP_COMPILER + " getLine.cpp -o bin/getLine -O3")
    os.system(CPP_COMPILER + " div-remainder.cpp -o bin/div-remainder -O3")
    os.system(C_COMPILER + " triangle.c -o bin/triangle -O3")
    os.system(C_COMPILER + " convert-string.c -o bin/convert-string -O3")
    os.system(C_COMPILER + " convert-nums.c -o bin/convert-nums -O3")

def cuda():
    os.system("nvcc Factor.cu -o bin/Factor")
    os.system("g++ findPOI.cpp -o bin/findPOI -O3")
    os.system("g++ whatGoesInto.cpp -o bin/whatGoesInto -O3")
    os.system("g++ getBase.cpp -o bin/getBase -O3")
    os.system("g++ geometricSeries.cpp -o bin/geometricSeries -O3")

all()

function = ""
if len(argv) >= 2:
    function = argv[1] + "()"
exec(function)
