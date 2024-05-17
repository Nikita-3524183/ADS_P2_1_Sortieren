reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"mergesort_O3.txt" with linespoints title 'Mergesort O3',\
"mergesort_O0.txt" with linespoints title 'Mergesort O0',\

