#pragma once
// c++이 실행되는 곳에서 사용할수 있는 모든 문자열 관련 처리방식을 지원
#include <filesystem>

// 경로
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	// 패스의 문자열 반환 
	std::string GetPathToString() const;

	// 나를 소유하고 있는 이전 경로로 이동
	// 즉, 현재경로의 가장마지막 경로를 삭제하는것.
	void MoveParent();

	// 특정 경로나 특정파일이 있는 곳으로 이동
	void MoveParentToChildPath(const std::string_view& _String);

	// 경로가 존재하는지 확인
	bool IsExists();

	// 경로에 인자로 들어온 경로를 이어붙이고 그 경로가 존재하는지 확인 
	bool IsExistsToPlusString(const std::string_view& _String);

	// 현재 경로가 마지막 경로라면 true, 아니라면 false 를 반환
	bool IsRoot();
	
	// 현재 경로에 다음 경로를 추가한다. 
	bool Move(const std::string_view& _Path);
protected:

private:
	// std::filesystem::path <--- 데이터타입
	std::filesystem::path Path;
};

// std::filesystem 