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
  sudo apt-get –y update<br>
  sudo apt-get –y upgrade<br>
  sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu precise main" > /etc/apt/sources.list.d/ros-latest.list'<br>
  wget http://packages.ros.org/ros.key -O - | sudo apt-key add -<br>
  sudo apt-get update<br>
  yes | sudo apt-get install ros-fuerte-desktop-full python-rosinstall python-rosdep ros-fuerte-joystick-drivers ros-fuerte-multimaster-experimental ros-fuerte-mjpeg-server<br>
  echo "source /opt/ros/fuerte/setup.bash" >> ~/.bashrc. ~/.bashrc<br>
  rosws init ~/fuerte_workspace /opt/ros/fuerte<br>
  echo "source ~/fuerte_workspace/setup.bash" >> ~/.bashrc. ~/.bashrc<br>
  source ~/fuerte_workspace/setup.bash<br>
  yes | rosws set eddiebot --git git://github.com/robotictang/eddiebot.git<br>
  yes | rosws set eddiebot_teleop --git git://github.com/robotictang/eddiebot_teleop.git<br>
  rosws update<br>
<br>
Kinect Installation<br>
<br>
  sudo apt-get install default-jre default-jdk g++ git-core git cmake freeglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev doxygen graphviz mono-complete ros-fuerte-mjpeg-server build-essential python ros-fuerte-camera* ros-fuerte-openni*<br>
  sudo modprobe -r gspca_kinect<br>
  sudo modprobe -r gspca_main<br>
  echo "blacklist gspca_kinect" | sudo tee -a /etc/modprobe.d/blacklist.conf<br>
  sudo adduser $USER plugdev<br>
<br>
OpenNI Installation:<br>
  git clone https://github.com/OpenNI/OpenNI.git<br>
  cd OpenNI<br>
  git checkout Unstable-1.5.4.0<br>
  cd Platform/Linux/CreateRedist<br>
  chmod +x RedistMaker<br>
  ./RedistMaker<br>
  cd ../Redist/OpenNI-Bin-Dev-Linux-[xxx]  (where [xxx] is your architecture and this particular OpenNI release)<br>
  sudo ./install.sh<br>
<br>
SensorKinect Installation:<br>
  git clone https://github.com/avin2/SensorKinect<br>
  cd SensorKinect<br>
  cd Platform/Linux/CreateRedist<br>
  chmod +x RedistMaker<br>
  sudo ./RedistMaker<br>
  cd ../Redist/Sensor-Bin-Linux-[xxx] (where [xxx] is your architecture and this particular OpenNI release)<br>
  sudo chmod +x install.sh<br>
  sudo ./install.sh<br>
  sudo cp ../Install/55-primesense-usb.rules /lib/udev/rules.d/<br>
  <br>
Test OpenNI Samples:<br>
  cd OpenNI/Platform/Linux-x86/Bin/Release<br>
  ./Sample-NiSimpleViewer<br>
<br>
Test RGB Image Camera<br>
  roslaunch openni_launch openni.launch<br>
  rosrun image_view image_view image:=/camera/rgb/image_color<br>
  rosrun image_view image_view image:=/camera/depth/image<br>
<br>
Save Images:<br>
  rosrun image_view image_saver image:=/camera/rgb/image_color<br>
<br>
Nite Installation:<br>
  cd ~/kinect/nite/<br>
  chmod a+x install.sh<br>
  sudo ./install.sh<br>
<br>
Links:<br>
  OPENNI(unstable): https://github.com/OpenNI/OpenNI.git<br>
  SensorKinect(unstable): https://github.com/avin2/SensorKinect<br>
  NiTE-2.0.0: https://isda.ncsa.uiuc.edu/svn/teeve/trunk/TEEVE/misc/NiTE-2.0.0/<br>
  http://mitchtech.net/ubuntu-kinect-openni-primesense/<br>
  http://igorbarbosa.com/articles/how-to-install-kin-in-linux-mint-12-ubuntu/<br>
<br>
ROS and Eddiebot<br>
<br>
  sudo chmod 666 /dev/ttyUSB0<br>
  gnome-terminal -x /opt/ros/fuerte/bin/roscore<br>
  <br>
  $roslaunch eddiebot minimal.launch // launch without kinect<br>
  $roslaunch eddiebot kinect.launch // launch with kinect<br>
<br>
  gnome-terminal -x /opt/ros/fuerte/bin/roslaunch eddiebot_bringup minimal.launch<br>
  roslaunch eddiebot_teleop keyboard_teleop.launch<br>
<br>
ROS Strucutre<br>
  rxgraph<br>
<br>
More Links:<br>
  http://www.20papercups.net/programming/kinect-on-ubuntu-with-openni/<br>
  http://answers.ros.org/question/58386/pointcloud_to_laserscan-error-on-eddiebot-stack/<br>
  http://www.umiacs.umd.edu/~cteo/umd-erratic-ros-data/README_Kinect<br>
  http://wiki.ros.org/openni_launch/Tutorials/QuickStart<br>
  http://answers.ros.org/question/11676/viewing-rgb-and-depth-from-kinect-camera-in-ubuntu-1010/<br>
  http://answers.ros.org/question/87631/how-to-retrieve-data-from-kinect-using-rviz/<br>
    <br>
ROS and Eclipse<br>
  http://wiki.ros.org/action/fullsearch/roblab-whge-ros-pkg?action=fullsearch&context=180&value=linkto%3A%22roblab-whge-ros-pkg%22
  (see videos at the bottom)<br>
<br>
Notice ROS Working Path<br>
  nano ~/fuerte_workspace/setup.bash<br>
  export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/fuerte_workspace/project_name<br>
    <br>
Installation Java 1.7<br>
  sudo apt-get update<br>
  sudo apt-get install openjdk-7-jdk<br>
  sudo update-alternatives --config java<br>
  <br>
Installation Festival (Text-to-speech)<br>
  sudo apt-get install festival festvox-kallpc16k<br>
<br>
Installation Tesseract-OCR<br>
  sudo apt-get install tesseract-ocr*<br>
<br>
Installation OpenCV<br>
  rosws set OpenCV --git https://github.com/ros-perception/vision_opencv/tree/fuerte-devel/cv_bridge<br>
<br>
Create Eclipse Project<br>
  roscreate-pkg name dependencie, dependencie,..<br>
  export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/path_to_pkg<br>
  cd path_to_pkg<br>
  make eclipse-project <br>
<br>
Installation image_ocr<br>
  rosws set image_ocr --git https://github.com/AlexTape/ros-image-ocr.git<br>
<br>
Update Workspace<br>
  rosws update<br>
<br>
Change Kinect Resolution<br>
  rosrun dynamic-reconfigure reconfigure_gui<br>
  Find Topic: /camera/rgb/image_mono<br>
<br>
This Node uses textcleaner<br>
  http://www.fmwconcepts.com/imagemagick/textcleaner/index.php<br>
<br>
More Links:<br>
  http://roblab-whge-ros-pkg.googlecode.com/svn/trunk/OCR4ROS/DoorplateReader/src/OCRNode.cpp<br>
  http://roblab-whge-ros-pkg.googlecode.com/svn/trunk/roblab-whge-ros-pkg-read-only<br>
  http://wiki.ros.org/image_transport/Tutorials/SubscribingToImages<br>
<br>
 
