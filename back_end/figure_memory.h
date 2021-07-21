#pragma once
#include "models.h"
#include <map>

#include <fstream>
#include<sstream>
#include <fstream>

class FigureMemory
{
public:
	FigureMemory();
	~FigureMemory();
	Figure* operator[](int index);
	void add(Figure* figure, int index);
	void del();
	void del(int index);
	void move(QPointF pt);
	
	void select(QPointF pt);
	
	void draw(QPainter* painter);
	

	Figure* get_by_cords(QPointF pt);
	bool is_selected();

	bool check_id(int id);

	void save(std::wstring);
	void load(std::wstring);
	void clear();

	int size();

private:
	std::map<int, Figure*>figure_list;
	int figure_index = -1;

	std::vector<std::wstring> split(std::wstring str);
};

