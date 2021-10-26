#include "DCT.h"
/// <2021�� 10�� 18�� ��ö��>
/// 8 x 8 ����� �̿��� DCT Quantization IDCT �ǽ�
/// <2021�� 10�� 18�� ��ö��>
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
	// �ǽ��� ���� �����͸� MyDct ��ü�� �����ϴ� �����Դϴ�.
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
	cout << "\t[���� Luminance Plane]" << endl;
	MyDct.PrintMatrix(YPLANE);
	// 128 ��ŭ Luminance Plane�� ���� Shift �ϴ� �ڵ��Դϴ�,.
	MyDct.ShiftLuminancePlane(DEFAULTSHIFT,SHIFTMINUS);
	cout << "\t[128��ŭ SHIFT�� ������ ���]" << endl;
	MyDct.PrintMatrix(YPLANE);

	//DCT ������Դϴ�.
	MyDct.Transform();
	cout << "\t[DCT�� ������ ���]" << endl;

	MyDct.PrintMatrix(DCT);

	//Quantization ������Դϴ�.
	cout << "\t[Quantization ������ ���]" << endl;
	MyDct.Quantizationing();
	MyDct.PrintMatrix(DCT);

	//Inverse Quantization ������Դϴ�.
	cout << "\t[Quantization ������ �ǵ��� ���]" << endl;
	MyDct.InvQuantizationing();
	MyDct.PrintMatrix(DCT);

	//Inverse DCT ������Դϴ�.
	cout << "\t[IDCT ���� ���]" << endl;
	MyDct.InvTransform();
	MyDct.ShiftLuminancePlane(DEFAULTSHIFT,SHIFTPLUS);
	MyDct.PrintMatrix(RECOVER);
	
	//Error ��� ���Դϴ�.
	MyDct.ShiftLuminancePlane(-128, SHIFTMINUS); // Error ����� ���� Luminance Plnae�� ���� ������ shift
	MyDct.PrintMatrix(ERROR);
	cout << "\t[DCT Operation End]" << endl;
	getchar();
	return 0;
}