#include <iostream>
#include <stdio.h>
#include <Windows.h>
using namespace std;

enum ConsoleColor{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8, LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

// устанавливает цвет текста и подложки в консоли
void SetColor(int text, int background){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void goXY(int x, int y){
	COORD position;										// Объявление необходимой структуры
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
	position.X = x;									    // Установка координаты X
	position.Y = y;									    // Установка координаты Y
	SetConsoleCursorPosition(hConsole, position);
}
//get the current position of cursor
int getposY(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;

	if(GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &csbi)){
		coord.X = csbi.dwCursorPosition.X;
		coord.Y = csbi.dwCursorPosition.Y;
		return coord.Y;
	} else{
		coord.X = 0;
		coord.Y = 0;
		return coord.Y;
	}
}

class Point{
private:
	float x;
	float y;
public:
	Point(){
		SetColor(Yellow, Black);
		cout << "Point() Constructor" << '\n';
		this->x = 0;
		this->y = 0;
		SetColor(White, Black);
	}
	Point(float x, float y){
		SetColor(Yellow, Black);
		cout << "Point(x, y) Constructor" << '\n';
		this->x = x;
		this->y = y;
		SetColor(White, Black);
	}
	Point(const Point* a){
		SetColor(Yellow, Black);
		cout << "Point(Point) Constructor" << '\n';
		this->x = a->x;
		this->y = a->y;
		SetColor(White, Black);
	}
	~Point(){
		SetColor(Yellow, Black);
		cout << "Point Destructor" << '\n';
		SetColor(White, Black);
	};
	void SetX(float x){this->x = x;}
	void SetY(float y){this->y = y;}
	float GetX();
	float GetY();
};
float Point::GetX(){
	return this->x;
}
float Point::GetY(){
	return this->y;
}
class Figure{
protected:
	Point* arr;
public:
	Figure(){
		SetColor(Green, Black);
		cout << "Figure Constructor\n";
		//arr = nullptr;
		SetColor(White, Black);
	};
	~Figure(){
		SetColor(Green, Black);
		cout << "Figure Destructor\n";
		SetColor(White, Black);
		delete[](arr);
	};
	virtual void draw(int offset){};
};

class Line : public Figure{
public:
	Line(){
		SetColor(Red, Black);
		cout << "Line Constructor\n";
		arr = new Point[2];
		arr[0] = new Point();
		arr[1] = new Point();
		SetColor(White, Black);
	};
	Line(const Point* a, const Point* b){
		SetColor(Red, Black);
		cout << "Line Constructor\n";
		arr = new Point[2];
		arr[0] = Point(a);
		arr[1] = Point(b);
		SetColor(White, Black);
	};
	Line(const Line* a){
		SetColor(Red, Black);
		cout << "Line Constructor\n";
		arr = new Point[2];
		arr[0] = new Point(a->arr[0]);
		arr[1] = new Point(a->arr[1]);
		SetColor(White, Black);
	};
	~Line(){
		SetColor(Red, Black);
		cout << "Line Destructor\n";
		SetColor(White, Black);
	};
	double length(){
		double length, width, height;
		width = this->arr[0].GetX() - this->arr[1].GetX();
		height = this->arr[0].GetY() - this->arr[1].GetY();
		length = sqrt(width*width + height*height);
		return length;
	}
	void draw(float startOffsetX=0, float startOffsetY=0){
		float step, offsetY, offsetX, signY, signX;
		offsetX = abs(arr[0].GetX() - arr[1].GetX());
		offsetY = abs(arr[0].GetY() - arr[1].GetY());
		signX = arr[0].GetX() > arr[1].GetX() ? -1 : 1;
		signY = arr[0].GetY() > arr[1].GetY() ? -1 : 1;
		if (offsetX > offsetY){
			step = (offsetY/offsetX > 0) ? offsetY / offsetX : 0;
			for(int i = 0; i <= offsetX; i++){
				goXY(arr[0].GetX() + (i*signX) + startOffsetX, arr[0].GetY() + (step * i * signY) + startOffsetY);
				cout << "*";
			}
		} else{
			step = (offsetX / offsetY > 0) ? offsetX / offsetY : 0;
			for(int i = 0; i <= offsetY; i++){
				goXY(arr[0].GetX() + (step * i * signX) + startOffsetX, arr[0].GetY() + (i * signY) + startOffsetY);
				cout << "*";
			}
		}
		//goXY(0, step * offsetY);
	}
};

class MyRectangle: public Figure{
public:
	MyRectangle(){
		SetColor(Blue, Black);
		cout << "Rectangle() Constructor\n";
		arr = new Point[2];
		arr[0] = Point();
		arr[1] = Point();
		SetColor(White, Black);
	};
	/* Принимает точки соответвующие левому верхнему и правому нижнему углам */
	MyRectangle(Point* a, Point* b){
		SetColor(Blue, Black);
		cout << "Rectangle(Point, Point) Constructor\n";
		arr = new Point[2];
		if((a->GetX() <= b->GetX()) && (a->GetY() <= b->GetY())){
			arr[0] = Point(a);
			arr[1] = Point(b);
		} else{
			arr[0] = Point(b);
			arr[1] = Point(a);
		}
		SetColor(White, Black);
	};
	MyRectangle(const MyRectangle *a){
		SetColor(Blue, Black);
		cout << "Rectangle(MyRectangle) Constructor\n";
		arr = new Point[2];
		arr[0] = a->arr[0];
		arr[1] = a->arr[1];
		SetColor(White, Black);
	};
	~MyRectangle(){
		SetColor(Blue, Black);
		cout << "Rectangle Destructor\n";
		SetColor(White, Black);
	};
	void draw(int offset){
		int minX, maxX, minY, maxY;
		minX = this->arr[0].GetX();
		maxX = this->arr[1].GetX();
		minY = this->arr[0].GetY();
		maxY = this->arr[1].GetY();
		for(int i = minX; i < maxX; i++){
			goXY(offset + i, minY);
			cout << "*";
			goXY(offset + i, maxY);
			cout << "*";
		}
		for(int i = minY; i < maxY; i++){
			goXY(offset + minX, i);
			cout << "*";
			goXY(offset + maxX, i);
			cout << "*";
		}
		cout << "\n";
	}
	double square(){
		double square, width, height;
		width = this->arr[1].GetX() - this->arr[0].GetX();
		height = this->arr[1].GetY() - this->arr[0].GetY();
		square = width * height;
		return square;
	}
};

class RectangleCompos: public Figure{
protected:
	Line *width;
	Line *height;
public:
	RectangleCompos(){
		SetColor(Blue, Black);
		cout << "RectangleCompos() Constructor\n";
		Point a = Point();
		this->width = new Line(&a, &a);
		this->height = new Line(&a, &a);
		SetColor(White, Black);
	};
	RectangleCompos(Point a, Point b, Point c){
		SetColor(Blue, Black);
		cout << "RectangleCompos(Point, Point, Point) Constructor\n";
		this->width = new Line(&a, &b);
		this->height = new Line(&b, &c);
		SetColor(White, Black);
	};
	RectangleCompos(const Line *width, const Line *height){
		SetColor(Blue, Black);
		cout << "RectangleCompos(Line, Line) Constructor\n";
		this->width = new Line(width);
		this->height = new Line(height);
		SetColor(White, Black);
	};
	RectangleCompos(const RectangleCompos* a){
		SetColor(Blue, Black);
		cout << "RectangleCompos(RectangleCompos) Constructor\n";
		this->width = new Line(a->width);
		this->height = new Line(a->height);
		SetColor(White, Black);
	}
	~RectangleCompos(){
		SetColor(Blue, Black);
		cout << "RectangleCompos Destructor\n";
		delete(width);
		delete(height);
		SetColor(White, Black);
	};
	void draw(float offset){
		int yStart = getposY();
		width->draw(offset);
		height->draw(offset);
		width->draw(offset, height->length());
		height->draw(offset + width->length());
		goXY(0, yStart);
	}
	double square(){
		double square, width, height;
		width = this->width->length();
		height = this->height->length();
		square = width * height;
		return square;
	}
};

int main()
{
	/*
	Point a(1, 2);
	Point b(10, 20);
	Line* LineA = new Line(&a, &b);
	cout << "Length: " << (LineA->length()) << '\n';
	LineA->draw(30);
	cout << "\n";
	delete(LineA);
	cout << "\n";
	//*/

	/*
	Point a(1, 2);
	Point b(10, 20);
	MyRectangle* RectangleA = new MyRectangle(&a, &b);
	cout << RectangleA->square() << '\n';
	RectangleA->draw(50);
	delete(RectangleA);
	cout << "\n";
	//*/

	/*
	Point a(1, 2);
	Point b(10, 2);
	Point c(1, 10);
	Line LineB(&a, &b);
	Line LineC(&a, &c);
	cout << "\n";
	RectangleCompos* RectangleComposA = new RectangleCompos(&LineB, &LineC);
	cout << "Square: " << RectangleComposA->square() << '\n';
	RectangleComposA->draw(30);
	delete(RectangleComposA);
	//*/

	/*
	Figure** arrF = new Figure*[2];
	Point a(1, 2);
	Point b(10, 20);
	arrF[0] = new Line(&a, &b);
	arrF[1] = new MyRectangle(&a, &b);
	arrF[0]->draw(30);
	delete(arrF[0]);
	delete(arrF[1]);
	delete[](arrF);
	*/
}
