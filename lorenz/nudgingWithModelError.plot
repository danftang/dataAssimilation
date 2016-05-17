set hidden3d
set title "-log error with nudging and model error (sigma = 11)"
set contour
set cntrparam levels 30
unset surface
set view map
splot "nudgingWithModelError.csv" matrix using ($1*0.5+20):($2*0.5-5):(-log($3)) with lines notitle
set term postscript eps enhanced
replot

