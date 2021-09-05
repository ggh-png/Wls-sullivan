# Project Team : Wls sisullivan
---

## Demo
---

##### reserved
##### 

<p alingn="center">
	<img src="https://user-images.githubusercontent.com/71277820/132127510-eb51b64b-3865-42ed-8802-37542fd9a69f.PNG" width="250">
</p>

## Introduce

```
위 로봇은 시각, 청각능력 없이 오직 촉각만을 느낄 수 있는 시청각 장애인들을 위해 만들어 졌으며, 로봇이 사용자의 특정한 손짓을 인식하여 사용자를 특정 장소까지 안전하게 인도하는 로봇이다. 
```
## Workflow 

<p alingn="center">
	<img src="https://user-images.githubusercontent.com/71277820/132127678-ddb22169-bbcf-41c4-a4d3-b42b810b9990.PNG" width="375">
	<img src="https://user-images.githubusercontent.com/71277820/132127679-26793a11-db7d-486e-ba1f-610323179d84.PNG" width="375">
</p>


## Install
---

```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
git clone https://github.com/ggh-png/MR_2.git
```
## Essential pakage install
---
```
cd ~/catkin_ws/src/MR_2
./essential_package_install.sh
source ~/.bashrc
```

## rebuild all
---
```
cd ~/catkin_ws/src/MR_2
./rebuild_all.sh
```
## build all
---
```
cd ~/catkin_ws/src/MR_2
./build_all.sh
```
## launch ui full size
---
```
cd ~/catkin_ws/src/MR_2
./launch_ui.sh
```
## launch ui max size
---
```
cd ~/catkin_ws/src/MR_2
./launch_ui_size_max.sh
```



---
## warning

이 package는 ubuntu 18.04 ros melodic 환경에서 동작합니다 
(그외의 환경에서는 작동하지 않습니다.)
 
