#include "GameEngineString.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

std::string GameEngineString::ToUpper(const std::string_view& _Str)
{
	// string_view �� ����Ǿ� �ִ� ���ڿ���
	// string Ŭ������ �����Ѵ�. 
	std::string Text = _Str.data();

	// toupper ��� �Լ��� ���ڿ��� �ϳ��� �ٲ��־�� �ϱ� ������
	// for���� ����Ͽ� �빮�ڷ� �����Ͽ� �ٽ� �ϳ��� �������ش�.
	for (size_t i = 0; i < Text.size(); i++)
	{
		Text[i] = toupper(Text[i]);
	}

	// ����� ���� ��ȯ
	return Text;
}