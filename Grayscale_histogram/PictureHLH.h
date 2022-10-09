#pragma once

#ifndef PICTURE_HLH_H
#define PICTURE_HLH_H

#include<malloc.h>
#include<stdlib.h>
#include<iostream>

#pragma pack(1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned char bfType[2];//�ļ���ʽ
    unsigned long bfSize;//�ļ���С
    unsigned short bfReserved1;//����
    unsigned short bfReserved2;
    unsigned long bfOffBits; //DIB�������ļ��е�ƫ����
}fileHeader;
#pragma pack()
/*
λͼ������Ϣ�ṹ
*/
#pragma pack(1)
typedef struct tagBITMAPINFOHEADER
{
    unsigned long biSize;//�ýṹ�Ĵ�С
    long biWidth;//�ļ����
    long biHeight;//�ļ��߶�
    unsigned short biPlanes;//ƽ����
    unsigned short biBitCount;//��ɫλ��
    unsigned long biCompression;//ѹ������
    unsigned long biSizeImage;//DIB��������С
    long biXPixPerMeter;
    long biYPixPerMeter;
    unsigned long biClrUsed;//������ɫ������
    unsigned long biClrImporant;//������Ҫ��ɫ
}fileInfo;
#pragma pack()
/*
��ɫ��ṹ
*/
#pragma pack(1)
typedef struct tagRGBQUAD
{
    unsigned char rgbBlue; //��ɫ��������
    unsigned char rgbGreen;//��ɫ��������
    unsigned char rgbRed;//��ɫ��������
    unsigned char rgbReserved;
}rgbq;
#pragma pack()
class PictureHLH
{
public:
    int a;
    long width;
    long height;
    int gray[256] = { 0 };
    unsigned char ImgData[3000][3];
    PictureHLH(const char* filename);
    void display();
};
#endif // PICTURE_HLH_H
