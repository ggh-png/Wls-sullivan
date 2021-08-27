#include "mrmainwindow.h"
#include "ui_mrmainwindow.h"

MRMainWindow::MRMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MRMainWindow)
{
  ui->setupUi(this);
  ROS_Init();
  SignalSlotInit();
  WidgetInit();
}

MRMainWindow::~MRMainWindow()
{
  delete ui;
}

void MRMainWindow::ROS_Init(){
    //ros publisher
    pub_waypoint = nh.advertise<std_msgs::Int16>("/MR_2/waypoint", 10);
    pub_setwaypoint = nh.advertise<std_msgs::Int16>("/MR_2/set_waypoint",10);
    pub_moverobot = nh.advertise<std_msgs::Int16>("/MR_2/teleopkey",10);

    //ros subscriber
    sub_status = nh.subscribe("/MR_2/TP_state", 10, &MRMainWindow::sub_TP_state_callback,this);
}

void MRMainWindow::sub_TP_state_callback(const std_msgs::Int16::ConstPtr& msg)
{
#if QT_EVENT_DEBUG
    ROS_INFO("Recieved: [%d]", msg->data);
#endif
    switch(msg->data){
    case TP_state::hungry:
        mrdialog->setModal(true);
        mrdialog->show();
        mrdialog->Hungry();
        break;
    case TP_state::thirsty:
        mrdialog->setModal(true);
        mrdialog->show();
        mrdialog->Thirsty();
        break;
    case TP_state::toilet:
        mrdialog->setModal(true);
        mrdialog->show();
        mrdialog->Toilet();
        break;
    case TP_state::painful:
        mrdialog->setModal(true);
        mrdialog->show();
        mrdialog->Painful();
        break;
    case TP_state::emergency:
        mrdialog->setModal(true);
        mrdialog->show();
        mrdialog->Emergency();
        break;
    }
}

void MRMainWindow::SignalSlotInit(){
    //ros topic timer connect
    connect(ros_timer,SIGNAL(timeout()),this,SLOT(ros_timer_timeout()));
    ros_timer->start(300);
}

void MRMainWindow::ros_timer_timeout(){
    if(ros::ok()){
        pub_waypoint.publish(waypoint);
        waypoint.data = 0;

        pub_setwaypoint.publish(setwaypoint);
        setwaypoint.data = 0;

        pub_moverobot.publish(moverobot);
        if(!MoveRobotButtonPressed)moverobot.data = 0;

        ros::spinOnce();
    }
}

void MRMainWindow::WidgetInit(){
    ui->stackedWidget_wls->setCurrentIndex(main_page::page_waypoint);
}

void MRMainWindow::optionImageInit(){
    SetImageOnpushbutton("forward",ui->pushButton_move_forward);
    SetImageOnpushbutton("backward",ui->pushButton_move_backward);
    SetImageOnpushbutton("left",ui->pushButton_move_left);
    SetImageOnpushbutton("right",ui->pushButton_move_right);
    SetImageOnpushbutton("stop",ui->pushButton_move_stop);
}

//page waypoint

void MRMainWindow::on_pushButton_waypoint_1_clicked()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_waypoint_1_clicked";
#endif
    waypoint.data = 1;
}

void MRMainWindow::on_pushButton_waypoint_2_clicked()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_waypoint_2_clicked";
#endif
    waypoint.data = 2;
}

void MRMainWindow::on_pushButton_waypoint_3_clicked()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_waypoint_3_clicked";
#endif
    waypoint.data = 3;
}

void MRMainWindow::on_pushButton_waypoint_4_clicked()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_waypoint_4_clicked";
#endif
    waypoint.data = 4;
}

void MRMainWindow::on_pushButton_waypoint_5_clicked()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_waypoint_5_clicked";
#endif
    waypoint.data = 5;
}

void MRMainWindow::on_pushButton_option_clicked()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_option_clicked";
#endif
    ui->stackedWidget_wls->setCurrentIndex(main_page::page_set_waypoint);
    optionImageInit();
}

//page set waypoint

void MRMainWindow::on_pushButton_move_forward_pressed()
{
#if QT_EVENT_DEBUG
    qDebug()<<"on_pushButton_move_forward_pressed";
#endif
    MoveRobotButtonPressed = true;
    moverobot.data = 1;
}

void MRMainWindow::on_pushButton_move_forward_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_forward_clicked";
#endif
  MoveRobotButtonPressed = false;
}

void MRMainWindow::on_pushButton_move_stop_pressed()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_stop_pressed";
#endif
  MoveRobotButtonPressed = true;
  moverobot.data = 2;

}

void MRMainWindow::on_pushButton_move_stop_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_stop_clicked";
#endif
  MoveRobotButtonPressed = false;

}

void MRMainWindow::on_pushButton_move_left_pressed()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_left_pressed";
#endif
  MoveRobotButtonPressed = true;
  moverobot.data = 3;
}

void MRMainWindow::on_pushButton_move_left_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_left_clicked";
#endif
  MoveRobotButtonPressed = false;
}

void MRMainWindow::on_pushButton_move_right_pressed()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_right_pressed";
#endif
  MoveRobotButtonPressed = true;
  moverobot.data = 4;
}

void MRMainWindow::on_pushButton_move_right_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_right_clicked";
#endif
  MoveRobotButtonPressed = false;
}

void MRMainWindow::on_pushButton_move_backward_pressed()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_backward_pressed";
#endif
  MoveRobotButtonPressed = true;
  moverobot.data = 5;
}

void MRMainWindow::on_pushButton_move_backward_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_move_backward_clicked";
#endif
  MoveRobotButtonPressed = false;
}

void MRMainWindow::on_pushButton_set_waypoint_1_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_set_waypoint_1_clicked";
#endif
  setwaypoint.data = 1;
}

void MRMainWindow::on_pushButton_set_waypoint_2_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_set_waypoint_2_clicked";
#endif
  setwaypoint.data = 2;
}

void MRMainWindow::on_pushButton_set_waypoint_3_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_set_waypoint_3_clicked";
#endif
  setwaypoint.data = 3;
}

void MRMainWindow::on_pushButton_set_waypoint_4_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_set_waypoint_4_clicked";
#endif
  setwaypoint.data = 4;
}

void MRMainWindow::on_pushButton_set_waypoint_5_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_set_waypoint_5_clicked";
#endif
  setwaypoint.data = 5;
}

void MRMainWindow::on_pushButton_back_clicked()
{
#if QT_EVENT_DEBUG
  qDebug()<<"on_pushButton_back_clicked";
#endif
  ui->stackedWidget_wls->setCurrentIndex(main_page::page_waypoint);
}
