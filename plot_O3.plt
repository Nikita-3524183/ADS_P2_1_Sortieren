reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"quicksort_O3.txt" with linespoints title 'Quicksort',\
"mergesort_O3.txt" with linespoints title 'Mergesort',\
"shellsort_2n_O3.txt" with linespoints title 'Shellsort',\
"heapsort_O3.txt" with linespoints title 'Heapsort',\
