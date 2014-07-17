#include "zjtablewidget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QInputMethodEvent>
#include <QMetaEnum>
#include <QKeyEvent>
#include <QCoreApplication>

zjTableWidget::zjTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    //    QObject::connect(this,SIGNAL(itemActivated(QTableWidgetItem*)),this,SLOT(printitemActivated()));
    //    QObject::connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(printitemChanged()));
    //    QObject::connect(this,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(printitemClicked()));
    //    QObject::connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(printitemDoubleClicked()));
    //    QObject::connect(this,SIGNAL(itemEntered(QTableWidgetItem*)),this,SLOT(printitemEntered()));
    //    QObject::connect(this,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(printitemPressed()));
    //    QObject::connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(printitemSelectionChanged()));

}

//void zjTableWidget::keyPressEvent(QKeyEvent *event)
//{
//    qDebug()<<event->key();

//    //    QKeyEvent e(QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
//    //    QApplication::sendEvent(this->focusWidget(),&e);
//}

//void zjTableWidget::inputMethodEvent(QInputMethodEvent *event)
//{
//    qDebug()<<"evet";
//}

bool zjTableWidget::event(QEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        if(ke->key() == Qt::Key_Enter)
        {
//            qDebug() << "pressed enter";
            if(this->currentItem() != NULL)
            {
                int c = this->currentItem()->column() ;
                int r = this->currentItem()->row();
                if(c < this->columnCount() - 3)
                {
//                    qDebug() << "pressed enter";
                    this->setCurrentItem(this->item(r,c+1));
                    this->editItem(this->currentItem());
                }else if(c == this->columnCount() - 3)
                {
//                    qDebug() << "pressed enter pressed enter";
//                    int i = 0;
//                    int j = 0;
//                    if(this->item(r,c)->text() != "")
//                    {
//                        i = this->item(r,c)->text().toInt();
//                    }
//                    if(this->item(r,c-1)->text() != "")
//                    {
//                        j = this->item(r,c-1)->text().toInt();
//                    }
//                    qDebug() << "pressed enter pressed enter"<<i<<j;
//                    this->item(r,c+1)->setText(QString::number(i + j));
                    this->setCurrentItem(this->item(r,c+2));
                    this->editItem(this->currentItem());
                }

            }
        }
    }
    return QTableWidget::event(e);
}

void zjTableWidget::resizeColumnsToContents()
{
//    int t_width = 0;
//    int i = 0;
//    for(; i <= this->columnCount(); i++)
//    {
//        t_width += this->columnWidth(i);
//    }
//    t_width += (i - 1);
//    qDebug()<<"size is "<<t_width;
//    emit changeSize(t_width,this->height());
    return QTableView::resizeColumnsToContents();
}

//void zjTableWidget::printitemActivated()
//{
//    qDebug()<<"printitemActivated";
//}

//void zjTableWidget::printitemChanged()
//{
//    qDebug()<<"printitemChanged";
//}

//void zjTableWidget::printitemClicked()
//{
//    qDebug()<<"printitemClicked";
//}

//void zjTableWidget::printitemDoubleClicked()
//{
//    qDebug()<<"printitemDoubleClicked";
//}

//void zjTableWidget::printitemEntered()
//{
//    qDebug()<<"printitemEntered";
//}

//void zjTableWidget::printitemPressed()
//{
//    qDebug()<<"printitemPressed";
//}

//void zjTableWidget::printitemSelectionChanged()
//{
//    qDebug()<<"printitemSelectionChanged";
//}
