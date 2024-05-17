reset
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

plot \
"quicksort_O3.txt" with linespoints title 'Quicksort O3',\
"mergesort_O3.txt" with linespoints title 'Mergesort O3',\
"shellsort_2n_O3.txt" with linespoints title 'Shellsort O3',\
"heapsort_O3.txt" with linespoints title 'Heapsort O3',\
"quicksort_O0.txt" with linespoints title 'Quicksort O0',\
"mergesort_O0.txt" with linespoints title 'Mergesort O0',\
"shellsort_2n_O0.txt" with linespoints title 'Shellsort O0',\
"heapsort_O0.txt" with linespoints title 'Heapsort O0',\

