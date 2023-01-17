#pragma once
#include <string>
#include <string_view>

// ���� :
class GameEngineString
{
public:
	// ��ҹ��� �Ǽ��� �����ϱ� ���� ���ڷ� ���� ���ڿ���
	// ��� �빮�ڷ� �����Ͽ� ��ȯ
	static std::string ToUpper(const std::string_view& _Str);
	
protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();
	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

};

// �� Ŭ������ �� �������?
// ���ڿ��� ����Ͽ� �ڵ带 �ۼ��� �� ��,�ҹ����� ���� ������ 
// ������ �߻��ϴ� �κ��� ������ �����ϱ� ���ؼ�, �ش� Ŭ������ �����
// Ŭ���� ���ο� ToUpper �Լ��� ����, ���ڿ��� ��� �빮�ڷ� ��ȯ�Ͽ� ����ϱ� ����

// string_view �� �� ����ϳ�?
// ���������� ���ڿ��� ���� �����Ϳ� ���̸� ������ ������ �ӽð�ü�� �������� �ʱ� ����.
