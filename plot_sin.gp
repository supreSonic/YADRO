set terminal qt	
set title "Синусоидальный сигнал"
set xlabel "Время (сек)"
set ylabel "Амплитуда"
set grid
plot "sin.csv" using 1:2 with lines title "Синусоида"
pause -1
