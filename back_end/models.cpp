#include "models.h"




Figure::Figure(){}

Figure::Figure(std::vector<std::wstring> load_string)
{
    std::vector<std::wstring> figInfo = split(load_string[1]);
    center.x = std::stoi(figInfo[0]);
    center.y = std::stoi(figInfo[1]);

    figInfo = split(load_string[2]);
    width = std::stoi(figInfo[0]);
    height = std::stoi(figInfo[1]);
   
}

Figure::Figure( int x, int y, int width, int height)
{

    this->height = height;
    this->width = width;
    center.x = x + int(width / 2);
    center.y = y + int(height / 2);
}

Figure::~Figure()
{
}

std::vector<std::wstring> Figure::split(std::wstring str)
{
    std::wstring temp;
    std::vector<std::wstring> parts;
    std::wstringstream wss(str);
    while (std::getline(wss, temp, L' '))
        parts.push_back(temp);

    return parts;
}



void Figure::draw_borders(HDC hDC)
{
    
}





bool Figure::check_position(QPointF pt)
{
    if ((center.x + width / 2 > pt.x() && center.x - width / 2 < pt.x()) && (center.y + height / 2 > pt.y() && center.y - height / 2 < pt.y()))
        return true;
    else
        return false;
}



bool Figure::select(QPointF pt)
{
    if (check_position(pt))
        if (select_flag)
            select_flag = false;
        else
            select_flag = true;

   return select_flag;
}

void Figure::stop_select()
{
    select_flag = false;
}

void Figure::move(QPointF pt)
{
    center.x = pt.x();
    center.y = pt.y();
}


POINT Figure::get_center()
{
    return center;
}


std::wstring Figure::get_type()
{
    return type;
}

std::wstring Figure::save()
{
    std::wstring figure_info = L"";
    figure_info += type + L"\n";
   
    figure_info += std::to_wstring(center.x) + L" " + std::to_wstring(center.y) + L"\n";
    figure_info += std::to_wstring(width) + L" "+std::to_wstring(height)+ L"\n";
   
    return figure_info;
}

Rectangle::Rectangle(std::vector<std::wstring> load_string) :Figure(load_string)
{

}
Rectangle::Rectangle(int x, int y, int width, int height) : Figure(x, y, width, height)
{
    this->type = L"Rectangle";
}

void Rectangle::draw(QPainter* painter)
{
    QColor color(0, 255, 0);
    QPen pen(color, 2);
    painter->setPen(pen);
    int x = center.x - width / 2;
    int y = center.y - height / 2;
    painter->drawRect(x, y, width, height);
}

void Elipse::draw(QPainter* painter)
{
    QColor color(255, 0, 0);
    QPen pen(color,2);
    painter->setPen(pen);
    int x = center.x - width / 2;
    int y = center.y - height / 2;
    painter->drawEllipse(x, y, width, height);
}

Elipse::Elipse(int x, int y, int width, int height) : Figure(x, y, width, height)
{
    this->type =L"Elipse";
}

Elipse::Elipse(std::vector<std::wstring> load_string) : Figure(load_string)
{
    
}





Triangle::Triangle(std::vector<std::wstring> load_string) :Figure(load_string)
{
   
}

Triangle::Triangle(int x, int y, int width, int height) : Figure(x, y, width, height)
{
    this->type = L"Triangle";
}
void Triangle::draw(QPainter* painter)
{
    QColor color(0, 0, 255);
    QPen pen(color, 2);
    painter->setPen(pen);
    painter->drawLine(center.x, center.y - height / 2, center.x + width / 2, center.y + height / 2);
    painter->drawLine( center.x + width / 2, center.y + height / 2, center.x-width/2, center.y + height / 2);
    painter->drawLine( center.x - width / 2, center.y + height / 2, center.x, center.y - height / 2 );
}


Arrow::Arrow(Figure* figur1, Figure* figur2)
{
    this->figur1 = figur1;
    this->figur2 = figur2;
    this->type = L"Arrow";
}

void Arrow::draw(QPainter* painter)
{

    QColor color(0, 0, 0);
    QPen pen(color, 2);
    painter->setPen(pen);
    painter->drawLine(figur1->get_center().x, figur1->get_center().y, figur2->get_center().x, figur2->get_center().y);
}




std::wstring  Arrow::save()
{
    std::wstring figure_info = L"";
    figure_info += type + L"\n";

    figure_info += std::to_wstring(figur1->get_center().x) + L" " + std::to_wstring(figur1->get_center().y) + L"\n";
    figure_info += std::to_wstring(figur2->get_center().x) + L" " + std::to_wstring(figur2->get_center().y) + L"\n";

    return figure_info;
}

