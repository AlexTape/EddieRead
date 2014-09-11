/*
 * camera_subscriber.cpp
 *
 *  Created on: 09.09.2014
 *      Author: eddie
 */
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "cv_bridge/CvBridge.h"
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <fstream>
#include <iostream>
#include <string>

// mode switching commands
std::string modeDictOn = "@ON";
std::string modeDictOff = "@OFF";

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {

	sensor_msgs::CvBridge bridge;

	try {

		// need a window?
		//cvNamedWindow("OCR View", CV_WINDOW_AUTOSIZE);
		//cvMoveWindow("OCR View", 150, 150);
		//cvStartWindowThread();

		// get single frame
		IplImage* frame = bridge.imgMsgToCv(msg, "bgr8");

		if (!frame) {

			ROS_INFO("RECIEVED NULL FRAME!");
		}

		// do NOT release the frame!
		//cvShowImage("OCR View", frame);

		// save image
		cvSaveImage("temp/capture.jpg", frame);

		/* Construct the command for Tesseract OCR and execute it*/
		std::ostringstream ocrCmdBuffer;
		ocrCmdBuffer.str("");

		/* Convert to tif for Tesseract */
		ocrCmdBuffer
		// with cropping
				<< "convert -gravity Center -crop 50%\! temp/capture.jpg temp/capture.tif >/dev/null 2>&1";
		// without cropping
		//<< "convert temp/capture.jpg temp/capture.tif >/dev/null 2>&1";

		system(ocrCmdBuffer.str().data());

		/* Process image (tif) and save it to <imgname>.tesseract.txt */
		ocrCmdBuffer.str("");
		ocrCmdBuffer
				<< "tesseract temp/capture.tif temp/capture.tesseract -l eng >/dev/null 2>&1";
		system(ocrCmdBuffer.str().data());

		/* Load the output of the OCR.
		 * Dump it to the console and return it to the caller. */
		std::ifstream inputFile("temp/capture.tesseract.txt");

		// read config file
		bool isDictMode;
		std::string stringMode;
		std::ifstream modeFile("temp/mode.txt");
		if (modeFile.is_open()) {

			getline(modeFile, stringMode);

			if (stringMode.find(modeDictOn) != std::string::npos) {

				isDictMode = true;
			} else {

				isDictMode = false;
			}

			modeFile.close();
		}

		// read ocr result
		while (!inputFile.eof() && !inputFile.fail()) {

			std::string line;
			std::getline(inputFile, line);

			if (!line.empty()) {

				std::cout << "Read: " << line << std::endl;
			} else {

				return;
			}

			// switch mode if needed
			if (line.find(modeDictOn) != std::string::npos) {

				std::string stringMode;
				std::ofstream modeFile("temp/mode.txt");
				if (modeFile.is_open()) {

					modeFile << modeDictOn;
					modeFile.close();
				}

				isDictMode = true;

				system("echo 'Dictionary Mode enabled' | festival --tts");
				ROS_INFO("Dictionary Mode enabled");
				return;
			}
			if (line.find(modeDictOff) != std::string::npos) {

				std::string stringMode;
				std::ofstream modeFile("temp/mode.txt");
				if (modeFile.is_open()) {

					modeFile << modeDictOff;
					modeFile.close();
				}

				isDictMode = false;

				system("echo 'Dictionary Mode disabled' | festival --tts");
				ROS_INFO("Dictionary Mode disabled");
				return;
			}

			// is dictionary mode?
			if (isDictMode == true) {

				std::string house = "House";
				if (line.find(house) != std::string::npos) {

					system("echo 'House' | festival --tts");

				}

				std::string computer = "Computer";
				if (line.find(computer) != std::string::npos) {

					system("echo 'Computer' | festival --tts");

				}
			}

			if (isDictMode == false) {

				std::string command = "echo '" + line + "' | festival --tts";
				system(command.c_str());
			}
		}

		inputFile.clear();
		inputFile.close();

		//cvDestroyWindow("OCR View");

	} catch (sensor_msgs::CvBridgeException& e) {

		ROS_ERROR("Could not convert from '%s' to 'bgr8'.",
				msg->encoding.c_str());
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "image_ocr");

	ros::NodeHandle nh;

	// set param for ocr mode
	ros::param::set("ocr_dictionary", false);

	ROS_INFO("IMAGE_OCR Callback() listening..");

	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("camera/rgb/image_mono", 1,
			imageCallback);

	ros::spin();
}
