#pragma once
#include "figure_memory.h"
#include "figure_fabric.h"

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

#define DRAW 0
#define MOVE 1

class QFigureDrawer : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName)
        

public:
    QFigureDrawer(QQuickItem* parent = 0);

    QString name() const;
    void setName(const QString& name);

    void paint(QPainter* painter);

    Q_INVOKABLE void setType(QString& type);
    Q_INVOKABLE void start_create();
    Q_INVOKABLE void stop_create();
    Q_INVOKABLE void select();
    Q_INVOKABLE void update_canvas();
    Q_INVOKABLE void save(QString& path);
    Q_INVOKABLE void load(QString& path);

private:
    FigureMemory *mem;
    Figure_fabric *fabricator;
    QString m_name;
    QColor m_color;
    
    int mode_of_work = MOVE;
};