#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    this->resize(600,600);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    path = QFileDialog::getOpenFileName(this,"选择存档","C:/Qt Game/游戏存档");

    QFile file(path);

    file.open(QIODevice::ReadOnly);

    QByteArray array = file.readAll();
    ui->textEdit->setText(array);

    file.close();
}

void Form::on_pushButton_2_clicked()
{
    QFile file(path);

    file.open(QIODevice::WriteOnly);

    QString text = ui->textEdit->toPlainText();

    file.write(text.toUtf8());

    file.close();

    this->close();
}

void Form::on_pushButton_3_clicked()
{
    path = QFileDialog::getSaveFileName(this,"存档","C:/Qt Game/游戏存档/请给存档命名.txt","*.txt");

    QFile file(path);

    file.open(QIODevice::WriteOnly);

    QString text = ui->textEdit->toPlainText();

    file.write(text.toUtf8());

    file.close();

    this->close();
}
