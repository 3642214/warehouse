#ifndef EVENT_H
#define EVENT_H
#include "mainwindow.h"
#include <QApplication>
#include <QKeyEvent>
#include "ui_mainwindow.h"

Ui::MainWindow ui;

class event:public QObject
{
    bool eventFilter(QObject *object, QEvent *event)
        {
            int key;

            switch(event->type())
            {
                // 只需要过滤按键事件
                case QEvent::KeyPress:
                case QEvent::KeyRelease:
                    // 对QEvent进行强制转换，并获得键值
                    key = (static_cast<QKeyEvent *>(event))->key();
                    // 需要过滤的按键
                    if (key == Qt::Key_Return)
                    {
                        // 当目标对象的类型是QExpandingLineEdit，则把消息转发给QTableWidget
                        if (! strcmp(object->metaObject()->className(), "QExpandingLineEdit"))
                        {

                            qDebug()<<"key in";
//                                focusNextChild();
                                QKeyEvent *k =  new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier,"\t",false,1);
                            qApp->sendEvent(ui.tableWidget, k);
                            return true;
                        }
                    }
                default:
                    return false;
            }
            return false;
        }
};

#endif // EVENT_H
