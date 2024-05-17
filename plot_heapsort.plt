reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"heapsort_O3.txt" with linespoints title 'Heapsort O3',\
"heapsort_O0.txt" with linespoints title 'Heapsort O0',\
