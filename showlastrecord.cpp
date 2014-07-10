#include "showlastrecord.h"
#include "ui_showlastrecord.h"
#include <QFileDialog>

showLastRecord::showLastRecord(db *myDB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showLastRecord),
    myDB1(myDB)
{
    ui->setupUi(this);

    QObject::connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(changeEtalon(QString)));

    ui->comboBox->addItem("所有");
    ui->comboBox->addItems(myDB1->getAllName());
}

showLastRecord::~showLastRecord()
{
    delete ui;
}

void showLastRecord::changeEtalon(QString name)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("所有");
    if(name == "所有")
    {
        return;
    }
    ui->comboBox_2->addItems(myDB1->getEtalon(name));
}

void showLastRecord::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    qDebug()<<"now row is "<<ui->tableWidget->rowCount();
    QString name = ui->comboBox->currentText();
    if(name == "所有")
    {
        QList<QString> namesList = myDB1->getAllName();
        for(int i = 0;i<namesList.size();i++)
        {
            QList<QString> etalonsList = myDB1->getEtalon(namesList.at(i));
            for(int j = 0;j<etalonsList.size();j++)
            {
                QString name1 = namesList.at(i);
                QString etalon1 = etalonsList.at(j);
                qDebug()<<"name etalon "<<name1<<etalon1;
                setTableItem(name1,etalon1,myDB1->getLastDetail(myDB1->getClassID(name1,etalon1)));
            }
        }
    }
    else {
        QString etalon = ui->comboBox_2->currentText();
        if(etalon == "所有")
        {
            QList<QString> etalonsList = myDB1->getEtalon(name);
            for(int i = 0;i<etalonsList.size();i++)
            {
                QString etalon2 = etalonsList.at(i);
                setTableItem(name,etalon2,myDB1->getLastDetail(myDB1->getClassID(name,etalon2)));
            }
        }
        else
        {
            setTableItem(name,etalon,myDB1->getLastDetail(myDB1->getClassID(name,etalon)));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void showLastRecord::setTableItem(QString name, QString etalon, QList<detail> detailList)
{
    for(int r = 0;r<detailList.size();r++)
    {
        detail m_detail = detailList.at(r);
        int row = ui->tableWidget->rowCount();
        qDebug()<<"row count = "<<row;
        ui->tableWidget->setRowCount(row+1);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(m_detail.id)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString(name)));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString(etalon)));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString(m_detail.date)));
        ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(m_detail.t_lend_long,10)));
        ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(m_detail.t_lend_sort,10)));
        ui->tableWidget->setItem(row,6,new QTableWidgetItem(QString::number(m_detail.t_new,10)));
        ui->tableWidget->setItem(row,7,new QTableWidgetItem(QString::number(m_detail.t_old,10)));
        ui->tableWidget->setItem(row,8,new QTableWidgetItem(QString::number(m_detail.t_total,10)));
        ui->tableWidget->setItem(row,9,new QTableWidgetItem(QString::number(m_detail.total,10)));
    }
}

void showLastRecord::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
}

void showLastRecord::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save excel"),".", tr("Microsoft Office 2003 (*.csv)"));//获取保存路径
    if (fileName.isEmpty()) {
        QMessageBox::critical(0, tr("错误"), tr("要保存的文件名为空！"));
        return;
    }
    QFile* m_file = new QFile(fileName);
    if(m_file->open(QIODevice::WriteOnly))
    {
        m_file->write("物品名:,");
        m_file->write(ui->comboBox->currentText().toUtf8().data());
        m_file->write(",规格:,");
        m_file->write(ui->comboBox_2->currentText().toUtf8().data());
        m_file->write("\n");
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            m_file->write(ui->tableWidget->horizontalHeaderItem(j)->text().toUtf8().data());
            if(j!=ui->tableWidget->columnCount() -1)
            {
                m_file->write(",");
            }
        }
        m_file->write("\n");

        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            for(int j=0;j<ui->tableWidget->columnCount();j++)
            {
                m_file->write(ui->tableWidget->item(i,j)->text().toUtf8().data());
                if(j!=ui->tableWidget->columnCount() -1)
                {
                    m_file->write(",");
                }
            }
            if(i!=ui->tableWidget->rowCount() -1 )
            {
                m_file->write("\n");
            }
        }
        m_file->close();
    }


    QMessageBox::information(this, tr("OK"), tr("保存成功！"));
}
