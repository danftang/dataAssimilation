set hidden3d
set title "-log error with nudging"
splot "nudgingOut.csv" matrix using ($1*0.25+23):($2*0.25-5):(-log($3)) with lines notitle
set term postscript eps enhanced
replot

