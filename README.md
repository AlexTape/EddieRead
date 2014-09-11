ros-image-ocr<br>
=============<br>
<br>
Simple Subscriber with tesseract binding<br>
<br>
Installation Notes:
http://www.parallax.com/downloads/propeller-Tool-Software<br>
git clone https://github.com/robotictang/eddiebot_firmware.git<br>
<br>
Environment Installation: Ubuntu 12.04 LTS + ROS<br>
<br>
  sudo apt-get –y update<br>
  sudo apt-get –y upgrade<br>
  sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu precise main" > /etc/apt/sources.list.d/ros-latest.list'
  wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
  sudo apt-get update
  yes | sudo apt-get install ros-fuerte-desktop-full python-rosinstall python-rosdep ros-fuerte-joystick-drivers ros-fuerte-multimaster-experimental ros-fuerte-mjpeg-server
  echo "source /opt/ros/fuerte/setup.bash" >> ~/.bashrc. ~/.bashrc
  rosws init ~/fuerte_workspace /opt/ros/fuerte
  echo "source ~/fuerte_workspace/setup.bash" >> ~/.bashrc. ~/.bashrc
  source ~/fuerte_workspace/setup.bash
  yes | rosws set eddiebot --git git://github.com/robotictang/eddiebot.git
  yes | rosws set eddiebot_teleop --git git://github.com/robotictang/eddiebot_teleop.git
  rosws update

Kinect Installation

  sudo apt-get install default-jre default-jdk g++ git-core git cmake freeglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev doxygen graphviz mono-complete ros-fuerte-mjpeg-server build-essential python ros-fuerte-camera* ros-fuerte-openni*
  sudo modprobe -r gspca_kinect
  sudo modprobe -r gspca_main
  echo "blacklist gspca_kinect" | sudo tee -a /etc/modprobe.d/blacklist.conf
  sudo adduser $USER plugdev

OpenNI Installation:
  git clone https://github.com/OpenNI/OpenNI.git
  cd OpenNI
  git checkout Unstable-1.5.4.0
  cd Platform/Linux/CreateRedist
  chmod +x RedistMaker
  ./RedistMaker
  cd ../Redist/OpenNI-Bin-Dev-Linux-[xxx]  (where [xxx] is your architecture and this particular OpenNI release)
  sudo ./install.sh

SensorKinect Installation:
  git clone https://github.com/avin2/SensorKinect
  cd SensorKinect
  cd Platform/Linux/CreateRedist
  chmod +x RedistMaker
  sudo ./RedistMaker
  cd ../Redist/Sensor-Bin-Linux-[xxx] (where [xxx] is your architecture and this particular OpenNI release)
  sudo chmod +x install.sh
  sudo ./install.sh
  sudo cp ../Install/55-primesense-usb.rules /lib/udev/rules.d/
  
Test OpenNI Samples:
  cd OpenNI/Platform/Linux-x86/Bin/Release
  ./Sample-NiSimpleViewer

Test RGB Image Camera
  roslaunch openni_launch openni.launch
  rosrun image_view image_view image:=/camera/rgb/image_color
  rosrun image_view image_view image:=/camera/depth/image

Save Images:
  rosrun image_view image_saver image:=/camera/rgb/image_color

Nite Installation:
  cd ~/kinect/nite/
  chmod a+x install.sh
  sudo ./install.sh

Links:
  OPENNI(unstable): https://github.com/OpenNI/OpenNI.git
  SensorKinect(unstable): https://github.com/avin2/SensorKinect
  NiTE-2.0.0: https://isda.ncsa.uiuc.edu/svn/teeve/trunk/TEEVE/misc/NiTE-2.0.0/
  http://mitchtech.net/ubuntu-kinect-openni-primesense/
  http://igorbarbosa.com/articles/how-to-install-kin-in-linux-mint-12-ubuntu/

ROS and Eddiebot

  sudo chmod 666 /dev/ttyUSB0
  gnome-terminal -x /opt/ros/fuerte/bin/roscore
  
  $roslaunch eddiebot minimal.launch // launch without kinect
  $roslaunch eddiebot kinect.launch // launch with kinect

  gnome-terminal -x /opt/ros/fuerte/bin/roslaunch eddiebot_bringup minimal.launch
  roslaunch eddiebot_teleop keyboard_teleop.launch

ROS Strucutre
  rxgraph

More Links:
  http://www.20papercups.net/programming/kinect-on-ubuntu-with-openni/
  http://answers.ros.org/question/58386/pointcloud_to_laserscan-error-on-eddiebot-stack/
  http://www.umiacs.umd.edu/~cteo/umd-erratic-ros-data/README_Kinect
  http://wiki.ros.org/openni_launch/Tutorials/QuickStart
  http://answers.ros.org/question/11676/viewing-rgb-and-depth-from-kinect-camera-in-ubuntu-1010/
  http://answers.ros.org/question/87631/how-to-retrieve-data-from-kinect-using-rviz/
    
ROS and Eclipse
  http://wiki.ros.org/action/fullsearch/roblab-whge-ros-pkg?action=fullsearch&context=180&value=linkto%3A%22roblab-whge-ros-pkg%22
  (see videos at the bottom)

Notice ROS Working Path
  nano ~/fuerte_workspace/setup.bash
  export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/fuerte_workspace/project_name
    
Installation Java 1.7
  sudo apt-get update
  sudo apt-get install openjdk-7-jdk
  sudo update-alternatives --config java
  
Installation Festival (Text-to-speech)
  sudo apt-get install festival festvox-kallpc16k

Installation Tesseract-OCR
  sudo apt-get install tesseract-ocr*

Installation OpenCV
  rosws set OpenCV --git https://github.com/ros-perception/vision_opencv/tree/fuerte-devel/cv_bridge

Create Eclipse Project
  roscreate-pkg name dependencie, dependencie,..
  export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/path_to_pkg
  cd path_to_pkg
  make eclipse-project 

Installation image_ocr
  rosws set image_ocr --git https://github.com/AlexTape/ros-image-ocr.git

Update Workspace
  rosws update

Change Kinect Resolution
  rosrun dynamic-reconfigure reconfigure_gui
  Find Topic: /camera/rgb/image_mono

This Node uses textcleaner
  http://www.fmwconcepts.com/imagemagick/textcleaner/index.php

More Links:
  http://roblab-whge-ros-pkg.googlecode.com/svn/trunk/OCR4ROS/DoorplateReader/src/OCRNode.cpp
  http://roblab-whge-ros-pkg.googlecode.com/svn/trunk/roblab-whge-ros-pkg-read-only
  http://wiki.ros.org/image_transport/Tutorials/SubscribingToImages

 
