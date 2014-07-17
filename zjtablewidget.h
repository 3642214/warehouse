#ifndef ZJTABLEWIDGET_H
#define ZJTABLEWIDGET_H

#include <QTableWidget>
#include <QEvent>

class zjTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit zjTableWidget(QWidget *parent = 0);

signals:
    void changeSize(int w,int h);
protected:
//    void keyPressEvent(QKeyEvent *event);
//    void inputMethodEvent(QInputMethodEvent *event);
    bool event(QEvent *e);

public slots:
    void resizeColumnsToContents();
//   void printitemActivated();
//   void printitemChanged();
//   void printitemClicked();
//   void printitemDoubleClicked();
//   void printitemEntered();
//   void printitemPressed();
//   void printitemSelectionChanged();
};


#endif // ZJTABLEWIDGET_H
