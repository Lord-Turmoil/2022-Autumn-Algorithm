/********************************************************************
** E1 - I
*/

#include <cstdio>
#include <algorithm>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

using std::swap;

const int BUFFER_SIZE = 2048;

#define MAPPING(x, y, w) ((x) + (y) * (w))

bool _bufferA[BUFFER_SIZE * BUFFER_SIZE];
bool _bufferB[BUFFER_SIZE * BUFFER_SIZE];
bool *buffer[] = { _bufferA, _bufferB };

class Matrix
{
public:
	Matrix() : _size(0), _buffer(nullptr) {}

	void SetSize(int size) { _size = size; }
	int GetSize() const { return _size; }
	
	void SetBuffer(bool* pBuffer) { _buffer = pBuffer; }
	bool* GetBuffer() { return _buffer; }
	
	void Draw();
	void Copy(int x, int y, Matrix* dest);
	void Flip();
	void MakeUnit();
	void Decorate();

	Matrix& operator=(const Matrix& matrix)
	{
		_size = matrix._size;
		_buffer = matrix._buffer;

		return *this;
	};

private:
	int _size;
	bool* _buffer;
};

int main()
{
	int n;
	int id = 0;
	int size;
	Matrix src;
	Matrix dest;

	scanf("%d", &n);
	src.SetBuffer(buffer[0]);
	src.MakeUnit();
	dest.SetSize(7);
	dest.SetBuffer(buffer[1]);
	for (int i = 1; i < n; i++)
	{
		src.Copy(src.GetSize() + 1, 0, &dest);
		src.Flip();
		src.Copy(0, 0, &dest);

		dest.Decorate();

		swap(src, dest);
		dest.SetSize(src.GetSize() * 2 + 1);
	}
	src.Draw();


	return 0;
}

void Matrix::Draw()
{
	bool* pBuffer = _buffer;
	
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
			putchar(pBuffer[j] ? '*' : ' ');
		putchar('\n');
		pBuffer += _size;
	}
}

void Matrix::Copy(int x, int y, Matrix* dest)
{
	bool* pDestBuffer = dest->GetBuffer();
	bool* pSrcBuffer = _buffer;
	int destSize = dest->GetSize();
	int srcSize = _size;
	int destX = x;
	int destY = y;

	pDestBuffer += (destY * destSize) + destX;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
			pDestBuffer[j] = pSrcBuffer[j];
		pDestBuffer += destSize;
		pSrcBuffer += srcSize;
	}
}

void Matrix::Flip()
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < i; j++)
			swap(_buffer[MAPPING(i, j, _size)], _buffer[MAPPING(j, i, _size)]);
	}
}

void Matrix::MakeUnit()
{
	bool* pSrcBuffer = _buffer;
	_size = 3;

	pSrcBuffer[0] = pSrcBuffer[1] = pSrcBuffer[2] = true;
	
	pSrcBuffer += _size;
	pSrcBuffer[0] = pSrcBuffer[1] = false;
	pSrcBuffer[2] = true;
	
	pSrcBuffer += _size;
	pSrcBuffer[0] = pSrcBuffer[1] = pSrcBuffer[2] = true;
}
	
void Matrix::Decorate()
{
	int n = _size / 2;

	bool* pUpperBuffer = _buffer;
	bool* pLowerBuffer = _buffer + (_size - 1) * _size;

	pUpperBuffer[n] = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < _size; j++)
			pLowerBuffer[j] = pUpperBuffer[j];
		if (i != 0)
			pUpperBuffer[n] = pLowerBuffer[n] = false;

		pLowerBuffer -= _size;
		pUpperBuffer += _size;
	}
	for (int j = 0; j < _size; j++)
		pUpperBuffer[j] = false;
	pUpperBuffer[n + 1] = true;
}
