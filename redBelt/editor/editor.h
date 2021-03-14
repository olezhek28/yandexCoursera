#pragma once

#include <string>
#include <string_view>

using namespace std;

class Editor
{
public:
	Editor() = default;
	void Left();   // �������� ������ �����
	void Right();  // �������� ������ ������
	void Insert(char token);   // �������� ������ token
	void Copy(size_t tokens);  // c����������
	// �� ����� tokens ��������,
	// ������� � ������� ������� �������
	void Cut(size_t tokens);  // �������� �� ����� tokens ��������,
	// ������� � ������� ������� �������
	void Paste();  // �������� ���������� ������
	// � ������� ������� �������
	string GetText() const;  // �������� ������� ����������
	// ���������� ���������

private:
	string text;
	size_t cursorPosition = 0;
	string_view buffer;
};

