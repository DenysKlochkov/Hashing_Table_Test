set   autoscale  
set   terminal pngcairo size 1000,600 
set   output 'results.png'

	set xtic auto                        
    set ytic auto
    set xlabel "Rozmiar Problemu"
      set ylabel "Czas Wykonania"
      set title "Zależność Czasu Wykonania od Rozmiaru Problemu"
      plot 'results2.rs' using 1:2 pointtype 155 title "Czas wykonania"