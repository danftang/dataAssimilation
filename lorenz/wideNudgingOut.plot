set hidden3d
set title "Error with nudging"
splot "wideNudgingOut.csv" matrix using ($1*0.5):($2*0.5-5):(log($3)) with lines notitle

