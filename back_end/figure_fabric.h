#pragma once

#include "figure_memory.h"
#include <QCursor>

class Figure_fabric
{
public:
	Figure_fabric(FigureMemory* mem);
	void set_start_cords(int widget_x,int widget_y);
	void set_width_height(int widget_x, int widget_y);
	Figure* create_figure();
	bool is_draw();
	void draw_focus(QPainter* painter, QPointF pt);

	void set_figure_class(QString figure_class);
	
	void stop_draw();
	QString get_figure_class();

private:
	
	int x;
	int y;
	int width;
	int height;
	
	int figure_number = 0;
	

	FigureMemory* mem;
	Figure* first_figur;
	Figure* second_figur;
	bool draw = false;
	QString figure_class = "NO";
};