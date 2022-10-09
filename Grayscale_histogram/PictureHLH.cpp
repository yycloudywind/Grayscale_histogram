#include "PictureHLH.h"

using namespace std;

PictureHLH::PictureHLH(const char* filename)
{
    /*�洢RGBͼ���һ�����ص�*/
    /*���Ҷ�ͼ�����ش浽һ��һά������*/
    unsigned char ImgData2[3000];
    int i, j, k;
    string fng = "";
    FILE* fp, * fp_gray;
    fileHeader* _fheader;
    fileInfo* _finfo;
    rgbq* _frgbq;

    if (fopen_s(&fp, filename, "rb"))
    {
        printf("���ļ�ʧ��");
        exit(0);
    }

    for (int i = 0; i < strlen(filename); i++)
    {
        if (filename[i] != '.') fng += filename[i];
        else fng += "_gray.";        
    }
    if (fopen_s(&fp_gray, fng.c_str(), "wb"))
    {
        printf("�����ļ�ʧ��");
        exit(0);
    }
    _fheader = (fileHeader*)malloc(sizeof(fileHeader));
    _finfo = (fileInfo*)malloc(sizeof(fileInfo));

    if (_finfo->biBitCount <= 8) cout << "�ǻҶ�ͼ" << endl;
    else {
        //��ȡλͼͷ�ṹ����Ϣͷ
        fread(_fheader, sizeof(fileHeader), 1, fp);
        fread(_finfo, sizeof(fileInfo), 1, fp);
        //�޸�ͷ��Ϣ
        _finfo->biBitCount = 8;
        _finfo->biSizeImage = ((_finfo->biWidth * 3 + 3) / 4) * 4 * _finfo->biHeight;
        //fi->biClrUsed=256;
        width = _finfo->biWidth;
        height = _finfo->biHeight;
        _fheader->bfOffBits = sizeof(fileHeader) + sizeof(fileInfo) + 256 * sizeof(rgbq);
        _fheader->bfSize = _fheader->bfOffBits + _finfo->biSizeImage;

        //������ɫ��
        _frgbq = (rgbq*)malloc(256 * sizeof(rgbq));
        for (i = 0; i < 256; i++)
        {
            _frgbq[i].rgbBlue = _frgbq[i].rgbGreen = _frgbq[i].rgbRed = i;
            //fq[i].rgbReserved=0;
        }
        //��ͷ��Ϣд��
        fwrite(_fheader, sizeof(fileHeader), 1, fp_gray);
        fwrite(_finfo, sizeof(fileInfo), 1, fp_gray);
        fwrite(_frgbq, sizeof(rgbq), 256, fp_gray);
        //����ֱ��ͼ
        cout << "������Ҷ�ֵ��������" << endl;
        int  b; cin >> a; cin.get(); double scale = 256 / a;
        //��ȡRGBͼ���ز�ת��Ϊ�Ҷ�ֵ
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
        //���Ҷ�ͼ��Ϣд��
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
    //ͳ��Ƶ��
    for (int i = 0; i < a; i++)
    {
        gray[i] = (100 * gray[i]) / size;
        //cout << gray[i] << endl;
    }
    //��ʼ����ֱ��ͼ
    for (int i = 0; i < a; i++)
    {
        cout << i << ":  ";
        star(gray[i]);
    }
}