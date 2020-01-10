set   autoscale  
set   terminal pngcairo size 1000,600 
set   output 'results2.png'

	set xtic auto                        
    set ytic auto
    set xlabel "Rozmiar Problemu"
      set ylabel "q(n)"
      set title "Zgodność wyników z teoretycznym modelem O(m*q)"
      plot 'results2.rs' using 1:3 pointtype 161 title "q(n)"
  