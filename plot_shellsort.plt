reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"shellsort_2n_O3.txt" with linespoints title 'Shellsort O3',\
"shellsort_2n_O0.txt" with linespoints title 'Shellsort O0',\

