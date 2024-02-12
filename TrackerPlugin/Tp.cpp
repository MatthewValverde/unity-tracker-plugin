#include "Tp.h";

extern "C" {
	int Init()
	{
		//Init Tracker with model and key
		int rtnValue = ULS_TrackerInit("./model/", "e9f7xxphqp7F9TWcWJCouzFpbfQozp1I", 5, 0, 40);

		if (rtnValue == -33) {
			//qDebug() << "NOT FOUND!!!!";
			return rtnValue;
		}
		else {
			//qDebug() << "GOOD";
		}

		ULS_SetSmooth(false);
		ULS_SetTwoThresholds(0.27f, 0.33f);

		//ULS_SetTwoThresholds(0.25f, 0.25f);
		ULS_SetTwoThresholds(0.25f, 0.28f);

		return 11;
	}

	int arr[] = { Points().pt0, 2, 3, 4 };

	int Tracking(int w, int h, void *data, FaceCenter *faceCenters, Points *pointsInt, int testNumber) {
		/*cv::Mat frame(cv::Size(w, h), CV_8UC4, data);
		cv::Mat grayscaleFrame;
		cvtColor(frame, grayscaleFrame, cv::COLOR_RGB2GRAY);*/

		cv::Mat frame(cv::Size(w, h), CV_8UC4, data);
		cv::Mat flippedFrame;
		// Flip the frame vertically (0 means flipping around the x-axis)
		cv::flip(frame, flippedFrame, 0);

		cv::Mat grayscaleFrame;
		// Convert the flipped frame to grayscale
		cv::cvtColor(flippedFrame, grayscaleFrame, cv::COLOR_RGB2GRAY);

		int results[5];

		int rtnstate;
		float yawAngle;

		if (testNumber == 2) {
			imshow("OUTPUT 2 - 1 Tracking", grayscaleFrame);
			return 0;
		}

		int c = 0;
		rtnstate = ULS_TrackerProcessByte((void*)grayscaleFrame.data, grayscaleFrame.cols, grayscaleFrame.rows, 0, 0, &yawAngle);

		int counter = 0;

		//draw results
		if (rtnstate < 0) {
			return 0;
		}
		else if (rtnstate >= 0) {
			int n = ULS_GetTrackerPointNum();
			for (int j = 0; j < 5; j++) {

				const float* pts = ULS_GetTrackerPoint(j);

				const float* pts3d = ULS_GetTrackerPoint3D(j);

				faceCenters[j].IsOn = 0;

				if (pts == NULL) {
					continue;
				}

				int fx, fy, fw, fh;

				bool faceRectResult = ULS_GetTrackerFacerect(j, fx, fy, fw, fh);

				if (!faceRectResult) {
					continue;
				}

				// face center
				float imx, imy;
				ULS_GetFaceCenter(imx, imy, j);

#if 0
				// without pose stability
				float pitch = ULS_GetPitchRadians(j);
				float yaw = ULS_GetYawRadians(j);
				float roll = ULS_GetRollRadians(j);
#else
				// with pose stability
				float pitch = ULS_GetStablePitchRadians(j);
				float yaw = ULS_GetStableYawRadians(j);
				float roll = ULS_GetStableRollRadians(j);
#endif			
				cv::Point2f pupils[2];
				ULS_GetLeftPupilXY(pupils[0].x, pupils[0].y, j);
				ULS_GetRightPupilXY(pupils[1].x, pupils[1].y, j);

				cv::Point3f gazes[2];
				ULS_GetLeftGaze(gazes[0].x, gazes[0].y, gazes[0].z, j);
				ULS_GetRightGaze(gazes[1].x, gazes[1].y, gazes[1].z, j);

				float hx, hy, hz;
				ULS_GetHead3DPosition(hx, hy, hz, j);

				float hxCC, hyCC, hzCC;
				ULS_GetHead3DPositionCC(hxCC, hyCC, hzCC, j);

				float faceScale;
				faceScale = ULS_GetScaleInImage(j);

				int lX = pts[0];
				int ly = pts[1];
				int rX = pts[32];
				int ry = pts[33];

				int noseX = pts[56];
				int noseY = pts[57];

				int lipX = pts[102];
				int lipY = pts[103];

				//cv::circle(frame, pupils[0], 12, CV_RGB(255, 0, 0));
				//cv::circle(frame, pupils[1], 12, CV_RGB(0, 255, 0));
				//cv::circle(frame, cv::Point2f(imx, imy), 12, CV_RGB(255, 255, 0));
				//const float* pt = pts;
				//int pointNum = ULS_GetTrackerPointNum();

				results[j] = imx;
				faceCenters[j].X = imx;
				faceCenters[j].Y = imy;
				faceCenters[j].Pitch = pitch;
				faceCenters[j].Roll = roll;
				faceCenters[j].Yaw = yaw;
				faceCenters[j].TopX = fx;
				faceCenters[j].TopY = fy;
				faceCenters[j].Width = fw;
				faceCenters[j].Height = fh;
				faceCenters[j].IsOn = 1;

				pointsInt[j].pt0 = pts[0];
				pointsInt[j].pt1 = pts[1];
				pointsInt[j].pt2 = pts[2];
				pointsInt[j].pt3 = pts[3];
				pointsInt[j].pt4 = pts[4];
				pointsInt[j].pt5 = pts[5];
				pointsInt[j].pt6 = pts[6];
				pointsInt[j].pt7 = pts[7];
				pointsInt[j].pt8 = pts[8];
				pointsInt[j].pt9 = pts[9];

				pointsInt[j].pt10 = pts[10];
				pointsInt[j].pt11 = pts[11];
				pointsInt[j].pt12 = pts[12];
				pointsInt[j].pt13 = pts[13];
				pointsInt[j].pt14 = pts[14];
				pointsInt[j].pt15 = pts[15];
				pointsInt[j].pt16 = pts[16];
				pointsInt[j].pt17 = pts[17];
				pointsInt[j].pt18 = pts[18];
				pointsInt[j].pt19 = pts[19];

				pointsInt[j].pt20 = pts[20];
				pointsInt[j].pt21 = pts[21];
				pointsInt[j].pt22 = pts[22];
				pointsInt[j].pt23 = pts[23];
				pointsInt[j].pt24 = pts[24];
				pointsInt[j].pt25 = pts[25];
				pointsInt[j].pt26 = pts[26];
				pointsInt[j].pt27 = pts[27];
				pointsInt[j].pt28 = pts[28];
				pointsInt[j].pt29 = pts[29];

				pointsInt[j].pt30 = pts[30];
				pointsInt[j].pt31 = pts[31];
				pointsInt[j].pt32 = pts[32];
				pointsInt[j].pt33 = pts[33];
				pointsInt[j].pt34 = pts[34];
				pointsInt[j].pt35 = pts[35];
				pointsInt[j].pt36 = pts[36];
				pointsInt[j].pt37 = pts[37];
				pointsInt[j].pt38 = pts[38];
				pointsInt[j].pt39 = pts[39];

				pointsInt[j].pt40 = pts[40];
				pointsInt[j].pt41 = pts[41];
				pointsInt[j].pt42 = pts[42];
				pointsInt[j].pt43 = pts[43];
				pointsInt[j].pt44 = pts[44];
				pointsInt[j].pt45 = pts[45];
				pointsInt[j].pt46 = pts[46];
				pointsInt[j].pt47 = pts[47];
				pointsInt[j].pt48 = pts[48];
				pointsInt[j].pt49 = pts[49];

				pointsInt[j].pt50 = pts[50];
				pointsInt[j].pt51 = pts[51];
				pointsInt[j].pt52 = pts[52];
				pointsInt[j].pt53 = pts[53];
				pointsInt[j].pt54 = pts[54];
				pointsInt[j].pt55 = pts[55];
				pointsInt[j].pt56 = pts[56];
				pointsInt[j].pt57 = pts[57];
				pointsInt[j].pt58 = pts[58];
				pointsInt[j].pt59 = pts[59];

				pointsInt[j].pt60 = pts[60];
				pointsInt[j].pt61 = pts[61];
				pointsInt[j].pt62 = pts[62];
				pointsInt[j].pt63 = pts[63];
				pointsInt[j].pt64 = pts[64];
				pointsInt[j].pt65 = pts[65];
				pointsInt[j].pt66 = pts[66];
				pointsInt[j].pt67 = pts[67];
				pointsInt[j].pt68 = pts[68];
				pointsInt[j].pt69 = pts[69];

				pointsInt[j].pt70 = pts[70];
				pointsInt[j].pt71 = pts[71];
				pointsInt[j].pt72 = pts[72];
				pointsInt[j].pt73 = pts[73];
				pointsInt[j].pt74 = pts[74];
				pointsInt[j].pt75 = pts[75];
				pointsInt[j].pt76 = pts[76];
				pointsInt[j].pt77 = pts[77];
				pointsInt[j].pt78 = pts[78];
				pointsInt[j].pt79 = pts[79];

				pointsInt[j].pt80 = pts[80];
				pointsInt[j].pt81 = pts[81];
				pointsInt[j].pt82 = pts[82];
				pointsInt[j].pt83 = pts[83];
				pointsInt[j].pt84 = pts[84];
				pointsInt[j].pt85 = pts[85];
				pointsInt[j].pt86 = pts[86];
				pointsInt[j].pt87 = pts[87];
				pointsInt[j].pt88 = pts[88];
				pointsInt[j].pt89 = pts[89];

				pointsInt[j].pt90 = pts[90];
				pointsInt[j].pt91 = pts[91];
				pointsInt[j].pt92 = pts[92];
				pointsInt[j].pt93 = pts[93];
				pointsInt[j].pt94 = pts[94];
				pointsInt[j].pt95 = pts[95];
				pointsInt[j].pt96 = pts[96];
				pointsInt[j].pt97 = pts[97];
				pointsInt[j].pt98 = pts[98];
				pointsInt[j].pt99 = pts[99];

				pointsInt[j].pt100 = pts[100];
				pointsInt[j].pt101 = pts[101];
				pointsInt[j].pt102 = pts[102];
				pointsInt[j].pt103 = pts[103];
				pointsInt[j].pt104 = pts[104];
				pointsInt[j].pt105 = pts[105];
				pointsInt[j].pt106 = pts[106];
				pointsInt[j].pt107 = pts[107];
				pointsInt[j].pt108 = pts[108];
				pointsInt[j].pt109 = pts[109];

				pointsInt[j].pt110 = pts[110];
				pointsInt[j].pt111 = pts[111];
				pointsInt[j].pt112 = pts[112];
				pointsInt[j].pt113 = pts[113];
				pointsInt[j].pt114 = pts[114];
				pointsInt[j].pt115 = pts[115];
				pointsInt[j].pt116 = pts[116];
				pointsInt[j].pt117 = pts[117];
				pointsInt[j].pt118 = pts[118];
				pointsInt[j].pt119 = pts[119];

				pointsInt[j].pt120 = pts[120];
				pointsInt[j].pt121 = pts[121];
				pointsInt[j].pt122 = pts[122];
				pointsInt[j].pt123 = pts[123];
				pointsInt[j].pt124 = pts[124];
				pointsInt[j].pt125 = pts[125];
				pointsInt[j].pt126 = pts[126];
				pointsInt[j].pt127 = pts[127];
				pointsInt[j].pt128 = pts[128];
				pointsInt[j].pt129 = pts[129];

				pointsInt[j].pt130 = pts[130];
				pointsInt[j].pt131 = pts[131];
				pointsInt[j].pt132 = pts[132];

				//---------------------------
				pointsInt[j].pt3D0 = pts3d[0];
				pointsInt[j].pt3D1 = pts3d[1];
				pointsInt[j].pt3D2 = pts3d[2];
				pointsInt[j].pt3D3 = pts3d[3];
				pointsInt[j].pt3D4 = pts3d[4];
				pointsInt[j].pt3D5 = pts3d[5];
				pointsInt[j].pt3D6 = pts3d[6];
				pointsInt[j].pt3D7 = pts3d[7];
				pointsInt[j].pt3D8 = pts3d[8];
				pointsInt[j].pt3D9 = pts3d[9];

				pointsInt[j].pt3D10 = pts3d[10];
				pointsInt[j].pt3D11 = pts3d[11];
				pointsInt[j].pt3D12 = pts3d[12];
				pointsInt[j].pt3D13 = pts3d[13];
				pointsInt[j].pt3D14 = pts3d[14];
				pointsInt[j].pt3D15 = pts3d[15];
				pointsInt[j].pt3D16 = pts3d[16];
				pointsInt[j].pt3D17 = pts3d[17];
				pointsInt[j].pt3D18 = pts3d[18];
				pointsInt[j].pt3D19 = pts3d[19];

				pointsInt[j].pt3D20 = pts3d[20];
				pointsInt[j].pt3D21 = pts3d[21];
				pointsInt[j].pt3D22 = pts3d[22];
				pointsInt[j].pt3D23 = pts3d[23];
				pointsInt[j].pt3D24 = pts3d[24];
				pointsInt[j].pt3D25 = pts3d[25];
				pointsInt[j].pt3D26 = pts3d[26];
				pointsInt[j].pt3D27 = pts3d[27];
				pointsInt[j].pt3D28 = pts3d[28];
				pointsInt[j].pt3D29 = pts3d[29];

				pointsInt[j].pt3D30 = pts3d[30];
				pointsInt[j].pt3D31 = pts3d[31];
				pointsInt[j].pt3D32 = pts3d[32];
				pointsInt[j].pt3D33 = pts3d[33];
				pointsInt[j].pt3D34 = pts3d[34];
				pointsInt[j].pt3D35 = pts3d[35];
				pointsInt[j].pt3D36 = pts3d[36];
				pointsInt[j].pt3D37 = pts3d[37];
				pointsInt[j].pt3D38 = pts3d[38];
				pointsInt[j].pt3D39 = pts3d[39];

				pointsInt[j].pt3D40 = pts3d[40];
				pointsInt[j].pt3D41 = pts3d[41];
				pointsInt[j].pt3D42 = pts3d[42];
				pointsInt[j].pt3D43 = pts3d[43];
				pointsInt[j].pt3D44 = pts3d[44];
				pointsInt[j].pt3D45 = pts3d[45];
				pointsInt[j].pt3D46 = pts3d[46];
				pointsInt[j].pt3D47 = pts3d[47];
				pointsInt[j].pt3D48 = pts3d[48];
				pointsInt[j].pt3D49 = pts3d[49];

				pointsInt[j].pt3D50 = pts3d[50];
				pointsInt[j].pt3D51 = pts3d[51];
				pointsInt[j].pt3D52 = pts3d[52];
				pointsInt[j].pt3D53 = pts3d[53];
				pointsInt[j].pt3D54 = pts3d[54];
				pointsInt[j].pt3D55 = pts3d[55];
				pointsInt[j].pt3D56 = pts3d[56];
				pointsInt[j].pt3D57 = pts3d[57];
				pointsInt[j].pt3D58 = pts3d[58];
				pointsInt[j].pt3D59 = pts3d[59];

				pointsInt[j].pt3D60 = pts3d[60];
				pointsInt[j].pt3D61 = pts3d[61];
				pointsInt[j].pt3D62 = pts3d[62];
				pointsInt[j].pt3D63 = pts3d[63];
				pointsInt[j].pt3D64 = pts3d[64];
				pointsInt[j].pt3D65 = pts3d[65];
				pointsInt[j].pt3D66 = pts3d[66];
				pointsInt[j].pt3D67 = pts3d[67];
				pointsInt[j].pt3D68 = pts3d[68];
				pointsInt[j].pt3D69 = pts3d[69];

				pointsInt[j].pt3D70 = pts3d[70];
				pointsInt[j].pt3D71 = pts3d[71];
				pointsInt[j].pt3D72 = pts3d[72];
				pointsInt[j].pt3D73 = pts3d[73];
				pointsInt[j].pt3D74 = pts3d[74];
				pointsInt[j].pt3D75 = pts3d[75];
				pointsInt[j].pt3D76 = pts3d[76];
				pointsInt[j].pt3D77 = pts3d[77];
				pointsInt[j].pt3D78 = pts3d[78];
				pointsInt[j].pt3D79 = pts3d[79];

				pointsInt[j].pt3D80 = pts3d[80];
				pointsInt[j].pt3D81 = pts3d[81];
				pointsInt[j].pt3D82 = pts3d[82];
				pointsInt[j].pt3D83 = pts3d[83];
				pointsInt[j].pt3D84 = pts3d[84];
				pointsInt[j].pt3D85 = pts3d[85];
				pointsInt[j].pt3D86 = pts3d[86];
				pointsInt[j].pt3D87 = pts3d[87];
				pointsInt[j].pt3D88 = pts3d[88];
				pointsInt[j].pt3D89 = pts3d[89];

				pointsInt[j].pt3D90 = pts3d[90];
				pointsInt[j].pt3D91 = pts3d[91];
				pointsInt[j].pt3D92 = pts3d[92];
				pointsInt[j].pt3D93 = pts3d[93];
				pointsInt[j].pt3D94 = pts3d[94];
				pointsInt[j].pt3D95 = pts3d[95];
				pointsInt[j].pt3D96 = pts3d[96];
				pointsInt[j].pt3D97 = pts3d[97];
				pointsInt[j].pt3D98 = pts3d[98];
				pointsInt[j].pt3D99 = pts3d[99];

				pointsInt[j].pt3D100 = pts3d[100];
				pointsInt[j].pt3D101 = pts3d[101];
				pointsInt[j].pt3D102 = pts3d[102];
				pointsInt[j].pt3D103 = pts3d[103];
				pointsInt[j].pt3D104 = pts3d[104];
				pointsInt[j].pt3D105 = pts3d[105];
				pointsInt[j].pt3D106 = pts3d[106];
				pointsInt[j].pt3D107 = pts3d[107];
				pointsInt[j].pt3D108 = pts3d[108];
				pointsInt[j].pt3D109 = pts3d[109];

				pointsInt[j].pt3D110 = pts3d[110];
				pointsInt[j].pt3D111 = pts3d[111];
				pointsInt[j].pt3D112 = pts3d[112];
				pointsInt[j].pt3D113 = pts3d[113];
				pointsInt[j].pt3D114 = pts3d[114];
				pointsInt[j].pt3D115 = pts3d[115];
				pointsInt[j].pt3D116 = pts3d[116];
				pointsInt[j].pt3D117 = pts3d[117];
				pointsInt[j].pt3D118 = pts3d[118];
				pointsInt[j].pt3D119 = pts3d[119];

				pointsInt[j].pt3D120 = pts3d[120];
				pointsInt[j].pt3D121 = pts3d[121];
				pointsInt[j].pt3D122 = pts3d[122];
				pointsInt[j].pt3D123 = pts3d[123];
				pointsInt[j].pt3D124 = pts3d[124];
				pointsInt[j].pt3D125 = pts3d[125];
				pointsInt[j].pt3D126 = pts3d[126];
				pointsInt[j].pt3D127 = pts3d[127];
				pointsInt[j].pt3D128 = pts3d[128];
				pointsInt[j].pt3D129 = pts3d[129];

				pointsInt[j].pt3D130 = pts3d[130];
				pointsInt[j].pt3D131 = pts3d[131];
				pointsInt[j].pt3D132 = pts3d[132];
				pointsInt[j].pt3D133 = pts3d[133];
				pointsInt[j].pt3D134 = pts3d[134];
				pointsInt[j].pt3D135 = pts3d[135];
				pointsInt[j].pt3D136 = pts3d[136];
				pointsInt[j].pt3D137 = pts3d[137];
				pointsInt[j].pt3D138 = pts3d[138];
				pointsInt[j].pt3D139 = pts3d[139];

				pointsInt[j].pt3D140 = pts3d[140];
				pointsInt[j].pt3D141 = pts3d[141];
				pointsInt[j].pt3D142 = pts3d[142];
				pointsInt[j].pt3D143 = pts3d[143];
				pointsInt[j].pt3D144 = pts3d[144];
				pointsInt[j].pt3D145 = pts3d[145];
				pointsInt[j].pt3D146 = pts3d[146];
				pointsInt[j].pt3D147 = pts3d[147];
				pointsInt[j].pt3D148 = pts3d[148];
				pointsInt[j].pt3D149 = pts3d[149];

				pointsInt[j].pt3D150 = pts3d[150];
				pointsInt[j].pt3D151 = pts3d[151];
				pointsInt[j].pt3D152 = pts3d[152];
				pointsInt[j].pt3D153 = pts3d[153];
				pointsInt[j].pt3D154 = pts3d[154];
				pointsInt[j].pt3D155 = pts3d[155];
				pointsInt[j].pt3D156 = pts3d[156];
				pointsInt[j].pt3D157 = pts3d[157];
				pointsInt[j].pt3D158 = pts3d[158];
				pointsInt[j].pt3D159 = pts3d[159];

				pointsInt[j].pt3D160 = pts3d[160];
				pointsInt[j].pt3D161 = pts3d[161];
				pointsInt[j].pt3D162 = pts3d[162];
				pointsInt[j].pt3D163 = pts3d[163];
				pointsInt[j].pt3D164 = pts3d[164];
				pointsInt[j].pt3D165 = pts3d[165];
				pointsInt[j].pt3D166 = pts3d[166];
				pointsInt[j].pt3D167 = pts3d[167];
				pointsInt[j].pt3D168 = pts3d[168];
				pointsInt[j].pt3D169 = pts3d[169];

				pointsInt[j].pt3D170 = pts3d[170];
				pointsInt[j].pt3D171 = pts3d[171];
				pointsInt[j].pt3D172 = pts3d[172];
				pointsInt[j].pt3D173 = pts3d[173];
				pointsInt[j].pt3D174 = pts3d[174];
				pointsInt[j].pt3D175 = pts3d[175];
				pointsInt[j].pt3D176 = pts3d[176];
				pointsInt[j].pt3D177 = pts3d[177];
				pointsInt[j].pt3D178 = pts3d[178];
				pointsInt[j].pt3D179 = pts3d[179];

				pointsInt[j].pt3D180 = pts3d[180];
				pointsInt[j].pt3D181 = pts3d[181];
				pointsInt[j].pt3D182 = pts3d[182];
				pointsInt[j].pt3D183 = pts3d[183];
				pointsInt[j].pt3D184 = pts3d[184];
				pointsInt[j].pt3D185 = pts3d[185];
				pointsInt[j].pt3D186 = pts3d[186];
				pointsInt[j].pt3D187 = pts3d[187];
				pointsInt[j].pt3D188 = pts3d[188];
				pointsInt[j].pt3D189 = pts3d[189];

				pointsInt[j].pt3D190 = pts3d[190];
				pointsInt[j].pt3D191 = pts3d[191];
				pointsInt[j].pt3D192 = pts3d[192];
				pointsInt[j].pt3D193 = pts3d[193];
				pointsInt[j].pt3D194 = pts3d[194];
				pointsInt[j].pt3D195 = pts3d[195];
				pointsInt[j].pt3D196 = pts3d[196];
				pointsInt[j].pt3D197 = pts3d[197];
				pointsInt[j].pt3D198 = pts3d[198];

				c = static_cast<int>(imx);
			}
		}
		if (testNumber == 5) {
			imshow("OUTPUT 5 - 1 Tracking", frame);
		}

		if (c == 0) {
			c = 0;
		}

		return c;
	}

	void Close()
	{
		//capture.release();
	}

	void SetScale(int scale)
	{
		scale = scale;
	}

	int TestSort(int a[], int length) {
		scale = 1;
		std::sort(a, a + length);
		return scale;
	}

	int SetData(int w, int h, cv::Mat frame) {
		//cv::Mat frame(cv::Size(w, h), CV_8UC4, data);
		if (frame.empty()) {
			return 0;
		}

		cv::flip(frame, frame, 0);

		//std::vector<cv::Rect> faces;
		// Convert the frame to grayscale for cascade detection.
		//cv::Mat grayscaleFrame;
		//cvtColor(frame, grayscaleFrame, cv::COLOR_BGR2GRAY);
		//cv::Mat resizedGray;
		// Scale down for better performance.
		//cv::resize(grayscaleFrame, resizedGray, cv::Size(frame.cols / 2, frame.rows / 2));
		//cv::equalizeHist(frame, frame);

		imshow("OUTPUT 1", frame);
		return 1;
	}

	uchar* SetData6()
	{
		return false;
	}
}

// COM-like Release macro
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(a) if (a) { a->Release(); a = NULL; }
#endif

static float g_Time;

extern "C" void ULSEE_PLUGIN_API SetTimeFromUnity(float t) { g_Time = t; }


extern "C" void ULSEE_PLUGIN_API UnityRenderEvent(int eventID)
{
}