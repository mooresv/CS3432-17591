/* Alyssandra M. Cordero*/
#include <stdio.h>
/* convert: conversion from Fahrenheit to Celsius; performs opperation*/
float convert(float fah){
	float celsius;celsius = (5.0 / 9.0) * (fah -32)
		return celsius;
}
/*test convert function*/
void main()
{
	float fahr; /*declaration*/
	for (fahr = 0.0; fahr <= 300.0; fahr = fahr + 20.0)
		printf("%3d %6.1f\n", fahr, convert(fahr));
}
