//---------------------------------------------------------------------------
// FILE: 		Training.cpp
//
// Author:
// Nimit Desai		<nimitdes@usc.edu>
// 
// University of Southern California
// LAST UPDATE:         Jan, 25, 2015
//---------------------------------------------------------------------------

#include "Library.h"

void calculate_SIFT(vector<Mat> Images, vector<vector<KeyPoint>> &Keypoints, vector<Mat> &Descriptor)
{
	// Used SIFT to get the Keypoints.
	SIFT sift;
	cout << "Starting SIFT" << endl;
	for (unsigned int i = 0; i < Images.size(); i++)
	{
		sift(Images[i], noArray(), Keypoints[i], Descriptor[i]);
	}
}

void merge_descriptor(Mat &full_Descriptor, vector<Mat> Descriptor)
{
	// Merge all training Descriptor to form one Training Descriptor
	for (unsigned int i = 0; i < Descriptor.size(); i++)
	{
		full_Descriptor.push_back(Descriptor[i]);
	}
}

void perform_PCA(Mat full_Descriptor, Mat &Pcafeature, PCA &pca)
{
	// Applied Priciple Component Analysis to reduce SIFT feature Dimension from 128 to 20.
	pca(full_Descriptor, noArray(), CV_PCA_DATA_AS_ROW, 20);
	cout << "Train PCA Complete" << endl;

	pca.project(full_Descriptor, Pcafeature);
	cout << "Train Projection Done" << endl;
}

void calculate_Kmeans(Mat Pcaduplicate, Mat &clusteridx)
{
	// Applied K-Means Clustering to similar Key-Points.
	kmeans(Pcaduplicate, Cluster, clusteridx, TermCriteria(CV_TERMCRIT_ITER, 10000, 0.01), 1, KMEANS_PP_CENTERS);
	cout << "Training kMeans Complete" << endl;
}

void make_dictionary(Mat clusteridx, Mat Pcaduplicate, Mat &Keyword)
{
	// Constructed a Codebook of Keywords from Cluster Centres.
	int count;
	for (int i = 0; i < Cluster; i++)
	{
		count = 0;
		for (int j = 0; j < clusteridx.rows; j++)
		{
			if (clusteridx.at<int>(j) == i)
			{
				Keyword.row(i) += Pcaduplicate.row(j);
				count++;
			}
		}
		Keyword.row(i) = Keyword.row(i) / count;
	}
}

void hist(vector<Mat> Descriptor, Mat clusteridx, Mat &histogram)
{
	// Construction of Histogram from Codebook.
	int m = 0, count, a;
	for (unsigned int i = 0; i < Descriptor.size(); i++)
	{
		count = 0;
		while (count < Descriptor[i].rows)
		{
			a = clusteridx.at<int>(m);
			histogram.at<float>(i, a) = histogram.at<float>(i, a) + 1;
			count++;
			m++;
		}
	}
}

void train_labels(Mat &trainlabels)
{
	// Assigned Training Label
	for (int i = 0; i < 100; i++)
	{
		if (i < 20)
			trainlabels.at <float>(i) = 0;
		else if (i >= 20 && i < 40)
			trainlabels.at<float>(i) = 1;
		else if (i >= 40 && i < 60)
			trainlabels.at<float>(i) = 2;
		else if (i >= 60 && i < 80)
			trainlabels.at<float>(i) = 3;
		else
			trainlabels.at<float>(i) = 4;
	}
}