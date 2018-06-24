#include <math.h>
#include <stdio.h>

double lambda  = 0.00000000000001;
double epsilon = 1.0;

double x[2][3];
double y[3];
double w[2];
double u[3][3];
double v[3][3][2];
double reg;
double Jw, Jwdw[2];
double min;
int i, j, k;
int step, step_min;
int OK;

int main(int argc, char *args[]){
  x[0][0] = 0.5 ;
  x[0][1] = 0.9 ;
  x[0][2] = 1.2 ;
  x[1][0] = 0.7 ;
  x[1][1] = 1.0 ;
  x[1][2] = 1.3 ;
  y[0] = 0.0 ;
  y[1] = 0.0 ;
  y[2] = 1.0 ;
  w[0] = 0.0 ;
  w[1] = 0.0 ;
  step = 1 ;
  min = 999.9 ;
  OK = 0 ;
  while(OK==0){
    OK = 1 ;
    for(i=0; i<100; i++){
      for(j=0; j<3; j++){
        u[0][j] = - y[j] * (w[0] * x[0][j] + w[1] * x[1][j]) ;
        u[1][j] = exp(u[0][j]) + 1.0 ;
        u[2][j] = log(u[1][j]) ;
      }
      reg = lambda * (w[0] * w[0] + w[1] * w[1]) ;
      Jw = (u[2][0] + u[2][1] + u[2][2]) / 3.0 + reg ;
      if(min > Jw){
        min = Jw ;
        step_min = step ;
        OK = 0 ;
      }
      printf("step %d : Jw = %.9f : min = %.9f : w1 = %.9f : w2 = %.9f\n",step,Jw,min,w[0],w[1]);
      for(k=0; k<2; k++){
        for(j=0; j<3; j++){
          v[0][j][k] = y[j] * w[k] * x[k][j] ;
          v[1][j][k] = exp(v[0][j][k]) + 1.0 ;
          v[2][j][k] = y[j] * x[k][j] / v[1][j][k] ;
        }
        Jwdw[k] = 2 * lambda * w[k] - (v[2][0][k] + v[2][1][k] + v[2][2][k]) / 3.0 ;



        w[k] = w[k] - epsilon * Jwdw[k] ;



      }
      step++;
    }
  }
  printf("w1 = %f , w2 = %f , step_min = %d\n",w[0],w[1],step_min);
  return 0 ;
}
