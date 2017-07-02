#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>

#define SEUIL 245
#define DEBUG 0

int main(int argc, char *argv[]){
	if(argc > 3){

		cv::Mat mat = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

		int w = std::strtol(argv[2], NULL, 10);
		int l = std::strtol(argv[3], NULL, 10);

		cv::Mat result;
		result.create(w, l, CV_8UC2);

		resize(mat, result, result.size(), 0, 0, cv::INTER_LANCZOS4);
		
		uint8_t currval = 0;
		int rowcount = 0;
		int row = 8, col = 0;
		int tmp;
		std::cout << "#include <avr/pgmspace.h>" << std::endl << std::endl;
		std::cout << "const uint8_t name[] PROGMEM = { " << std::endl;

		// Parse matrix for arduino
		while(col < result.cols){
			tmp = row;
			currval = 0;
		    for(int j = 0, row = tmp-8; j < 8 && row < result.rows; j++, row++){
		    	
		    	if(rowcount == 16) {
		    		std::cout << std::endl;
		    		rowcount = 0;
		    	}

		    	// Binarize matrix and compute currval
		        if (result.at<unsigned char>(row,col) < SEUIL){
		        	result.at<unsigned char>(row,col) = 0;
		        	currval += pow(2, j);
		        } else {
		        	result.at<unsigned char>(row,col) = 255;
		        }

		        // 0xFF print value when 8 pixel collected
		        if(j == 7 || row == result.rows-1){
#if DEBUG
		    		std::cout << " (" << static_cast<unsigned int>(currval) << ") ";
#endif
		    		std::cout << std::hex << "0x" << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(currval) << ", ";
					rowcount++;
		    	}
		    }
		    col ++;
		    if(row < result.rows && col == result.cols){
		    	col = 0;
		    	row += 8;
		    }
		}
		std::cout << "};" << std::endl;

		// Write image resize
		cv::imwrite("resize.jpeg", result);

	} else {
		std::cout << "Use " << argv[0] << " filename.jpg " << "width_result " << "height_result" << std::endl;
	}
}