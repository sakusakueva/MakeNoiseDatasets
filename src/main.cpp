#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#define SIGMA 5

/*=============   TODO   ===============*/
/*画像サイズを変えること                */
/*GTを修正すること                      */
/*入力画像にノイズを付与すること        */
/*テンプレート画像にノイズを付与すること*/
/*======================================*/

void AddNoiseMono(const cv::Mat &src, cv::Mat &dst);
void AddNoise(const cv::Mat &src, cv::Mat &dst);

int main(void){
	// Template image
	cv::Mat temp_img = cv::imread("template.png", 1);
	cv::Mat temp_img_r, temp_img_rn;
	temp_img_r = temp_img.clone();
	//cv::resize(temp_img, temp_img_r, cv::Size(), 0.5, 0.5);
	//cv::imwrite("template_re.png", temp_img_r);

	// Add Noise
	AddNoise(temp_img_r, temp_img_rn);
	cv::imwrite("template_dst.png", temp_img_rn);

	for(int i = 0; i < 1000; i++){
		// Input image
		std::stringstream ss;
		ss << "test/input" << std::setfill('0') << std::setw(3) << std::right << i << ".png";
		std::string input_fname = ss.str();
		cv::Mat input_img = cv::imread(input_fname, 1);

		cv::Mat input_img_r, input_img_rn;
		input_img_r = input_img.clone();
		//cv::resize(input_img, input_img_r, cv::Size(), 0.5, 0.5);

		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << "test_re/input" << std::setfill('0') << std::setw(3) << std::right << i << ".png";
		//cv::imwrite(ss.str(), input_img_r);

		// Add Noise
		AddNoise(input_img_r, input_img_rn);
		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << "test_dst/input" << std::setfill('0') << std::setw(3) << std::right << i << ".png";
		cv::imwrite(ss.str(), input_img_rn);

		// GT txt
		/*ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << "testGT/input" << std::setfill('0') << std::setw(3) << std::right << i << ".txt";
		std::string gt_fname = ss.str();
		std::ifstream in_gt_txt(gt_fname);
		if (!in_gt_txt.is_open()) {
			std::cerr << "Could not open the file - '" << gt_fname << "'" << std::endl;
			return EXIT_FAILURE;
		}
		int num, dst_posi[2];
		int n = 0;
		while(in_gt_txt >> num){
			std::cout << num << ";";
			dst_posi[n] = (int)((double)num/2.0);
			n++;
		}
		std::cout << std::endl;
		in_gt_txt.close();

		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << "testGT_dst_re/input" << std::setfill('0') << std::setw(3) << std::right << i << ".txt";
		std::ofstream out_gt_txt(ss.str());
		out_gt_txt << dst_posi[0] << " " << dst_posi[1];
		out_gt_txt.close();
		*/
	}

	for(int i = 0; i < 10; i++){
		// Input image
		std::stringstream ss;
		ss << "detect/input" << i << ".png";
		std::string input_fname = ss.str();
		cv::Mat input_img = cv::imread(input_fname, 1);

		cv::Mat input_img_r, input_img_rn;
		input_img_r = input_img.clone();
		//cv::resize(input_img, input_img_r, cv::Size(), 0.5, 0.5);

		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << "detect_re/input" << i << ".png";
		//cv::imwrite(ss.str(), input_img_r);

		// Add Noise
		AddNoise(input_img_r, input_img_rn);
		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << "detect_dst/input" << std::setfill('0') << std::setw(3) << std::right << i << ".png";
		cv::imwrite(ss.str(), input_img_rn);
	}
	return 0;
}

void AddNoiseMono(const cv::Mat &src, cv::Mat &dst){
	cv::Mat s;
	src.convertTo(s, CV_16S);
	cv::Mat n(s.size(), CV_16S);
	cv::randn(n, 0, SIGMA);
	cv::Mat temp = s + n;
	temp.convertTo(dst, CV_8U);
}

void AddNoise(const cv::Mat &src, cv::Mat &dst){
	std::vector<cv::Mat> s;
	std::vector<cv::Mat> d(src.channels());
	cv::split(src, s);
	for (int i = 0; i < src.channels(); i++)
	{
		AddNoiseMono(s[i], d[i]);
	}
	cv::merge(d, dst);
	return;
}