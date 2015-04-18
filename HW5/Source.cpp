//---------------------------------------------------------------------------
// FILE: 		Source.cpp
//
// Author:
// Nimit Desai		<nimitdes@usc.edu>
// 
// University of Southern California
// LAST UPDATE:         Jan, 25, 2015
//---------------------------------------------------------------------------

#include "Library.h"


int main(int argc, char **argv[])
{
	string name;
	vector<Mat>Images(100), TestImages(50);
	vector<Mat> Descriptor(100), TestDescriptor(50), TestPcafeature(50);
	vector<vector<KeyPoint>>Keypoints(100), TestKeypoint(50);
	Mat histogram = Mat::zeros(100, Cluster, CV_32F);
	Mat Testhistogram = Mat::zeros(50, Cluster, CV_32F);
	Mat Keyword = Mat::zeros(Cluster, 20, CV_32F);
	Mat full_Descriptor, Pcafeature, Pcaduplicate, clusteridx, trainlabels(100, 1, CV_32F);
	vector<vector<DMatch>> matches(50);
	Mat predicted(Testhistogram.rows, 1, CV_32F);

	// Read Training Images.
	read_train(Images, name);

	//Calculate SIFT features for the Training Images.
	calculate_SIFT(Images,Keypoints,Descriptor);
	merge_descriptor(full_Descriptor,Descriptor);

	//Compute PCA for all the features across all Images.
	PCA pca;
	perform_PCA(full_Descriptor, Pcafeature, pca);
	
	//Perform K-Means on all the PCA reduced features.
	Pcafeature.convertTo(Pcaduplicate, CV_32F);
	calculate_Kmeans(Pcaduplicate, clusteridx);

	//Calculate the Keywords in the Feature Space.
	make_dictionary(clusteridx, Pcaduplicate, Keyword);

	//Get the Histogram for each Training Image.
	hist(Descriptor, clusteridx, histogram);

	//Read Test Image
	read_test(TestImages, name);

	//Calculate the SIFT feature for all the test Images.
	calculate_SIFT(TestImages, TestKeypoint, TestDescriptor);

	//Project the SIFT feature of each feature on the lower dimensional PCA plane calculated above. 
	pca_testProject(TestDescriptor, TestPcafeature, pca);

	//Find the Label by searching for keywords closest to current feature.
	get_matches(TestPcafeature,Keyword,matches);

	//Calculate Histogram for each test Image.
	hist_test(TestDescriptor, matches, Testhistogram);
	
	//Perform classification through Knn Classifier. 
	train_labels(trainlabels);
	KNearest knn;
	train_classifier(histogram, trainlabels, knn);
	test_classify(Testhistogram,predicted,knn);

	//Calculate Accuracy for each class.
	calculate_accuracy(predicted);
	
	getchar();
	return 0;
}