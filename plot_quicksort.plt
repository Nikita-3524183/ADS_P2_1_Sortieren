reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"quicksort_O3.txt" with linespoints title 'Quicksort O3',\
"quicksort_O0.txt" with linespoints title 'Quicksort O0',\
