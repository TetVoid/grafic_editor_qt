#include "figure_fabric.h"

Figure_fabric::Figure_fabric(FigureMemory* mem)
{
	this->mem = mem;
}

void Figure_fabric:: set_start_cords(int widget_x, int widget_y)
{
	draw = true;
	if (figure_class != "arrow")
	{
		x = widget_x;
		y = widget_y;
	}
	else
	{
		QPoint pt(widget_x, widget_y);
		first_figur = mem->get_by_cords(pt);
	}
	
}

void  Figure_fabric::set_width_height(int widget_x, int widget_y)
{
	draw = false;
	if (figure_class != "arrow")
	{
		QPoint pt = QCursor::pos();
		width = (widget_x - x);
		height = (widget_y - y);
		
	}
	else
	{
		QPoint pt(widget_x, widget_y);
		second_figur = mem->get_by_cords(pt);
	}
	while (!mem->check_id(figure_number))
		figure_number++;
	mem->add(create_figure(), figure_number);
}

Figure* Figure_fabric::create_figure()
{
	Figure* pict = NULL;
	if (figure_class == "ellips")
	{
		pict = new Elipse(x, y, width, height);
		
	}
	else if (figure_class == "rect")
	{
		pict = new Rectangle(x, y, width, height);
		
	}
	else if (figure_class == "triangle")
	{
		pict = new Triangle(x, y, width, height);
		
	}
	else if (figure_class == "arrow")
	{
		pict = new Arrow(first_figur, second_figur);
	}

	figure_number++;
	return pict;
}

void Figure_fabric::draw_focus(QPainter* painter,QPointF pt)
{
	Figure* pict = NULL;

	if (figure_class == "ellips")
	{
		pict = new Elipse(x, y, (pt.x()-x), (pt.y()-y));

	}
	else if (figure_class == "rect")
	{
		pict = new Rectangle(x, y, (pt.x() - x), (pt.y() - y));

	}
	else if (figure_class == "triangle")
	{
		pict = new Triangle(x, y, (pt.x() - x), (pt.y() - y));

	}
	else if (figure_class == "arrow")
	{
		painter->drawLine(first_figur->get_center().x, first_figur->get_center().y,pt.x(),pt.y());
	}
	
	if(pict!=NULL)
		pict->draw(painter);

	delete pict;
}

bool Figure_fabric::is_draw()
{
	return draw;
}


void Figure_fabric::set_figure_class(QString figure_class)
{
	this->figure_class = figure_class;
}

QString Figure_fabric::get_figure_class()
{
	return figure_class;
}



void Figure_fabric::stop_draw()
{
	draw = false;
}

