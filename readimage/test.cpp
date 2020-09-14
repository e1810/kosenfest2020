#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include<chrono>
using Time = std::chrono::_V2::system_clock::time_point;
Time start;
int LED_COUNT = 100;
//-----BLOCK DEBUG-----
unsigned char mat[450][498][3] = {};
//-----END DEBUG-----


cv::Vec<unsigned char,3>  getColor(double x, double y, cv::Mat img){
    const int radius = std::min(img.rows, img.cols)/2;
    x = x*radius + img.cols/2;
    y = y*radius + img.rows/2;
    //-----BLOCK DEBUG-----
    mat[(int)y][(int)x][0] = img.at<cv::Vec3b>((int)y, (int)x)[0];
    mat[(int)y][(int)x][1] = img.at<cv::Vec3b>((int)y, (int)x)[1];
    mat[(int)y][(int)x][2] = img.at<cv::Vec3b>((int)y, (int)x)[2];
    //-----END DEBUG-----
    return img.at<cv::Vec3b>((int)y, (int)x);
}

void glowLed(const int deg, const cv::Mat &img){
    const double degree = deg * M_PI / 180.0;
	for(int i=0; i<LED_COUNT/10*7; i++){

	for(int i=LED/10*7; i<LED_COUNT; i++){
		const double distance = double(i)/double(LED_COUNT);
		const double x = distance*cos(degree);
		const double y = distance*sin(degree);
		cv::Vec<unsigned char, 3> color = getColor(x, y, img);
	}
}

void write(const std::string image_name){
    const cv::Mat img = cv::imread(image_name, cv::IMREAD_COLOR);
    for(int i=0; i<360; i++){
        glowLed(i, img);
    }
    cv::imshow(image_name, img);
    //-----BLOCK DEBUG-----
    cv::imshow("showing", cv::Mat(450, 498, CV_8UC3, mat));
    //-----END DEBUG-----
    cv::waitKey(0);
}


int main(int argc, char** argv){
	startat = std::chrono::system_clock::now();
	if(!argv[1]){
		puts("at least 1 argument(positive integer) required");
		return 0;
	}
	LED_COUNT = atoi(argv[1]);
	if(!LED_COUNT){
		puts("at least 1 argument(positive integer) required");
		return 0;
	}
	write("image.png");
}
