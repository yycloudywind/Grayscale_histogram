#include "PictureHLH.h"

using namespace std;

PictureHLH::PictureHLH(const char* filename)
{
    /*存储RGB图像的一行像素点*/
    /*将灰度图的像素存到一个一维数组中*/
    unsigned char ImgData2[3000];
    int i, j, k;
    string fng = "";
    FILE* fp, * fp_gray;
    fileHeader* _fheader;
    fileInfo* _finfo;
    rgbq* _frgbq;

    if (fopen_s(&fp, filename, "rb"))
    {
        printf("打开文件失败");
        exit(0);
    }

    for (int i = 0; i < strlen(filename); i++)
    {
        if (filename[i] != '.') fng += filename[i];
        else fng += "_gray.";        
    }
    if (fopen_s(&fp_gray, fng.c_str(), "wb"))
    {
        printf("创建文件失败");
        exit(0);
    }
    _fheader = (fileHeader*)malloc(sizeof(fileHeader));
    _finfo = (fileInfo*)malloc(sizeof(fileInfo));

    if (_finfo->biBitCount <= 8) cout << "是灰度图" << endl;
    else {
        //读取位图头结构和信息头
        fread(_fheader, sizeof(fileHeader), 1, fp);
        fread(_finfo, sizeof(fileInfo), 1, fp);
        //修改头信息
        _finfo->biBitCount = 8;
        _finfo->biSizeImage = ((_finfo->biWidth * 3 + 3) / 4) * 4 * _finfo->biHeight;
        //fi->biClrUsed=256;
        width = _finfo->biWidth;
        height = _finfo->biHeight;
        _fheader->bfOffBits = sizeof(fileHeader) + sizeof(fileInfo) + 256 * sizeof(rgbq);
        _fheader->bfSize = _fheader->bfOffBits + _finfo->biSizeImage;

        //创建调色版
        _frgbq = (rgbq*)malloc(256 * sizeof(rgbq));
        for (i = 0; i < 256; i++)
        {
            _frgbq[i].rgbBlue = _frgbq[i].rgbGreen = _frgbq[i].rgbRed = i;
            //fq[i].rgbReserved=0;
        }
        //将头信息写入
        fwrite(_fheader, sizeof(fileHeader), 1, fp_gray);
        fwrite(_finfo, sizeof(fileInfo), 1, fp_gray);
        fwrite(_frgbq, sizeof(rgbq), 256, fp_gray);
        //绘制直方图
        cout << "请输入灰度值区间数：" << endl;
        int  b; cin >> a; cin.get(); double scale = 256 / a;
        //读取RGB图像素并转换为灰度值
        for (i = 0; i < _finfo->biHeight; i++)
        {
            for (j = 0; j < (_finfo->biWidth + 3) / 4 * 4; j++)
            {
                for (k = 0; k < 3; k++)
                    fread(&ImgData[j][k], 1, 1, fp);
            }
            for (j = 0; j < (_finfo->biWidth + 3) / 4 * 4; j++)
            {
                ImgData2[j] = int((float)ImgData[j][0] * 0.114 +
                    (float)ImgData[j][1] * 0.587 +
                    (float)ImgData[j][2] * 0.299);
                b = ImgData2[j] / scale;
                //cout << b << endl;
                gray[b]++;
            }
        }
        //将灰度图信息写入
        fwrite(ImgData2, sizeof(char), 3000, fp_gray);
        free(_fheader);
        free(_finfo);
        free(_frgbq);
        fclose(fp);
        fclose(fp_gray);
        printf("success\n");
    }
}

void star(int x)
{
    for (int i = 0; i < x; i++)
        cout << "*";
    cout << endl;
}

void PictureHLH::display()
{
    int size = height * ((width + 3) / 4 * 4);
    //cout << size;
    //统计频率
    for (int i = 0; i < a; i++)
    {
        gray[i] = (100 * gray[i]) / size;
        //cout << gray[i] << endl;
    }
    //开始绘制直方图
    for (int i = 0; i < a; i++)
    {
        cout << i << ":  ";
        star(gray[i]);
    }
}