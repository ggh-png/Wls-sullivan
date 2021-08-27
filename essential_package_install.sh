sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt -y install curl # if you haven't already installed curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

sudo apt -y update
sudo apt -y upgrade

sudo apt -y install ros-melodic-desktop-full


sudo apt -y install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential

sudo apt -y install python-rosdep
	
sudo apt -y install ros-melodic-qt*
sudo apt -y install ros-melodic-move-base-msgs
sudo apt -y install ros-melodic-robot-pose-ekf

echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
