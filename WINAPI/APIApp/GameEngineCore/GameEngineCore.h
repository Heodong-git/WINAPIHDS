#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// ���漱���� ���� Ŭ������ ���������� ����� �� ����, ��ü�����Ͽ� �Լ� ȣ����� �Ұ���
// �������� �ʼ������� �ε��ؾ��� �κ��� ���
class GameEngineLevel;
class GameEngineCore
{
private:
	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	// ���α׷��� ����
	void CoreStart(HINSTANCE _instance);

protected:
	// ���ø��Լ��� �ۼ��Ͽ� �Լ�ȣ��� ������Ÿ���� �Է¹޴´�. 
	// ���ο��� ��ӹ��� Ŭ�������� �����Ҵ� �� ��ĳ���� �Ǿ� �θ�Ŭ���� Ÿ�� ������ ������
	// ����Ǳ� ������ ��ӹ��� ���� Ŭ�������� �Էµǰ� �ȴٸ� ����.
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		// ���ڷ� ���� Ű���� �Ǵ� ���ڿ��� end() �� �ƴ϶��
		// �̹� �ش� Ű������ �����Ͱ� ����Ǿ� �ִٴ� �ǹ��̴�. 
		if (Levels.end() != Levels.find(_Name.data()))
		{
			// ���ڷ� ���� ���ڿ��� ǥ�����ָ� assert
			std::string Name = _Name.data();
			MsgAssert(Name + "�̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
			return;
		}

		// Ű������ �����͸� �������ش�. 
		GameEngineLevel* Level = new LevelType();
		// ���� ���� �� �ش� ������ �ʿ��� ������ �ε�
		LevelLoading(Level);
		// ������ ������ ����
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	// ���ڷ� ���� Ű������ ����� �����Ѵ�. 
	void ChangeLevel(const std::string_view& _Name);

	// ��ӹ޴� Ŭ������ �ݵ�� �� �Լ����� �����ؾ� �Ѵ�. 
	// �θ�Ŭ������ �߻�Ŭ������ ��� , �ڽ�Ŭ�������� �������� �ʴ´ٸ�
	// �ڽ�Ŭ������ �߻�Ŭ������ �Ǿ� ��ü�� �������� ���ϰ� �ȴ�. 
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// ���ڿ� Ű������ ���������� ����
	std::map<std::string, GameEngineLevel*> Levels;

	GameEngineLevel* MainLevel = nullptr;
	
	// �����ε��Լ� (��ȯ��������, ��ɺи�)
	void LevelLoading(GameEngineLevel* _Level);
};