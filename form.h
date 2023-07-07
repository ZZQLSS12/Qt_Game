#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include<QFileDialog>
namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Form *ui;

    QString path;
};

#endif // FORM_H
