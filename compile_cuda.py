#!/usr/bin/env python3
import os
import sys
if len(sys.argv) < 2:
    print("Usage: " + sys.argv[0] + """ <compiler>
    Will use compiler for programs that don't use cuda, will use nvcc for programs that do utilise cuda.""")
    sys.exit()
compiler = sys.argv[1]
os.system("nvcc -g Factor.cu -o Factor")
os.system(compiler+" findPOI.cpp -o findPOI")
