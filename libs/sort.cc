#include <stdio.h>
#include <stdlib.h>     /* srand, rand */

int sonar = 2;

int getDistance(int x){
  return rand() % 10 + 1;
}

float getFrontDistance(){  
  int attemptCount = 5;
  int attempts[5] = {};
  for(int a=0;a<attemptCount;a++){
    int d = getDistance(sonar);
    for(int i=0;i<attemptCount;i++){
      int v = attempts[i];
      if(v==0){
        attempts[i] = d;
        break; // we are done
      }else{
        // shift everything by one
        if(d<v){
          for(int j=a;j>i;j--){
            attempts[j] = attempts[j-1];
          }
          attempts[i] = d;
          break;
        }
      }
    }
  }
  float distanceSum = 0;
  for(int i=1;i<attemptCount-1;i++){
    distanceSum += attempts[i];
  }
  return distanceSum / attemptCount;
}

int main(){
  printf("%f\n", getFrontDistance());
}

