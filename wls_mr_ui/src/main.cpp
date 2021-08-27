#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <QApplication>
#include "mrmainwindow.h"


#define Normal 0
#define Full  1
#define Max   2
#define Min   3

namespace mainwindow_type{
  enum index{
    normal = 0,
    full,
    max,
    min
  };
}

int main(int argc, char **argv)
{
  int MainwindowType = 0;

  ros::init(argc, argv, "wls_mr_ui");

  std::string packagePath = ros::package::getPath( "wls_mr_ui" );

  if(ros::param::has("~mainwindow_type"))
  {
    ros::param::get("~mainwindow_type",MainwindowType);
  }

  QApplication a(argc,argv);

  MRMainWindow w;


  switch(MainwindowType){
    case mainwindow_type::normal:
      printf("\n normal ros param");
      w.show();
    break;
    case mainwindow_type::full:
      printf("\n full ros param");
      w.showFullScreen();
    break;
    case mainwindow_type::max:
      printf("\n maximum ros param");
      w.showMaximized();
    break;
    case mainwindow_type::min:
      printf("\n minimum ros param");
      w.showMinimized();
    break;
    default:
      printf("\nERROR :: wrong ros param\n\n\n\n\n\n\n");
      w.show();
    break;
  }
  return a.exec();
}
