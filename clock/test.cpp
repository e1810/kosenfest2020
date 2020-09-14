#include <iostream>
//-----BLOCK DEBUG-----
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
//-----END DEBUG-----
#include<time.h>

int LED_COUNT = 12;

//-----BLOCK DEBUG-----
const int HEIGHT = 450;
const int WIDTH = 498;
unsigned char mat[HEIGHT][WIDTH][3] = {};
//-----END DEBUG-----


bool getTimeChar(int num, int x, int y){
	std::string time_char[6];
	if(num==3){			// 左向き
		time_char[0] = "......############...";
		time_char[1] = "......############...";
		time_char[2] = "......##..##....##...";
		time_char[3] = "......##..##....##...";
		time_char[4] = "......##..##....##...";
		time_char[5] = "......##..##....##...";
	}else if(num==6){		// 逆向き
		time_char[0] = "......#########......";
		time_char[1] = "......###...###......";
		time_char[2] = "......#########......";
		time_char[3] = "............###......";
		time_char[4] = "............###......";
		time_char[5] = "......#########......";
	}else if(num==9){		// 右向き
		time_char[0] = "...##....######......";
		time_char[1] = "...##....######......";
		time_char[2] = "...##....##..##......";
		time_char[3] = "...##....##..##......";
		time_char[4] = "...##....######......";
		time_char[5] = "...############......";
	}else if(num==12){		// 正向き
		time_char[0] = "...###...#########...";
		time_char[1] = "...###.........###...";
		time_char[2] = "...###...#########...";
		time_char[3] = "...###...###.........";
		time_char[4] = "...###...###.........";
		time_char[5] = "...###...#########...";
	}
	return (time_char[5-x][20-y] == '#');
}


void glowLed(int deg){
	time_t _now = time(0);
	tm *now = localtime(&_now);
	int hour_deg = (60 * now->tm_hour + now->tm_min) / 4;
	hour_deg = (540 - hour_deg) % 360;
	int minute_deg = (now->tm_min) * 6;
	minute_deg = (540 - minute_deg) % 360;

	for(int i=0; i<12; i++){
		bool color = 0;
		if(i<4 && deg==hour_deg) color = true;
		if(i<6 && deg==minute_deg) color = true;
		if(i>=6){
			if(80<=deg && deg <=100) color = getTimeChar(3, i-6, deg-80);
			if(350<=deg || deg<=10) color = getTimeChar(6, i-6, (deg+10)%360);
			if(260<=deg && deg<=280) color = getTimeChar(9, i-6, deg-260);
			if(170<=deg && deg<=190) color = getTimeChar(12, i-6, deg-170);
		}

		//-----BLOCK DEBUG-----
		const double distance = double(i)/double(LED_COUNT);
    	const double radian = deg * M_PI / 180.0;
		const double X = distance*cos(radian);
		const double Y = distance*sin(radian);
		const int radius = std::min(HEIGHT, WIDTH)/2;
		int x = X*radius + HEIGHT/2, y = Y*radius + WIDTH/2;
		mat[x][y][0] = std::max<unsigned>(mat[x][y][0], color*255);
		mat[x][y][1] = std::max<unsigned>(mat[x][y][0], color*255);
		mat[x][y][2] = std::max<unsigned>(mat[x][y][2], color*255);
		//-----END DEBUG-----
	}
}

void write(){
    for(int i=0; i<360; i++){
        glowLed(i);
    }
    //-----BLOCK DEBUG-----
	time_t _now = time(0);
	tm *now = localtime(&_now);
	std::string time = std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min);
    cv::imshow(time, cv::Mat(HEIGHT, WIDTH, CV_8UC3, mat));
    cv::waitKey(0);
    //-----END DEBUG-----
}


int main(int argc, char** argv){
	write();	// == void loop() {}
}
