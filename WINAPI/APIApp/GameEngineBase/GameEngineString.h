#pragma once
#include <string>
#include <string_view>

// 설명 :
class GameEngineString
{
public:
	// 대소문자 실수를 방지하기 위해 인자로 들어온 문자열을
	// 모두 대문자로 변경하여 반환
	static std::string ToUpper(const std::string_view& _Str);
	
	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

};

