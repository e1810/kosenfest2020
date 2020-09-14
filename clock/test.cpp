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
	

void glowLed(const int deg){
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
		// TODO nin, six, thr を実装
	}
}

void write(){
    for(int i=0; i<360; i++){
        glowLed(i);
    }
    //-----BLOCK DEBUG-----
    cv::imshow("showing", cv::Mat(HEIGHT, WIDTH, CV_8UC3, mat));
    //-----END DEBUG-----
    cv::waitKey(0);
}


int main(int argc, char** argv){
	startat = system_clock::now();
	write();	// == void loop() {}
}
