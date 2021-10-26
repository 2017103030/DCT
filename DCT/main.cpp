#include "DCT.h"
/// <2021년 10월 18일 정철현>
/// 8 x 8 행렬을 이용한 DCT Quantization IDCT 실습
/// <2021년 10월 18일 정철현>
unsigned char src_example[8][8] = {
	{200, 202, 189, 188, 189, 175, 175, 175},
	{200, 203, 198, 188, 189, 182, 178, 175},
	{203, 200, 200, 195, 200, 187, 185, 175},
	{200, 200, 200, 200, 197, 187, 187, 187},
	{200, 205, 200, 200, 195, 188, 187, 175},
	{200, 200, 200, 200, 200, 190, 187, 175},
	{205, 200, 199, 200, 191, 187, 187, 175},
	{210, 200, 200, 200, 188, 185, 187, 186}
};


int main() {
	// 실습을 위한 데이터를 MyDct 객체에 저장하는 과정입니다.
	cout << endl << endl;
	int my_block_size = 8;
	Dct MyDct(my_block_size);
	unsigned char** example;
	example = new unsigned char*[my_block_size];
	for (int i = 0; i < my_block_size; i++) {
		example[i] = new unsigned char[my_block_size];
		memcpy(example[i], src_example[i], my_block_size);
	}
	MyDct.ReadMat(example);
	cout << "\t[원본 Luminance Plane]" << endl;
	MyDct.PrintMatrix(YPLANE);
	// 128 만큼 Luminance Plane의 값을 Shift 하는 코드입니다,.
	MyDct.ShiftLuminancePlane(DEFAULTSHIFT,SHIFTMINUS);
	cout << "\t[128만큼 SHIFT를 수행한 결과]" << endl;
	MyDct.PrintMatrix(YPLANE);

	//DCT 실행부입니다.
	MyDct.Transform();
	cout << "\t[DCT를 수행한 결과]" << endl;

	MyDct.PrintMatrix(DCT);

	//Quantization 실행부입니다.
	cout << "\t[Quantization 수행한 결과]" << endl;
	MyDct.Quantizationing();
	MyDct.PrintMatrix(DCT);

	//Inverse Quantization 실행부입니다.
	cout << "\t[Quantization 과정을 되돌린 결과]" << endl;
	MyDct.InvQuantizationing();
	MyDct.PrintMatrix(DCT);

	//Inverse DCT 실행부입니다.
	cout << "\t[IDCT 실행 결과]" << endl;
	MyDct.InvTransform();
	MyDct.ShiftLuminancePlane(DEFAULTSHIFT,SHIFTPLUS);
	MyDct.PrintMatrix(RECOVER);
	
	//Error 출력 부입니다.
	MyDct.ShiftLuminancePlane(-128, SHIFTMINUS); // Error 계산을 위해 Luminance Plnae을 원래 값으로 shift
	MyDct.PrintMatrix(ERROR);
	cout << "\t[DCT Operation End]" << endl;
	getchar();
	return 0;
}