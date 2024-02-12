#define ULSEE_PLUGIN_API __declspec(dllexport) 

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <bitset>

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

struct FaceCenter
{
	FaceCenter() {}
	float X, Y, Radius, Yaw, Pitch, Roll, TopX, TopY, Width, Height, IsOn;
	//FaceCenter(float x, float y, float radius) : X(x), Y(y), Radius(radius) {}
};

struct Points
{
	Points() {}
	float pt0, pt1, pt2, pt3, pt4, pt5, pt6, pt7, pt8, pt9, pt10, pt11, pt12, pt13, pt14, pt15, pt16, pt17, pt18, pt19, pt20, pt21, pt22, pt23, pt24, pt25, pt26, pt27, pt28, pt29, pt30, pt31, pt32, pt33, pt34, pt35, pt36,
		pt37, pt38, pt39, pt40, pt41, pt42, pt43, pt44, pt45, pt46, pt47, pt48, pt49, pt50, pt51, pt52, pt53, pt54, pt55, pt56, pt57, pt58, pt59, pt60, pt61, pt62, pt63, pt64, pt65, pt66, pt67, pt68, pt69, pt70, pt71, pt72, pt73, pt74, pt75, pt76, pt77, pt78, pt79, pt80,
		pt81, pt82, pt83, pt84, pt85, pt86, pt87, pt88, pt89, pt90, pt91, pt92, pt93, pt94, pt95, pt96, pt97, pt98, pt99, pt100, pt101, pt102, pt103, pt104, pt105, pt106, pt107, pt108, pt109, pt110, pt111, pt112, pt113, pt114, pt115, pt116, pt117, pt118, pt119,
		pt120, pt121, pt122, pt123, pt124, pt125, pt126, pt127, pt128, pt129, pt130, pt131, pt132;

	float pt3D0, pt3D1, pt3D2, pt3D3, pt3D4, pt3D5, pt3D6, pt3D7, pt3D8, pt3D9, pt3D10, pt3D11, pt3D12, pt3D13, pt3D14, pt3D15, pt3D16, pt3D17, pt3D18, pt3D19, pt3D20, pt3D21, pt3D22, pt3D23, pt3D24, pt3D25, pt3D26, pt3D27, pt3D28, pt3D29, pt3D30, pt3D31, pt3D32, pt3D33, pt3D34, pt3D35, pt3D36,
		pt3D37, pt3D38, pt3D39, pt3D40, pt3D41, pt3D42, pt3D43, pt3D44, pt3D45, pt3D46, pt3D47, pt3D48, pt3D49, pt3D50, pt3D51, pt3D52, pt3D53, pt3D54, pt3D55, pt3D56, pt3D57, pt3D58, pt3D59, pt3D60, pt3D61, pt3D62, pt3D63, pt3D64, pt3D65, pt3D66, pt3D67, pt3D68, pt3D69, pt3D70, pt3D71, pt3D72,
		pt3D73, pt3D74, pt3D75, pt3D76, pt3D77, pt3D78, pt3D79, pt3D80, pt3D81, pt3D82, pt3D83, pt3D84, pt3D85, pt3D86, pt3D87, pt3D88, pt3D89, pt3D90, pt3D91, pt3D92, pt3D93, pt3D94, pt3D95, pt3D96, pt3D97, pt3D98, pt3D99, pt3D100, pt3D101, pt3D102, pt3D103, pt3D104, pt3D105, pt3D106, pt3D107,
		pt3D108, pt3D109, pt3D110, pt3D111, pt3D112, pt3D113, pt3D114, pt3D115, pt3D116, pt3D117, pt3D118, pt3D119, pt3D120, pt3D121, pt3D122, pt3D123, pt3D124, pt3D125, pt3D126, pt3D127, pt3D128, pt3D129, pt3D130, pt3D131, pt3D132, pt3D133, pt3D134, pt3D135, pt3D136, pt3D137, pt3D138, pt3D139,
		pt3D140, pt3D141, pt3D142, pt3D143, pt3D144, pt3D145, pt3D146, pt3D147, pt3D148, pt3D149, pt3D150, pt3D151, pt3D152, pt3D153, pt3D154, pt3D155, pt3D156, pt3D157, pt3D158, pt3D159, pt3D160, pt3D161, pt3D162, pt3D163, pt3D164, pt3D165, pt3D166, pt3D167, pt3D168, pt3D169, pt3D170, pt3D171,
		pt3D172, pt3D173, pt3D174, pt3D175, pt3D176, pt3D177, pt3D178, pt3D179, pt3D180, pt3D181, pt3D182, pt3D183, pt3D184, pt3D185, pt3D186, pt3D187, pt3D188, pt3D189, pt3D190, pt3D191, pt3D192, pt3D193, pt3D194, pt3D195, pt3D196, pt3D197, pt3D198;
};

extern "C" {
	ULSEE_PLUGIN_API int rtnstate = 0;
	ULSEE_PLUGIN_API FaceCenter facesOrg[5];
	ULSEE_PLUGIN_API int scale = 1;
	ULSEE_PLUGIN_API cv::Mat testImage;
	ULSEE_PLUGIN_API int frameCount = 0;
	ULSEE_PLUGIN_API int TestSort(int a[], int length);
	ULSEE_PLUGIN_API int Init();
	ULSEE_PLUGIN_API void Close();
	ULSEE_PLUGIN_API void SetScale(int scale);
	ULSEE_PLUGIN_API int SetData(int w, int h, cv::Mat frame);
	ULSEE_PLUGIN_API uchar* SetData6();
	ULSEE_PLUGIN_API int Tracking(int w, int h, void* data, FaceCenter *faceCenters, Points *pointsInt, int testNumber);
}