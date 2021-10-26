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
	// 기능 : DCT 계산을 위한 C(Ksi) 결과 반환
	float ConstC(int ksi) const;
	float DctSigma(int u, int v) const;
	float IdctSigma(int i, int j) const;
public:
	// Dct Class의 생성자
	// 기능 : blocksize 를 입력 받아 이를 바탕으로
	// m_yplane과 m_FUV에 메모리 공간 할당
	// 입력이 없을 경우 default = 8 로 m_blocksize를 설정
	Dct(int blocksize);
	// DCT Class의 소멸자
	// 기능 : m_blocksize 를 바탕으로 객체 소멸시
	// 할당한 메모리를 해제하도록 함
	~Dct();
	// 기능 : m_yplane과 m_Fuv를 출력
	// 출력 예 :
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
	

	// 기능 : mode가 SHIFTPLUS라면  m_yplane의 값을 int shift 만큼 더해줌.
	//		  mode가 SHIFTMINUS라면 m_recovery 값을 int shift 만큼 뺀다.
	void ShiftLuminancePlane(int shift, int mode);

	// 기능 : 데이터를 읽어 m_yplane에 저장하도록 함
	void ReadMat(unsigned char** &input);
	// 기능 : 2D DCT 연산을 m_yplane을 이용해 수행
	// 결과는 m_Fuv에 저장
	void Transform();
	// 기능 :: 2D 역 DCT 연산을 m_Fuc를 이용해 수행
	// 결과는 m_recovery에 저장
	void InvTransform();
	// 기능 : Quantization Table을 이용해 F(u,v) 영억의 행렬의 값을 정해진 값으로 나눠줌.
	// 결과는 m_Fuv 에 그대로 저장
	void Quantizationing();
	//기능 : Quantization Table을 이용해 F(u,v) 영역의 행렬의 값을 다시 복구해줌.
	void InvQuantizationing();
	void PrintMatrix(int mode) const;

};
