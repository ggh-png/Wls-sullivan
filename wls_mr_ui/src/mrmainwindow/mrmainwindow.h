#ifndef MRMAINWINDOW_H
#define MRMAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>
#include "image.h"
#include <QTimer>
#include "mrdialog.h"


#define QT_EVENT_DEBUG true

namespace main_page {
    enum index{
        page_waypoint = 0,
        page_set_waypoint
    };

}

namespace TP_state {
    enum index{
        hungry = 1,
        thirsty,
        toilet,
        painful,
        emergency
    };
}

namespace Ui {
class MRMainWindow;
}

class MRMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MRMainWindow(QWidget *parent = nullptr);
  ~MRMainWindow();

    //ros nodehandle
    ros::NodeHandle nh;

    //ros topic timer
    QTimer *ros_timer = new QTimer;

    MRDialog *mrdialog = new MRDialog;

private slots:

    //page waypoint

    void on_pushButton_waypoint_1_clicked();

    void on_pushButton_waypoint_2_clicked();

    void on_pushButton_waypoint_3_clicked();

    void on_pushButton_waypoint_4_clicked();

    void on_pushButton_waypoint_5_clicked();

    void on_pushButton_option_clicked();

    //page set waypoint

    void on_pushButton_move_forward_pressed();

    void on_pushButton_move_forward_clicked();

    void on_pushButton_move_stop_clicked();

    void on_pushButton_move_stop_pressed();

    void on_pushButton_move_left_pressed();

    void on_pushButton_move_left_clicked();

    void on_pushButton_move_right_pressed();

    void on_pushButton_move_right_clicked();

    void on_pushButton_move_backward_pressed();

    void on_pushButton_move_backward_clicked();

    void on_pushButton_set_waypoint_1_clicked();

    void on_pushButton_set_waypoint_2_clicked();

    void on_pushButton_set_waypoint_3_clicked();

    void on_pushButton_set_waypoint_4_clicked();

    void on_pushButton_set_waypoint_5_clicked();

    void on_pushButton_back_clicked();

    //ros topic timer timeout

    void ros_timer_timeout();

private:
  Ui::MRMainWindow *ui;

  void ROS_Init();
  void SignalSlotInit();
  void WidgetInit();
  void optionImageInit();

  //move robot value
  bool MoveRobotButtonPressed = false;

  //ros publisher
  ros::Publisher pub_waypoint;
  ros::Publisher pub_setwaypoint;
  ros::Publisher pub_moverobot;

  //ros pub value
  std_msgs::Int16 waypoint;
  std_msgs::Int16 setwaypoint;
  std_msgs::Int16 moverobot;

  //ros subscriber
  ros::Subscriber sub_status;

  //ros callback
  void sub_TP_state_callback(const std_msgs::Int16::ConstPtr& msg);





};

#endif // MRMAINWINDOW_H
