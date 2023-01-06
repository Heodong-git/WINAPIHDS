#pragma once
// c++�� ����Ǵ� ������ ����Ҽ� �ִ� ��� ���ڿ� ���� ó������� ����
#include <filesystem>

// ���
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

	// �н��� ���ڿ� ��ȯ 
	std::string GetPathToString() const;

	// ���� �����ϰ� �ִ� ���� ��η� �̵�
	// ��, �������� ���帶���� ��θ� �����ϴ°�.
	void MoveParent();

	// Ư�� ��γ� Ư�������� �ִ� ������ �̵�
	void MoveParentToChildPath(const std::string_view& _String);

	// ��ΰ� �����ϴ��� Ȯ��
	bool IsExists();

	// ��ο� ���ڷ� ���� ��θ� �̾���̰� �� ��ΰ� �����ϴ��� Ȯ�� 
	bool IsExistsToPlusString(const std::string_view& _String);

	// ���� ��ΰ� ������ ��ζ�� true, �ƴ϶�� false �� ��ȯ
	bool IsRoot();
	
	// ���� ��ο� �߰� ��θ� �̾���̰� ���� ��θ� �߰��� ��η� �����Ѵ�.
	bool Move(const std::string_view& _Path);
protected:

private:
	// std::filesystem::path <--- ������Ÿ��
	std::filesystem::path Path;
};

// std::filesystem 