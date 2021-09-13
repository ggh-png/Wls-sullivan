#include "image.h"
#include <QCoreApplication>
#include <QDebug>


QPixmap LoadPicture(QString ImagefileName){
  QString ApplicationDir = QCoreApplication::applicationDirPath();
  ApplicationDir.append(IMAGE_DIR);
  ApplicationDir.append(ImagefileName);
  QPixmap Image(ApplicationDir);
  if(Image.isNull()){
    qDebug() << "Get Picture fail / DIR:" << ApplicationDir;
  }
  return Image;
}

bool SetImageOnLabel(QString ImagefileName,QLabel* targetlabel){
  QPixmap Image = LoadPicture(ImagefileName).scaled(targetlabel->width()-10,targetlabel->height()-10,Qt::KeepAspectRatio); //사진 불러 오기 .png 생략가능
  if(Image.isNull()){
    qDebug()<<"Error :: Get Picture Failed \n"; // 사진 불러오기 확인
    return false;
   }
  targetlabel->setPixmap(Image); //라벨에 사진 나타내기
  return true;
}

bool SetImageOnpushbutton(QString ImagefileName, QPushButton* targetpushbutton){
  QPixmap Image = LoadPicture(ImagefileName);
  QSize ImageSize(targetpushbutton->width()-10,targetpushbutton->height()-10); //사진 불러 오기 .png 생략가능
  if(Image.isNull()){
    qDebug()<<"Error :: Get Picture Failed \n"; // 사진 불러오기 확인
    return false;
  }
  targetpushbutton->setIcon(Image); //라벨에 사진 나타내기
  targetpushbutton->setIconSize(ImageSize);
  return true;
}
