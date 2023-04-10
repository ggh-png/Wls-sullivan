# **Wls-sullivan**

## Membor

[윤우성(Woosung Yun )](https://github.com/ggh-png), [김건우(Gun-woo Kim)](https://github.com/kimku-0112), [유창민(Changmin Yoo)](https://github.com/qprkquf)

Robot sw : [윤우성(Woosung Yun)](https://github.com/ggh-png)

Robot hw : [유창민(Changmin Yoo)](https://github.com/qprkquf)

Robot ui : [김건우(Gun-woo Kim)](https://github.com/kimku-0112)

![Image Label](https://user-images.githubusercontent.com/71277820/132127880-b20c1869-dfa0-4aea-ad04-9a5fe2b14d9d.PNG)

Wls-sullivan is a robot designed for visually impaired people who can only feel through touch. The robot recognizes the user's hand movements and delivers information to the user through a vibration pad. The robot is designed to safely guide the user to a specific location.

## **Demo**

![ezgif.com-gif-maker.gif](ezgif.com-video-to-gif.gif)


## **YouTube**

[![Video Label](https://user-images.githubusercontent.com/71277820/161438131-49853121-f4f7-4918-919d-9333d6604514.png)](https://youtu.be/FCpgLseV2Cw)

( When you click on the image above, you can see the demo link. )

## **Workflow**

### **Normal Mode**

![https://user-images.githubusercontent.com/71277820/132127678-ddb22169-bbcf-41c4-a4d3-b42b810b9990.PNG](https://user-images.githubusercontent.com/71277820/132127678-ddb22169-bbcf-41c4-a4d3-b42b810b9990.PNG)

### **Emergency Mode**

![https://user-images.githubusercontent.com/71277820/132127679-26793a11-db7d-486e-ba1f-610323179d84.PNG](https://user-images.githubusercontent.com/71277820/132127679-26793a11-db7d-486e-ba1f-610323179d84.PNG)

## **Hardware Architecture**

![https://user-images.githubusercontent.com/71277820/132128891-1c86db73-4cc6-4690-b971-a1122bcf12d5.PNG](https://user-images.githubusercontent.com/71277820/132128891-1c86db73-4cc6-4690-b971-a1122bcf12d5.PNG)

## **Software Architecture**

![https://user-images.githubusercontent.com/71277820/132128803-9cf4da9d-1bc5-4ff7-a755-14320d0988df.png](https://user-images.githubusercontent.com/71277820/132128803-9cf4da9d-1bc5-4ff7-a755-14320d0988df.png)

## **Installation**

### Clone the repository:

```bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
git clone https://github.com/ggh-png/Wls-sisullivan.git
```

## rebuild all

```bash
cd ~/catkin_ws/src/MR_2
./rebuild_all.sh
```

## build all

```bash
cd ~/catkin_ws/src/MR_2
./build_all.sh
```

## launch server

```bash
roscore
roslaunch MR_2_core MR_2_core.launch
```

## launch TP

### launch ui full size

```bash
cd ~/catkin_ws/src/MR_2
./launch_ui.sh
```

### launch ui max size

```bash
cd ~/catkin_ws/src/MR_2
./launch_ui_size_max.sh
```

### launch robot

```bash
source ~/catkin_ws/devel/setup.bash
roslaunch slam bringup.launch
```

> Note: This package works only in Ubuntu 18.04 with ROS Melodic. It may not work in other environments.
>
