#include<stdio.h>
#include"calc_mean.h"

int main(){
double v1, v2, m;
v1=5.2;
v2=7.9;

m=mean(v1,v2);

printf("The mean of %3.2f and %32.f is %3.2f\n", v1, v2,m);
return 0;
}
