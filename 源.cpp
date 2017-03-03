#include <iostream>
#include <string>
#include <fstream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
const int rows = 281;             //define the size of Mat variable
const int cols = 361;
using namespace cv;

int main()
{
	for (int dat_i = 0; dat_i <= 4380; dat_i++) {
		char inputpath[100]= "F:\\25points\\data_points_";
		char temp_dat_i[20];
		_itoa(dat_i, temp_dat_i, 10);
		char temp_txt[10] = ".txt";
	    strcat(inputpath, temp_dat_i);
		strcat(inputpath, temp_txt);

		char outputpath[100] = "F:\\25canshu1\\canshu";
		strcat(outputpath, temp_dat_i);
		strcat(outputpath, temp_txt);
		printf("%s  %s\n", inputpath, outputpath);
		string sx,sy;
		ifstream fp(inputpath);

		if (!fp)
		{
			continue;
		}

		float num;
		ofstream out(outputpath);      //saveroute
		while (getline(fp, sx))          //get a line of datas then ergodic and chartofloat
		{
			vector<Point> pointsf;
			int x_point[500], y_point[500];
			int countx = 0, county = 0;
			char bufferx[20];
			int posx = 0;
			int len_sx = sx.length();
			for (int i = 0; i < len_sx; i++) {
				if (sx[i] != ' ') {
					bufferx[posx++] = sx[i];
					if (i == len_sx - 1 || sx[i + 1] == ' ') {
						num = atof(bufferx);          //chartofloat
						memset(bufferx, 0, 20);         //clear the buffer 
						x_point[countx] = num;
						countx++;
						posx= 0;
					}
				}
			}
			
			getline(fp, sy);
			char buffery[20];
			int posy = 0;
			int len_sy = sy.length();
			for (int i = 0; i < len_sy; i++) {
				if (sy[i] != ' ') {
					buffery[posy++] = sy[i];
					if (i == len_sy - 1 || sy[i + 1] == ' ') {
						num = atof(buffery);          //chartofloat
						memset(buffery, 0, 20);         //clear the buffer 
						y_point[county] = num;
						county++;
						posy= 0;
					}
				}
			}
			for (int point_i = 0; point_i < countx; point_i++) {
				Point temp_point;
				temp_point.x = x_point[point_i];
				temp_point.y = y_point[point_i];
				pointsf.push_back(temp_point);
			}
			cout << size(pointsf) << endl;
			RotatedRect box = fitEllipse(pointsf);
			float Cx =  box.center.x;
			float Cy = box.center.y;
			float a = max(box.size.width, box.size.height);
			float b=min(box.size.width, box.size.height);
			out << Cx << " " << Cy << " " << a << " " << b << " "<<box.angle << endl;
		}
	}

	return 0;
}
