#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include<chrono>
using std::chrono::_V2::system_clock;

system_clock::time_point startat;
int LED_COUNT = 12;

//-----BLOCK DEBUG-----
const int HEIGHT = 450;
const int WIDTH = 498;
unsigned char mat[HEIGHT][WIDTH][3] = {};
//-----END DEBUG-----


void twe(int twe_x, int twe_y, double degree, double x, double y){
	std::string twe_char[6] = {
		"...###...#########...",
		"...###.........###...",
		"...###...#########...",
		"...###...###.........",
		"...###...###.........",
		"...###...#########..."
	};
	const int radius = std::min(HEIGHT, WIDTH)/2;
	x = x*radius + WIDTH/2;
	y = y*radius + HEIGHT/2;
	int color = (twe_char[5-twe_x][20-twe_y]=='#')? 255:0;
	mat[(int)x][(int)y][0] = mat[(int)x][(int)y][1] = mat[(int)x][(int)y][2] = color;
}
	

void glowLed(const int deg, const cv::Mat &img){
    const double degree = deg * M_PI / 180.0;
	for(int i=0; i<6; i++){
	}

	for(int i=6; i<12; i++){
		const double distance = double(i)/double(LED_COUNT);
		const double x = distance*cos(degree);
		const double y = distance*sin(degree);
		if(80<=deg && deg<=100){
			twe(i-6, deg-80, degree, x, y);
		}
	}
}

void write(const std::string image_name){
    const cv::Mat img = cv::imread(image_name, cv::IMREAD_COLOR);
    for(int i=0; i<360; i++){
        glowLed(i, img);
    }
    cv::imshow(image_name, img);
    //-----BLOCK DEBUG-----
    cv::imshow("showing", cv::Mat(HEIGHT, WIDTH, CV_8UC3, mat));
    //-----END DEBUG-----
    cv::waitKey(0);
}


int main(int argc, char** argv){
	startat = system_clock::now();
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
