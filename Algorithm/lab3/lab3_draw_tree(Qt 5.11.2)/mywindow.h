#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include "binarytree.h"
#include "balancetree.h"

class NodeItem;

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);
    void drawTree(BinaryTree<QChar> &tree, double sizeFactor = 1, bool red = false);

public slots:
    void slotPaint();
    void slotRedPaint();

private:
    void drawTreeImpl(Node<QChar> *node, double level,
                      double x, double y,
                      double prevX, double prevY,
                      BinaryTree<QChar> &tree, bool red = false);

    QGraphicsView *view_;
    QGraphicsScene *scene_;
    QLineEdit *lineInputString_;
    QPushButton *buttonPaint_;
    QPushButton *buttonRedPaint_;
};

class NodeItem : public QGraphicsItem
{
public:
    NodeItem(double x, double y, QString str, bool red);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    double x_;
    double y_;
    QString str_;
    bool red_;
};

#endif // MYWINDOW_H
