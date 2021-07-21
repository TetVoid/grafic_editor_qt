#include "QFigureDrawer.h"

QFigureDrawer::QFigureDrawer(QQuickItem* parent): QQuickPaintedItem(parent)
{
    mem = new FigureMemory();
    fabricator = new Figure_fabric(mem);
}

QString QFigureDrawer::name() const
{
    return m_name;
}
void QFigureDrawer::setName(const QString& name)
{
    m_name = name;
}

void QFigureDrawer::setType(QString& type)
{
    if (type == "NO")
        mode_of_work = MOVE;
    else
        mode_of_work = DRAW;

    fabricator->set_figure_class(type);
}

void QFigureDrawer::paint(QPainter* painter)
{
    QPointF pt = mapFromGlobal(this->cursor().pos());
    if (fabricator->is_draw())
        fabricator->draw_focus(painter,pt);
    mem->draw(painter);
}

void  QFigureDrawer::start_create()
{
    QPointF pt = mapFromGlobal(this->cursor().pos());
    fabricator->set_start_cords(pt.x(),pt.y());
}
void  QFigureDrawer::stop_create()
{
    QPointF pt = mapFromGlobal(this->cursor().pos());
    fabricator->set_width_height(pt.x(), pt.y());
    update();
}

void QFigureDrawer::select()
{
    QPointF pt = mapFromGlobal(this->cursor().pos());
    mem->select(pt);
}

void  QFigureDrawer::update_canvas()
{
   
    if (mode_of_work == MOVE)
    {
        QPointF pt = mapFromGlobal(this->cursor().pos());
        mem->select(pt);
        if(mem->is_selected())
            mem->move(pt);
    }
    update();
}

void QFigureDrawer::save(QString& path)
{
    path.remove(0, 8);
    mem->save(path.toStdWString());
}


void QFigureDrawer::load(QString& path)
{
    path.remove(0, 8);
    mem->load(path.toStdWString());
}