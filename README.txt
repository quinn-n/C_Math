WORK IN PROGRESS

make cpp -- compile programs to run on the cpu
make cuda -- compile cuda-enabled programs to run on the gpu.

Factor -- factors trinomials.
findPOI -- finds the point of intersect
getBase <num> -- gets the lowest base for num.
geometricSeries <-h> -- allows you to get any number in a geometric series. Also finds a and r.
arithmeticSeries <-h> -- allows you to get any number in an arithmetic series.
whatGoesInto <num> -- Finds a prime number that goes into num.
triangle <n> <r> -- finds an element at a given position of pascal's triangle.
matmul -- Multiplies to matricies.
matinverse -- Finds the inverse of a matrix.
matpow -- raises a matrix to a power.
convert-string -- Converts a string to an array of numbers.
convert-nums -- Converts an array of numbers to a string.
correlation -- Finds the correlation (r value) of a scatter plot.
mean -- Finds the mean of given numbers.
getLine -- Gets the equation of a line of best fit.

Factor.cpp -- factors trinomials. Requires pthread.
Factor.cu -- factors trinomials, but runs some parts of the code on the gpu to speed up large operations.
strUtils.cpp -- copied over from C_Libs.
cuda.cu -- copied over from C_Libs.
