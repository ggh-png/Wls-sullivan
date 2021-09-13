#include "mrdialog.h"
#include "ui_mrdialog.h"

MRDialog::MRDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MRDialog)
{
    ui->setupUi(this);
}

MRDialog::~MRDialog()
{
    delete ui;
}

void MRDialog::Hungry()
{
    ui->label_status->setText("hungry");
    SetImageOnLabel("hungry",ui->label_status_image);
}

void MRDialog::Thirsty()
{
    ui->label_status->setText("thirsty");
    SetImageOnLabel("thirsty",ui->label_status_image);
}

void MRDialog::Toilet()
{
    ui->label_status->setText("toilet");
    SetImageOnLabel("toilet",ui->label_status_image);
}

void MRDialog::Painful()
{
    ui->label_status->setText("painful");
    SetImageOnLabel("painful",ui->label_status_image);
}

void MRDialog::Emergency()
{
    ui->label_status->setText("emergency");
    SetImageOnLabel("emergency",ui->label_status_image);
}

void MRDialog::on_pushButton_ok_clicked()
{
    MRDialog::accept();
}
