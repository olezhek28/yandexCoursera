#pragma once

#include <string>
#include <string_view>

using namespace std;

class Editor
{
public:
	Editor() = default;
	void Left();   // сдвинуть курсор влево
	void Right();  // сдвинуть курсор вправо
	void Insert(char token);   // вставить символ token
	void Copy(size_t tokens);  // cкопировать
	// не более tokens символов,
	// начиная с текущей позиции курсора
	void Cut(size_t tokens);  // вырезать не более tokens символов,
	// начиная с текущей позиции курсора
	void Paste();  // вставить содержимое буфера
	// в текущую позицию курсора
	string GetText() const;  // получить текущее содержимое
	// текстового редактора

private:
	string text;
	size_t cursorPosition = 0;
	string_view buffer;
};

