#include <iostream>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

int main()
{
	//string xmlPath = "D:\\Program Files (x86)\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml";
	//string xmlPath = "D:\\Program Files (x86)\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	string xmlPath = "D:\\Program Files (x86)\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml";
	//string xmlPath = "D:\\Program Files (x86)\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt_tree.xml";
	CascadeClassifier ccf;   //��������������
	if (!ccf.load(xmlPath))   //����ѵ���ļ�
	{
		cout << "���ܼ���ָ����xml�ļ�" << endl;
		return 0;
	}
	vector<Rect> faces;  //����һ�������������������

	// ���һ��ͼƬ
	Mat img = imread("C:\\Users\\mengf\\Pictures\\����Ƭ\\1.jpg");
	resize(img, img, img.size() / 3);
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	ccf.detectMultiScale(img_gray, faces, 1.1, 3, 0, Size(5, 5), Size(500, 500));
	for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
	{
		rectangle(img, *iter, Scalar(0, 0, 255), 2, 8); //������������
		rectangle(img_gray, *iter, Scalar(255, 255, 255));
	}
	imshow("Picture Color", img);
	imshow("Picture Gray", img_gray);
	while (true)
	{
		if (waitKey(10) >= 0) break;
	}
	return 0;
}