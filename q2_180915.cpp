#include <iostream>
#include "Rectangle.h"

using namespace std;

void main(){
	Rectangle rect1;

	rect1.setLenght(3);
	rect1.setWidth(8);

	cout<<"Area: "<<rect1.getArea();

	rect1.draw();

	rect1.rotateRectangle();

	rect1.draw();

	int dum;
	cin>>dum;

}