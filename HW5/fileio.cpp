//---------------------------------------------------------------------------
// FILE: 		fileio.cpp
//
// Author:
// Nimit Desai		<nimitdes@usc.edu>
// 
// University of Southern California
// LAST UPDATE:         Jan, 25, 2015
//---------------------------------------------------------------------------

#include "Library.h"

void readmul(string path, int number, vector<Mat> &Images, string name)
{
	for (int i = 0; i <= 8; i++)
	{
		name = path + "/image_000" + to_string(i + 1) + ".jpg";
		Images[i + number] = imread(name);
	}

	for (int i = 9; i <= 19; i++)
	{
		name = path + "/image_00" + to_string(i + 1) + ".jpg";
		Images[i + number] = imread(name);
	}
}

void readmultest(string path, int number, vector<Mat> &TestImages, string name)
{

	for (int i = 20; i <= 29; i++)
	{
		name = path + "/image_00" + to_string(i + 1) + ".jpg";
		TestImages[i - 20 + number] = imread(name);
	}
}

void read_train(vector<Mat> &Images, string name)
{
	// Read Training Images.
	string path1 = ("training/car");
	readmul(path1, 0, Images, name);
	string path2 = ("training/cougar");
	readmul(path2, 20, Images, name);
	string path3 = ("training/face");
	readmul(path3, 40, Images, name);
	string path4 = ("training/pizza");
	readmul(path4, 60, Images, name);
	string path5 = ("training/sunflower");
	readmul(path5, 80, Images, name);
}

void read_test(vector<Mat> &TestImages, string name)
{
	//Read Test Image
	string path6 = ("testing/car");
	readmultest(path6, 0, TestImages, name);
	string path7 = ("testing/cougar");
	readmultest(path7, 10, TestImages, name);
	string path8 = ("testing/face");
	readmultest(path8, 20, TestImages, name);
	string path9 = ("testing/pizza");
	readmultest(path9, 30, TestImages, name);
	string path10 = ("testing/sunflower");
	readmultest(path10, 40, TestImages, name);
}

void calculate_accuracy(Mat predicted)
{
	float car = 0, cougar = 0, face = 0, pizza = 0, sunflower = 0;
	for (int i = 0; i < predicted.rows; i++)
	{
		if (i < (predicted.rows / 5))
		{
			if (predicted.at<float>(i, 0) == 0)
				car++;
		}
		if (i < (2 * predicted.rows / 5) && i >= (predicted.rows / 5))
		{
			if (predicted.at<float>(i, 0) == 1)
				cougar++;
		}
		if (i < (3 * predicted.rows / 5) && i >= (2 * predicted.rows / 5))
		{
			if (predicted.at<float>(i, 0) == 2)
				face++;
		}
		if (i < (4 * predicted.rows / 5) && i >= (3 * predicted.rows / 5))
		{
			if (predicted.at<float>(i, 0) == 3)
				pizza++;
		}
		else
		{
			if (predicted.at<float>(i, 0) == 4)
				sunflower++;
		}
	}

	cout << "Number of Cluster " << Cluster << "  Number of PCA is 20 " << "  Number of K in Knn is 17" << endl;
	cout << "Car Testing Accuracy % " << (car * 10) << endl;
	cout << "Cougar Testing Accuracy % " << (cougar * 10) << endl;
	cout << "Face Testing Accuracy % " << (face * 10) << endl;
	cout << "Pizza Testing Accuracy % " << (pizza * 10) << endl;
	cout << "Sunflower Testing Accuracy % " << (sunflower * 10) << endl;
	cout << "Total Accuracy % is " << ((car + cougar + face + pizza + sunflower) * 2) << endl;
}