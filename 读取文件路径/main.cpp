//main.cpp
//��ȡѵ��ģ��,����̨�������д��faces.txt�ļ�

#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void getFiles(string path, vector<string>& files);

int main()
{
	ofstream f("E:\\project\\facedata\\san\\faces.txt", ios::beg);//��ͷд���ļ�
	string filePath = "E:\\project\\facedata\\san";
	vector<string> files;
	getFiles(filePath, files);
	int number = files.size();//�ļ�����
	//����ļ�·������д��txt�ļ���
	for (int i = 0; i < number; i++)
	{
		cout<<files[i]<<endl;
		f << files[i] << endl;
	}

	return 0;
}

void getFiles(string path, vector<string>& files)
{
	//intptr_t��uintptr_t��ʲô����:typedef long int/ typedef unsigned long int
	intptr_t   hFile = 0;
	//�洢�ļ�������Ϣ�Ľṹ��
	struct _finddata_t fileinfo;
	string p; 
	//assign�����������Ϊ�Ƚ�ԭ�ַ�����գ�Ȼ�����µ�ֵ���滻��
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		string indexTmp,fileName;
		int numEle = 0;
		do
		{
			//�Ƿ�Ϊ�ļ���
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						//���ļ����µݹ����
						getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
					}
			}
			else//���ļ���
			{
				//���ݵ�ǰ�ļ�������ȷ������
				//�ļ�����ȥ��s��������ַ�����
				numEle = p.rfind("\\") - (p.rfind("s") + 1);
				indexTmp = p.substr((p.rfind("s") + 1), numEle);
				//����Ϊtxt,��¼·��
				fileName = fileinfo.name;
				if (fileName.rfind(".txt") == fileName.npos)
				{
					//�ֺź��������
					files.push_back(p.assign(path).append("\\").append(fileinfo.name).append(";") + indexTmp);
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);//�ļ����µ��ļ���ȡ���
		_findclose(hFile);
	}
}
