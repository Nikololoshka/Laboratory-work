#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    // init
    view_ = new QGraphicsView;
    scene_  = new QGraphicsScene;
    buttonPaint_ = new QPushButton(tr("Рисовать!"));
    buttonRedPaint_ =new QPushButton(tr("Красный!"));
    lineInputString_ = new QLineEdit;

    // settings
    scene_->setSceneRect(0, 0, 1280, 720);
    view_->setScene(scene_);
    view_->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    lineInputString_->setText("abcdefghijklmnopqrstuvwxyz");
    //lineInputString_->setText("jfpdglvcnsxqu");
    setMinimumSize(1280, 720);

    // layout setup
    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addWidget(lineInputString_);
    upLayout->addWidget(buttonPaint_);
    upLayout->addWidget(buttonRedPaint_);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addWidget(view_);

    setLayout(layout);

    // connections
    connect(buttonPaint_, &QPushButton::clicked, this, &MyWindow::slotPaint);
    connect(buttonRedPaint_, &QPushButton::clicked, this, &MyWindow::slotRedPaint);
}

void MyWindow::drawTree(BinaryTree<QChar> &tree, double sizeFactor, bool red)
{
    drawTreeImpl(tree.root_, scene_->width() * sizeFactor * tree.size() / 128,
                 scene_->width() / 2, scene_->height() / 3,
                 scene_->width() / 2, scene_->height() / 3,
                 tree, red);
}

void MyWindow::slotPaint()
{
    scene_->clear();
    BalanceTree<QChar> tree;
    for (auto &el : lineInputString_->text())
        tree.insert(el);

    drawTree(tree);
}

void MyWindow::slotRedPaint()
{
    scene_->clear();
    BinaryTree<QChar> tree;
    for (auto &el : lineInputString_->text())
        tree.insert(el);

    drawTree(tree, 2, true);
}

void MyWindow::drawTreeImpl(Node<QChar> *node, double level,
                            double x, double y,
                            double prevX, double prevY,
                            BinaryTree<QChar> &tree, bool red)
{
    if (node != nullptr) {
        drawTreeImpl(node->left_, level / 2,
                     x - level, y + 60,
                     x, y,
                     tree, red);

        scene_->addLine(prevX, prevY, x, y);

        drawTreeImpl(node->right_, level / 2,
                     x + level, y + 60,
                     x, y,
                     tree, red);

        scene_->addItem(new NodeItem(x, y, node->data_,
                                     (red && tree.count(node->data_) >= 2 )? true : false));
    }
}

NodeItem::NodeItem(double x, double y, QString str, bool red)
    : x_(x), y_(y), str_(str), red_(red)
{
}

QRectF NodeItem::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawEllipse(QPointF(x_, y_), 20, 20);
    painter->setFont(QFont("Arial", 16));
    if (red_)
        painter->setPen(Qt::red);
    painter->drawText(QRectF(x_ - 20, y_ - 20, 40, 40), Qt::AlignCenter, str_);
}
