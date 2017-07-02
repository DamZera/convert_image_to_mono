#include <opencv2/opencv.hpp>

#define SEUIL 245

int main(int argc, char *argv[]){
	if(argc > 3){

		cv::Mat mat = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
		std::cout << "rows: " << mat.rows << " cols: " << mat.cols << std::endl;

		int w = std::strtol(argv[2], NULL, 10);
		int l = std::strtol(argv[3], NULL, 10);

		cv::Mat result;
		result.create(w, l, CV_8UC2);

		resize(mat, result, result.size(), 0, 0, cv::INTER_LINEAR);
		
		for(int i = 0; i < result.rows; i++){
		    unsigned char* mi = result.ptr<unsigned char>(i);
		    for(int j = 0; j < result.cols; j++){
		        if (mi[j] < SEUIL) mi[j] = 0;
		        else mi[j] = 255;
		    }
		}

		cv::imwrite("resized.jpg", result);

	} else {
		std::cout << "Use " << argv[0] << " filename.jpg" << "width_result" << "height_result" << std::endl;
	}
}