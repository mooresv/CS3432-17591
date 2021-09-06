#include <stdio.h>
int main()
{
	float convert(float x){
		return (5.0/9.0)*(x-32);
	}
	  int fahr;

	  for (fahr = 0; fahr <= 300; fahr = fahr + 20)
		    printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
	  
	  printf("%6.1f",convert(20));
}
