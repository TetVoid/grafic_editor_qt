#pragma once
#include <string>
#include <vector>
#include <fstream>
#include<sstream>

#include <QtQuick/QQuickPaintedItem>
#include <QPen>
#include <QPainter>
#include <QColor>


struct POINT
{
	int x;
	int y;
};

class Figure
{
public:
	Figure();
	Figure(std::vector<std::wstring>);
	Figure(int x, int y, int width, int height);
	~Figure();

	void virtual draw(QPainter* painter)=0;
	
	void move(QPointF pt);
	
	POINT get_center();
	std::wstring get_type();


	bool check_position(QPointF pt);

	bool select(QPointF pt);
	void stop_select();

	std::wstring virtual save();

protected:
	POINT center;

	bool select_flag=false;
	int height, width;

	std::wstring type = L"";
	
	void draw_borders(HDC hDC);
	
	std::vector<std::wstring> split(std::wstring);
};

class Rectangle : public Figure
{
public:
	Rectangle(std::vector<std::wstring>);
	Rectangle(int x, int y, int width, int height);
	void draw(QPainter* painter);
};

class Elipse : public Figure
{
public:
	Elipse(std::vector<std::wstring>);
	Elipse(int x, int y, int width, int height);
	void draw(QPainter* painter);

};

class Triangle : public Figure
{
public:
	Triangle(std::vector<std::wstring>);
	Triangle(int x, int y, int width, int height);
	void draw(QPainter* painter);
};


class Arrow : public Figure
{
public:
	Arrow(Figure* figur1, Figure* figur2);
	void draw(QPainter* painter);
	std::wstring save();
private:
	Figure* figur1;
	Figure* figur2;

};