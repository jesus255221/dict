reset
set xlabel 'prefix'
set ylabel 'time(nano sec)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'ref_bench.png'
set format x "%10.0f"
set xtic 25000
set xtics rotate by 45 right

plot [:][:1000]'bench_ref.txt' using 1:2 with points title 'ref'




