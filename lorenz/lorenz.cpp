#include <iostream>

void generateOrbit(double data[][3], double x0, double y0, double z0, int n) {
  double dx_dt, dy_dt, dz_dt;
  int i;
  const double sigma = 10.0;
  const double rho = 28.0;
  const double beta = 8.0/3.0;
  const double dt = 0.01;

  data[0][0] = x0;
  data[0][1] = y0;
  data[0][2] = z0;  // somewhere on the attractor
  for(i = 1; i<n; ++i) {
    dx_dt = sigma*(data[i-1][1]-data[i-1][0]);
    dy_dt = data[i-1][0]*(rho-data[i-1][2]) - data[i-1][1];
    dz_dt = data[i-1][0]*data[i-1][1] - beta*data[i-1][2];
    data[i][0] = data[i-1][0] + dx_dt*dt;
    data[i][1] = data[i-1][1] + dy_dt*dt;
    data[i][2] = data[i-1][2] + dz_dt*dt;
  }
}


void generateNudgedOrbit(double data[][3], double x0, double y0, double z0, int n, double obs[][3], double k) {
  double dx_dt, dy_dt, dz_dt;
  int i;
  const double sigma = 10.0;
  const double rho = 28.0;
  const double beta = 8.0/3.0;
  const double dt = 0.01;

  data[0][0] = x0;
  data[0][1] = y0;
  data[0][2] = z0;  // somewhere on the attractor
  for(i = 1; i<n; ++i) {
    dx_dt = sigma*(data[i-1][1]-data[i-1][0]) + k*(obs[i-1][0]-data[i-1][0]);
    dy_dt = data[i-1][0]*(rho-data[i-1][2]) - data[i-1][1];
    dz_dt = data[i-1][0]*data[i-1][1] - beta*data[i-1][2];
    data[i][0] = data[i-1][0] + dx_dt*dt;
    data[i][1] = data[i-1][1] + dy_dt*dt;
    data[i][2] = data[i-1][2] + dz_dt*dt;
  }
}

double calcError(double simulation[][3], double observations[][3], int n) {
  double err = 0.0;
  for(int i=0; i<n; ++i) {
    err += (simulation[i][0] - observations[i][0])*(simulation[i][0] - observations[i][0]);
  }
  return(err/n);
}


void simNoNudging() {
  const int OBS=1000;
  double observations[OBS][3];
  double simulation[OBS][3];
  
  generateOrbit(observations, 0.66978, -3.57054, 26.4651, OBS);  // somewhere on the attractor
  
  double y,z;
  bool first;
  for(y=-5.0; y<0.0; y+=0.25) {
    first = true;
    for(z=23.0; z<28.0; z+=0.25) {
      generateOrbit(simulation, 0.66978, y, z, OBS);
//      std::cout << y << "," << z << "," << calcError(simulation, observations, OBS) << std::endl;
      if(first) first = false; else std::cout << ", ";
      std::cout << calcError(simulation, observations, OBS);
    }
    std::cout << std::endl; 
  }
}
  
void simWithNudging() {
  const int OBS=10000;
  double observations[OBS][3];
  double simulation[OBS][3];
  
  generateOrbit(observations, 0.66978, -3.57054, 26.4651, OBS);  // somewhere on the attractor
  
  double y,z;
  bool first;
  for(y=-5.0; y<5.0; y+=0.5) {
    first = true;
    for(z=0.0; z<28.0; z+=0.5) {
      generateNudgedOrbit(simulation, 0.66978, y, z, OBS, observations, 40.0);
      if(first) first = false; else std::cout << ", ";
      std::cout << calcError(simulation, observations, OBS);
    }
    std::cout << 0.0 << std::endl;
  }  
}

int main() {
  simWithNudging();
  return 0;
}