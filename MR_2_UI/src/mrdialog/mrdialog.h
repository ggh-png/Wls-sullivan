#ifndef MRDIALOG_H
#define MRDIALOG_H

#include <QDialog>
#include <image.h>

namespace Ui {
class MRDialog;
}

class MRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MRDialog(QWidget *parent = nullptr);
    ~MRDialog();

    void Hungry();
    void Thirsty();
    void Toilet();
    void Painful();
    void Emergency();


private slots:

    void on_pushButton_ok_clicked();

private:
    Ui::MRDialog *ui;
};

#endif // MRDIALOG_H
