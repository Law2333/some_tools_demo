//main.cpp
//读取训练模型,控制台输出，并写入faces.txt文件

#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void getFiles(string path, vector<string>& files);

int main()
{
	ofstream f("E:\\project\\facedata\\san\\faces.txt", ios::beg);//从头写入文件
	string filePath = "E:\\project\\facedata\\san";
	vector<string> files;
	getFiles(filePath, files);
	int number = files.size();//文件数量
	//输出文件路径，并写入txt文件中
	for (int i = 0; i < number; i++)
	{
		cout<<files[i]<<endl;
		f << files[i] << endl;
	}

	return 0;
}

void getFiles(string path, vector<string>& files)
{
	//intptr_t和uintptr_t是什么类型:typedef long int/ typedef unsigned long int
	intptr_t   hFile = 0;
	//存储文件各种信息的结构体
	struct _finddata_t fileinfo;
	string p; 
	//assign方法可以理解为先将原字符串清空，然后赋予新的值作替换。
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		string indexTmp,fileName;
		int numEle = 0;
		do
		{
			//是否为文件夹
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						//子文件夹下递归访问
						getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
					}
			}
			else//非文件夹
			{
				//根据当前文件夹名，确定索引
				//文件夹名去除s后的名字字符数量
				numEle = p.rfind("\\") - (p.rfind("s") + 1);
				indexTmp = p.substr((p.rfind("s") + 1), numEle);
				//若不为txt,记录路径
				fileName = fileinfo.name;
				if (fileName.rfind(".txt") == fileName.npos)
				{
					//分号后添加索引
					files.push_back(p.assign(path).append("\\").append(fileinfo.name).append(";") + indexTmp);
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);//文件夹下的文件读取完毕
		_findclose(hFile);
	}
}
