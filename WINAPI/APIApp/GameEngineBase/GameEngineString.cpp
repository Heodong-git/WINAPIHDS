#include "GameEngineString.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

std::string GameEngineString::ToUpper(const std::string_view& _Str)
{
	// string_view 에 저장되어 있는 문자열을
	// string 클래스에 저장한다. 
	std::string Text = _Str.data();

	// toupper 라는 함수는 문자열을 하나씩 바꿔주어야 하기 때문에
	// for문을 사용하여 대문자로 변경하여 다시 하나씩 저장해준다.
	for (size_t i = 0; i < Text.size(); i++)
	{
		Text[i] = toupper(Text[i]);
	}

	// 변경된 값을 반환
	return Text;
}

// 값을 넣어주면 문자로 변환
std::string GameEngineString::ToString(int Value)
{
	return std::to_string(Value);
}