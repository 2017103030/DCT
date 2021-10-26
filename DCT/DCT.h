#pragma once
#include <iostream>
#include <cmath>
using namespace std;
const float PI = 3.141592;
const int SHIFTPLUS = 1;
const int SHIFTMINUS = 0;
const int DEFAULTSHIFT = 128;
enum PrintOption {
	YPLANE = 0,
	DCT,
	RECOVER,
	ERROR
};
const int LuminanceQuantizationTable[8][8] = {
	{16,11,10,16,24,40,51,61},
	{12,12,14,19,26,58,60,55},
	{14,13,16,24,40,57,69,56},
	{14,17,22,29,51,87,80,62},
	{18,22,37,56,68,109,103,77},
	{24,35,55,64,81,104,113,92},
	{49,64,78,87,103,121,120,101},
	{72,92,95,98,112,100,103,99}
};

class Dct {
private:
	int m_blocksize; // Macro Block size
	unsigned char** m_yplane; // Bytes represent Luminance Plane
	unsigned char** m_recovery;
	int** m_Fuv; // Bytes represent output of DCT
	// ��� : DCT ����� ���� C(Ksi) ��� ��ȯ
	float ConstC(int ksi) const;
	float DctSigma(int u, int v) const;
	float IdctSigma(int i, int j) const;
public:
	// Dct Class�� ������
	// ��� : blocksize �� �Է� �޾� �̸� ��������
	// m_yplane�� m_FUV�� �޸� ���� �Ҵ�
	// �Է��� ���� ��� default = 8 �� m_blocksize�� ����
	Dct(int blocksize);
	// DCT Class�� �Ҹ���
	// ��� : m_blocksize �� �������� ��ü �Ҹ��
	// �Ҵ��� �޸𸮸� �����ϵ��� ��
	~Dct();
	// ��� : m_yplane�� m_Fuv�� ���
	// ��� �� :
	// Luminance palne :
	// 200 202 189 188 189 175 175 175
	// 200 203 198 188 189 182 178 175
	// 203 200 200 195 200 187 185 175
	// 200 200 200 200 197 187 187 187
	// 200 205 200 200 195 188 187 175
	// 200 200 200 200 200 190 187 175
	// 205 200 199 200 191 187 187 175
	// 210 200 200 200 188 185 187 186
	// DCT :
	// 515 65 -12 4 1 2 -8 5
	// -16 3 2 0 0 -11 -2 3
	// -12 6 11 -1 3 0 1 -2
	// -8 3 -4 2 -2 -3 -5 -2
	// 0 -2 7 -5 4 0 -1 -4
	// 0 -3 -1 0 4 1 -1 0
	// 3 -2 -3 3 3 -1 -1 3
	

	// ��� : mode�� SHIFTPLUS���  m_yplane�� ���� int shift ��ŭ ������.
	//		  mode�� SHIFTMINUS��� m_recovery ���� int shift ��ŭ ����.
	void ShiftLuminancePlane(int shift, int mode);

	// ��� : �����͸� �о� m_yplane�� �����ϵ��� ��
	void ReadMat(unsigned char** &input);
	// ��� : 2D DCT ������ m_yplane�� �̿��� ����
	// ����� m_Fuv�� ����
	void Transform();
	// ��� :: 2D �� DCT ������ m_Fuc�� �̿��� ����
	// ����� m_recovery�� ����
	void InvTransform();
	// ��� : Quantization Table�� �̿��� F(u,v) ������ ����� ���� ������ ������ ������.
	// ����� m_Fuv �� �״�� ����
	void Quantizationing();
	//��� : Quantization Table�� �̿��� F(u,v) ������ ����� ���� �ٽ� ��������.
	void InvQuantizationing();
	void PrintMatrix(int mode) const;

};
