//---------------------------------------------------------------------------
// FILE: 		Library.h
//
// Author:
// Nimit Desai		<nimitdes@usc.edu>
// 
// University of Southern California
// LAST UPDATE:         Jan, 25, 2015
//---------------------------------------------------------------------------

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\nonfree\features2d.hpp"
#include "opencv2\ml\ml.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

#define Cluster 100


void readmul(string path, int number, vector<Mat> &Images, string name);
void readmultest(string path, int number, vector<Mat> &TestImages, string name);
void read_train(vector<Mat> &Images, string name);
void read_test(vector<Mat> &TestImages, string name);
void calculate_SIFT(vector<Mat> Images, vector<vector<KeyPoint>> &Keypoints, vector<Mat> &Descriptor);
void merge_descriptor(Mat &full_Descriptor, vector<Mat> Descriptor);
void perform_PCA(Mat full_Descriptor, Mat &Pcafeature, PCA &pca);
void calculate_Kmeans(Mat Pcaduplicate, Mat &clusteridx);
void make_dictionary(Mat clusteridx, Mat Pcaduplicate, Mat &Keyword);
void hist(vector<Mat> Descriptor, Mat clusteridx, Mat &histogram);
void pca_testProject(vector<Mat> TestDescriptor, vector<Mat> &TestPcafeature, PCA pca);
void hist_test(vector <Mat> TestDescriptor, vector<vector<DMatch>> matches, Mat &Testhistogram);
void get_matches(vector<Mat> TestPcafeature, Mat Keyword, vector<vector<DMatch>> &matches);
void train_labels(Mat &trainlabels);
void train_classifier(Mat histogram, Mat trainlabels, KNearest &knn);
void test_classify(Mat Testhistogram, Mat &predicted, KNearest knn);
void calculate_accuracy(Mat predicted);