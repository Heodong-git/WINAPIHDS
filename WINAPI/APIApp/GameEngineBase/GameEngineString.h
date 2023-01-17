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

// 이 클래스는 왜 만들었나?
// 문자열을 사용하여 코드를 작성할 때 대,소문자의 구분 때문에 
// 에러가 발생하는 부분을 사전에 차단하기 위해서, 해당 클래스를 만들고
// 클래스 내부에 ToUpper 함수를 만들어서, 문자열을 모두 대문자로 변환하여 사용하기 위함

// string_view 는 왜 사용하나?
// 내부적으로 문자열에 대한 포인터와 길이만 가지기 때문에 임시객체를 생성하지 않기 때문.
