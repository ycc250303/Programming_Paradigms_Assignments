#include<iostream>

/*define a base class Shape, which has a pure virtual function clone()*/
class Shape {
public:
	virtual Shape* clone() = 0;
	virtual ~Shape(){}
};

/*define a class Rectangle, which is derived from Shape*/
class Rectangle :public Shape {
private:
	int x;
	int y;
public:
    /*constructor*/
	Rectangle(int length,int width):x(length),y(width){}
	/*get area of Rectangle*/
	int area()const {
		return x * y; 
	}
    /*override clone() to return a copy of Rectangle*/
	Shape* clone()override {
		return new Rectangle(*this);
	}
};

/*define a class Circle, which is derived from Shape*/
class Circle : public Shape {
private:
	int radius;
public:
    /*constructor*/
	Circle(int r) : radius(r) {}
    /*get area of Circle*/
	double area() const {
		return 3.14 * radius * radius;
	}
    /*override clone() to return a copy of Circle*/
    Shape* clone() override {
        return new Circle(*this);
    }
};

int main() {
    
    Shape* shapes[2];
    shapes[0] = new Rectangle(3, 4); // Upcast to Shape
    shapes[1] = new Circle(5);       // Upcast to Shape

    Shape* clonedShapes[2];
    clonedShapes[0] = shapes[0]->clone(); // Clone Rectangle
    clonedShapes[1] = shapes[1]->clone(); // Clone Circle

    /* Verify cloned copies */
    Rectangle* rectClone = dynamic_cast<Rectangle*>(clonedShapes[0]);
    Circle* circleClone = dynamic_cast<Circle*>(clonedShapes[1]);

    if (rectClone != NULL) {
        std::cout << "Cloned Rectangle Area: " << rectClone->area() << std::endl;
    }
    else {
        std::cout << "Cloned Rectangle is not a Rectangle" << std::endl;
    }

    if (circleClone != NULL) {
        std::cout << "Cloned Circle Area: " << circleClone->area() << std::endl;
    }
    else {
        std::cout << "Cloned Circle is not a Circle" << std::endl;
    }

    // Clean up
    delete shapes[0];
    delete shapes[1];
    delete clonedShapes[0];
    delete clonedShapes[1];

    return 0;
}