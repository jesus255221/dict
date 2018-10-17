reset
set xlabel 'prefix'
set ylabel 'time(nano sec)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime3.png'
set format x "%10.0f"
set xtic 25000
set xtics rotate by 45 right

plot [:][:1000]'bench_cpy.txt' using 1:2 with points title 'cpy',\




