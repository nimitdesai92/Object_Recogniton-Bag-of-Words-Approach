//---------------------------------------------------------------------------
// FILE: 		Testing.cpp
//
// Author:
// Nimit Desai		<nimitdes@usc.edu>
// 
// University of Southern California
// LAST UPDATE:         Jan, 25, 2015
//---------------------------------------------------------------------------

#include "Library.h"

void pca_testProject(vector<Mat> TestDescriptor, vector<Mat> &TestPcafeature, PCA pca)
{
	// Projected Test Descriptors on the previously found PCA components
	for (int i = 0; i < 50; i++)
	{
		pca.project(TestDescriptor[i], TestPcafeature[i]);
	}
}

void hist_test(vector <Mat> TestDescriptor, vector<vector<DMatch>> matches, Mat &Testhistogram)
{
	// Constructed a histogram of test images.
	int a;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < TestDescriptor[i].rows; j++)
		{
			a = matches[i][j].trainIdx;
			Testhistogram.at<float>(i, a) = Testhistogram.at<float>(i, a) + 1;
		}
	}
}

void get_matches(vector<Mat> TestPcafeature, Mat Keyword, vector<vector<DMatch>> &matches)
{
	// Calculated Matches with L2 norm using Brute Force matches
	BFMatcher matcher(NORM_L2, false);
	for (int i = 0; i < 50; i++)
	{
		matcher.match(TestPcafeature[i], Keyword, matches[i]);
	}
}

void train_classifier(Mat histogram, Mat trainlabels, KNearest &knn)
{
	// Training K-nearest neighbour Classifier
	knn.train(histogram, trainlabels, cv::Mat(), false, 17);
}

void test_classify(Mat Testhistogram, Mat &predicted, KNearest knn)
{
	// Classifying Test Images based on trained Knn classifier
	for (int i = 0; i < Testhistogram.rows; i++)
	{
		Mat sample = Testhistogram.row(i);
		predicted.at<float>(i, 0) = knn.find_nearest(sample, 17);
	}

	cout << endl;
}