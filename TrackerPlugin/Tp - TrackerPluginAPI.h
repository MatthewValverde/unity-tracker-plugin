#define TRACKER_PLUGIN_API __declspec(dllexport) 

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include<bitset>

#include "libTracker.h";

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <assert.h>
#include <math.h>
#include <vector>

#include "UnityPluginInterface.h"

using namespace std;

#pragma once

struct Faces
{
	Faces() {}
	float X, Y, Radius, Yaw, Pitch, Roll, IsOn;
};

struct Faces2
{
	Faces2() {}
	float X, Y, Radius, Yaw, Pitch, Roll, IsOn;
};

extern "C" {
	//TRACKER_PLUGIN_API FaceCenter faceCenters;

	TRACKER_PLUGIN_API int rtnstate = 0;
	TRACKER_PLUGIN_API Faces facesOrg[5];
	TRACKER_PLUGIN_API int scale = 1;
	TRACKER_PLUGIN_API cv::Mat testImage;
	TRACKER_PLUGIN_API int frameCount = 0;
	TRACKER_PLUGIN_API int TestSort(int a[], int length);
	TRACKER_PLUGIN_API int Init();
	TRACKER_PLUGIN_API void Close();
	TRACKER_PLUGIN_API void SetScale(int scale);
	TRACKER_PLUGIN_API int SetData(int w, int h, cv::Mat frame);
	TRACKER_PLUGIN_API uchar* SetData6();
	TRACKER_PLUGIN_API int Tracking(int w, int h, void *data, Faces* facesPointer, int testNumber);
	TRACKER_PLUGIN_API int Tracking2(int w, int h, void *data, Faces2* facesPointer2, int testNumber);
}