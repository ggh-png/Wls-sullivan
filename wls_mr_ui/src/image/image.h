#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QSize>

#define IMAGE_DIR       "/../../../src/wls_mr_ui/Image/"

QPixmap LoadPicture(QString ImagefileName);

bool SetImageOnLabel(QString ImagefileName,QLabel* tergetlabel);

bool SetImageOnpushbutton(QString ImagefileName, QPushButton* targetpushbutton);







#endif // PICTURE_H
