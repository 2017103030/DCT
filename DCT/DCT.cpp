#include "DCT.h"

Dct::Dct(int blocksize = 8) : m_blocksize(blocksize) {
	m_yplane = new unsigned char* [m_blocksize];
	m_recovery = new unsigned char* [m_blocksize];
	m_Fuv = new int * [m_blocksize];
	for (int c = 0; c < m_blocksize; c++) {
		m_yplane[c] = new unsigned char[m_blocksize];
		m_Fuv[c] = new int[m_blocksize];
		m_recovery[c] = new unsigned char[m_blocksize];
	}
}

Dct::~Dct() {
	for (int c = 0; c < m_blocksize; c++) {
		delete[] m_yplane[c];
		delete[] m_Fuv[c];
		delete[] m_recovery[c];
	}
	delete[] m_yplane;
	delete[] m_Fuv;
	delete[] m_recovery;
}

float Dct::ConstC(int ksi) const {
	if (ksi == 0) return (float)0.7071; // arroximation of [root(2) / 2]
	else return (float)1.0;
}

float Dct::DctSigma(int u, int v) const{
	float summation = 0.0;
	for (int i = 0; i < m_blocksize; i++) {
		for (int j = 0; j < m_blocksize; j++) {
			summation += cos(((2 * i + 1) * u * PI) / (float)(m_blocksize + m_blocksize)) * cos(((2 * j + 1) * v * PI) / (float)(m_blocksize + m_blocksize)) *(float) m_yplane[i][j];
		}
	}
	return summation;
}

float Dct::IdctSigma(int i, int j) const {
	float summation = 0.0;
	for (int u = 0; u < m_blocksize; u++) {
		for (int v = 0; v < m_blocksize; v++) {
			summation += (2 *  ConstC(u) * ConstC(v) / (float)m_blocksize) * cos((2 * i + 1) * u * PI / (float)(m_blocksize + m_blocksize)) * cos((2 * j + 1) * v * PI / (float)(m_blocksize + m_blocksize)) * m_Fuv[u][v];
		}
	}
	return summation;
}
void Dct::ShiftLuminancePlane(int shift, int mode) {
	if (mode == SHIFTMINUS) {
		for (int i = 0; i < m_blocksize; i++) {
			for (int j = 0; j < m_blocksize; j++) {
				m_yplane[i][j] -= shift;
			}
		}
	}
	else {
		for (int i = 0; i < m_blocksize; i++) {
			for (int j = 0; j < m_blocksize; j++) {
				m_recovery[i][j] += shift;
			}
		}
	}
}

void Dct::ReadMat(unsigned char**& input) {
	for (int c = 0; c < m_blocksize; c++) {
		memcpy(m_yplane[c], input[c], m_blocksize);
	}
}

void Dct::Transform() {
	for (int u = 0; u < m_blocksize; u++) {
		for (int v = 0; v < m_blocksize; v++) {
			m_Fuv[u][v] = roundf((2 * ( ConstC(u) * ConstC(v) / (float)m_blocksize) * DctSigma(u, v)));
		}
	}
}

void Dct::InvTransform() {
	for (int i = 0; i < m_blocksize; i++) {
		for (int j = 0; j < m_blocksize; j++) {
			m_recovery[i][j] = roundf(IdctSigma(i, j));
		}
	}
}

void Dct::Quantizationing() {
	for (int i = 0; i < m_blocksize; i++) {
		for (int j = 0; j < m_blocksize; j++) {
			m_Fuv[i][j] = roundf(m_Fuv[i][j] /(float) LuminanceQuantizationTable[i][j]);
		}
	}
}

void Dct::InvQuantizationing() {
	for (int i = 0; i < m_blocksize; i++) {
		for (int j = 0; j < m_blocksize; j++) {
			m_Fuv[i][j] = roundf(m_Fuv[i][j] * (float)LuminanceQuantizationTable[i][j]);
		}
	}
}

void Dct::PrintMatrix(int mode)const {

	switch (mode)
	{
	case (PrintOption::YPLANE):
		for (int i = 0; i< m_blocksize; i++) {
			cout << "\t";
			for (int x = 0; x<m_blocksize; x++) {
				cout << (int)m_yplane[i][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
		break;
	case (PrintOption::DCT):
		for (int i = 0; i<m_blocksize; i++) {
			cout << "\t";
			for (int x = 0; x<m_blocksize; x++) {
				cout << (int)m_Fuv[i][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
		break;
	case (PrintOption::RECOVER):
		for (int i = 0; i<m_blocksize; i++) {
			cout << "\t";
			for (int x = 0; x<m_blocksize; x++) {
				cout << (int)m_recovery[i][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
		break;
	case (PrintOption::ERROR):
		int accumulate_error = 0;
		for (int i = 0; i < m_blocksize; i++) {
			cout << "\t";
			for (int x = 0; x < m_blocksize; x++) {
				cout << (int) m_yplane[i][x] - (int)m_recovery[i][x] << " ";
				accumulate_error += abs((int)m_yplane[i][x] - (int)m_recovery[i][x]);
			}
			cout << endl;
		}
		cout << "\t[Mean Absolute Error] " << accumulate_error / (float)m_blocksize / (float)m_blocksize << endl;
		cout << endl;
		break;
	}

}
