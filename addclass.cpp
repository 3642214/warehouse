#include "addclass.h"
#include "ui_addclass.h"

addClass::addClass(db* myDB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addClass),
    myDB1(myDB)
{
    ui->setupUi(this);

    QObject::connect(ui->namesComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(changeEtalon(QString)));
    ui->namesComboBox->addItems(myDB1->getAllName());
}

addClass::~addClass()
{
    delete ui;
}

void addClass::changeEtalon(QString name)
{
    ui->etalonComboBox->clear();
    ui->etalonComboBox->addItems(myDB1->getEtalon(name));
}

void addClass::on_addButton_clicked()
{
    QString newName = ui->lineEdit->text();
    QString newEtalon = ui->lineEdit_2->text();
    if(myDB1->setClass(newName,newEtalon) > 0)
    {
        ui->namesComboBox->clear();
        ui->namesComboBox->addItems(myDB1->getAllName());
        ui->namesComboBox->setCurrentText(newName);
        ui->etalonComboBox->setCurrentText(newEtalon);
        emit changeNames();
    }
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");

}

void addClass::on_delButton_clicked()
{
    QString delName = ui->lineEdit->text();
    QString delEtalon = ui->lineEdit_2->text();
    if(delName == NULL && delEtalon == NULL)
    {
        delName = ui->namesComboBox->currentText();
        delEtalon = ui->etalonComboBox->currentText();
    }
    QMessageBox::StandardButton delWarn = QMessageBox::warning(NULL, "删除提示", "是否删除>>" + delName + "<<的>>" + delEtalon +"<<规格,删除无法恢复!!!", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(delWarn == QMessageBox::Yes)
    {
        int classID = myDB1->getClassID(delName,delEtalon);
        if(myDB1->delClass(delName,delEtalon) && myDB1->delDetailByClassID(classID))
        {
            ui->namesComboBox->clear();
            ui->namesComboBox->addItems(myDB1->getAllName());
            emit changeNames();
        }
    }
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void addClass::on_flushButton_clicked()
{
    ui->namesComboBox->clear();
    ui->namesComboBox->addItems(myDB1->getAllName());
}

void addClass::on_modifyButton_clicked()
{
    QString oldName = ui->namesComboBox->currentText();
    QString oldEtalon = ui->etalonComboBox->currentText();
    QString newName = ui->lineEdit->text();
    QString newEtalon = ui->lineEdit_2->text();
    QMessageBox::StandardButton delWarn = QMessageBox::warning(NULL, "修改提示", "是否将>>" + oldName + "<<的>>" + oldEtalon +"<<规格,修改为>>" + newName + "<<的>>" + newEtalon + "<<规格!!!", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(delWarn == QMessageBox::Yes)
    {
        int classID = myDB1->getClassID(oldName,oldEtalon);
        if(myDB1->updateClass(classID,newName,newEtalon))
        {
            ui->namesComboBox->clear();
            ui->namesComboBox->addItems(myDB1->getAllName());
            emit changeNames();
        }
    }
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}
