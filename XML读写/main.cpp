#include <iostream>
#include <vector>
using namespace std;

#include <opencv2\opencv.hpp>
#include <opencv2\xfeatures2d.hpp>
using namespace cv;
using namespace xfeatures2d;
  
const int NUM_OF_PICTURES = 41;
const String XML_FILE_NAME = "TempletInformation-600px.xml";

int main()
{
	Ptr<SurfFeatureDetector> detector
		= SurfFeatureDetector::create(800);		// Surf���������
	Ptr<SurfDescriptorExtractor> descriptor_extractor
		= SurfDescriptorExtractor::create(800);	// Surf��������������

	Mat img;
	vector<KeyPoint> key_points;		// ������洢vector
	Mat descriptor;

	FileStorage fs_write(XML_FILE_NAME, FileStorage::WRITE);
	fs_write << "NumOfPictures" << NUM_OF_PICTURES;

	String file_no;			// �ļ����
	String file_name;		// �ļ�����
	String file_path;		// �ļ�·��
	String img_mat_name;	// ͼƬ��������
	String img_key_points_name;		// ͼƬ������vector����
	String img_descriptor_name;		// ͼƬ������������

	double sum_of_time = 0.0;		// SURF����ʱ
	double t;

	for (int i = 0; i < NUM_OF_PICTURES; i++)
	{
		stringstream ss;
		ss << i;
		cout << ss.str() << endl;
		file_no = ss.str();
		file_name = file_no + ".jpg";
		file_path = "ProcessedImage-600px\\" + file_name;
		img_mat_name = "ImgMat" + file_no;
		img_key_points_name = "KeyPoints" + file_no;
		img_descriptor_name = "Descriptor" + file_no;

		img = imread(file_path);
		if (img.empty())
		{
			cout << file_name << " read false!\n";
			return -1;
		}
		
		t = getTickCount();		//��ǰ�δ���
		detector->detect(img, key_points);
		descriptor_extractor->compute(img, key_points, descriptor);
		t = ((double)getTickCount() - t) / getTickFrequency();
		cout << "��ʱ��" << t << "��" << endl;
		sum_of_time += t;
		cout << "Ŀǰ����ʱ��" << sum_of_time << "��" << endl;
		
		//fs_write << img_mat_name << img;
		fs_write << img_key_points_name << key_points;
		fs_write << img_descriptor_name << descriptor;
		
		Mat img_key;
		drawKeypoints(img, key_points, img_key, CV_RGB(255, 0, 0));
		imshow("KeyPoints", img_key);
		
		waitKey();
	}
	cout << "ƽ����ʱ: " << sum_of_time / NUM_OF_PICTURES << endl;
	fs_write.release();

	/*
	Mat img_copy;
	vector<KeyPoint> key_points_copy;
	Mat descripter_copy;

	FileStorage fs_read(XML_FILE_NAME, FileStorage::READ);

	for (int i = 0; i < NUM_OF_PICTURES; i++)
	{
		stringstream ss;
		ss << i;
		cout << ss.str() << endl;
		file_no = ss.str();
		file_name = file_no + ".jpg";
		file_path = "ProcessedImage-600px\\" + file_name;
		img_mat_name = "ImgMat" + file_no;
		img_key_points_name = "KeyPoints" + file_no;
		img_descriptor_name = "Descriptor" + file_no;

		//fs_read[img_mat_name] >> img_copy;
		fs_read[img_key_points_name] >> key_points_copy;
		fs_read[img_descriptor_name] >> descripter_copy;
		
		//Mat img_key_copy;
		//drawKeypoints(img_copy, key_points_copy, img_key_copy, CV_RGB(255, 0, 0));
		//imshow("KeyPointsCopy", img_key_copy);

		waitKey();
	}
	fs_read.release();
	*/

	return 0;
}