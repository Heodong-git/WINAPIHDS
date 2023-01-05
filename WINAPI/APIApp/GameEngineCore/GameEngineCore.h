#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// �������� �ʼ������� �ε��ؾ��� �κ��� ����Ѵ�. �̹���, ���� ���ҽ� ��
// ���漱���� ���� Ŭ������ ���������� ����� �� ����, ��ü�����Ͽ� �Լ� ȣ����� �Ұ����ϴ�. 
class GameEngineLevel;
class GameEngineCore
{
private:
	// ���� ���ӽ���, ������, ��������� �����ؾ��� ������ �ۼ��Ǽ� �Է��ϰ� �ȴ�. 
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

	// ���α׷��� ���۽�Ų��. 
	void CoreStart(HINSTANCE _instance);

protected:
	// template �Լ��� �����������ν� �Լ�ȣ��ÿ�
	// ���ϴ� ������Ÿ���� �ۼ��Ͽ� ȣ���ϰ� �Ǹ� �ʿ� �ش��ϴ� Ÿ������ �������� �� �ִ�. 
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		// ���ڷ� ���� Ű���� �Ǵ� ���ڿ��� end() �� �ƴ϶��
		// �̹� �ش� Ű������ �����Ͱ� ����Ǿ� �ִٴ� �ǹ��̴�. 
		if (Levels.end() != Levels.find(_Name.data()))
		{
			// ���ڷ� ���� ���ڿ��� ǥ�����ָ� assert ó��
			std::string Name = _Name.data();
			MsgAssert(Name + "�̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
			return;
		}

		// �װ� �ƴ϶�� Ű������ �����͸� �������ش�. 
		// ���ڷ� ���� ������ �����Ѵ�. 
		GameEngineLevel* Level = new LevelType();
		// ������ ������ �Ŀ��� �ش��ϴ� �������� �ʿ��� �����͸� �ε��Ѵ�.
		LevelLoading(Level);
		// �����͸� �ʿ� �������ش�. 
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	// ���ڷ� ���� Ű������ ����� �����Ų��. 
	void ChangeLevel(const std::string_view& _Name);

	// ����� �޴� Ŭ������ �ݵ�� �� �Լ����� �������־�� �Ѵ�. 
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// Ű���� ����� Ž���ϴ� �κп� Ưȭ�Ǿ� ����
	std::map<std::string, GameEngineLevel*> Levels;

	// ���� ���õǾ� �ִ� ���η���
	GameEngineLevel* MainLevel = nullptr;

	// Core ������� Level ����� ��Ŭ��� ���� �ʱ� ���� ����� �и�
	void LevelLoading(GameEngineLevel* _Level);
};

// ����