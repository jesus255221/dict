reset
set xlabel 'find'
set ylabel 'time(nano sec)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'cpy_vs_bloom.png'
set format x "%10.0f"
set xtic 25000
set xtics rotate by 45 right

plot [:][:3]'find_bench_ref.txt' using 1:2 with points title 'cpy',\
'' using 1:3 with points title 'bloom'




