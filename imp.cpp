#include <iostream>

#include "Rectangle.h"

using namespace std;

int Rectangle::getWidth(){
	return width;
}

int Rectangle::getLenght(){
	return lenght;
}

void Rectangle::setLenght(int PLenght){
	if (PLenght>=0)
		lenght=PLenght;
	else
		lenght=5;
}

void Rectangle::setWidth(int PWidth){
	if (PWidth>=0)
		width=PWidth;
	else
		width=5;
}

int Rectangle::getArea(){
	return lenght*width;
}

void Rectangle::rotateRectangle(){
	int temp;
	temp=lenght;
	lenght=width;
	width=temp;
}

void Rectangle::draw(){
	cout<<endl;
	for (int row=0;row<lenght;++row){

		for (int col=0;col<width;++col){
			cout<<'*';
		}
		cout<<endl;
	}
}