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

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	sensor_msgs::CvBridge bridge;
	try {

		cvNamedWindow("OCR View", CV_WINDOW_AUTOSIZE);
		cvMoveWindow("OCR View", 150, 150);
		cvStartWindowThread();

		// get initial timer
		ROS_INFO("IMAGE_OCR Callback()");

		// get single frame
		IplImage* frame = bridge.imgMsgToCv(msg, "bgr8");

		if (!frame) {

			ROS_INFO("RECIEVED NULL FRAME!");
		}

		// do NOT release the frame!
		cvShowImage("OCR View", frame);

		// save image
		cvSaveImage("temp/capture.jpg", frame);

		/* Construct the command for Tesseract OCR and execute it*/
		std::ostringstream ocrCmdBuffer;
		ocrCmdBuffer.str("");

		/* Convert to tif for Tesseract */
		ocrCmdBuffer << "convert -auto-level -type Grayscale temp/capture.jpg temp/capture.tif";
		system(ocrCmdBuffer.str().data());

		/* Process image (tif) and save it to <imgname>.tesseract.txt */
		ocrCmdBuffer.str("");
		ocrCmdBuffer << "tesseract temp/capture.tif temp/capture.tesseract -l eng";
		system(ocrCmdBuffer.str().data());

		/* Load the output of the OCR.
		 * Dump it to the console and return it to the caller. */
		std::ifstream inputFile("temp/capture.tesseract.txt");


		std::cout << std::endl << std::endl <<"Read:" << std::endl << "---------------------------" << std::endl;
		std::ostringstream returnBuffer;
		returnBuffer.str("");
		while (!inputFile.eof() && !inputFile.fail()) {
			std::string line;
			std::getline(inputFile, line);
			std::cout << line << std::endl;
			returnBuffer << line << std::endl;
		}
		std::cout << "---------------------------" << std::endl;
		inputFile.clear();
		inputFile.close();

		cvDestroyWindow("OCR View");

	} catch (sensor_msgs::CvBridgeException& e) {

		ROS_ERROR("Could not convert from '%s' to 'bgr8'.",
				msg->encoding.c_str());
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "image_ocr");

	ros::NodeHandle nh;

	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("camera/rgb/image_color", 1,
			imageCallback);

	ros::spin();
}

