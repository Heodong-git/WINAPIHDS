#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>

// static �����̱� ������ cpp �ֻ�ܿ� �����ؾ� ��밡��
GameEngineResources GameEngineResources::Inst;

GameEngineResources::GameEngineResources()
{
}

GameEngineResources::~GameEngineResources()
{
}

// ��� �������ߴ���? Ȯ���Ұ�
void GameEngineResources::Release()
{
	// ���� ���ϴ� ������ ���ϴ� ���� ��Ȯ�ϰ� 
	for (std::pair<std::string, GameEngineImage*> Pair : AllImage)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}

	AllImage.clear();
}

// ��θ� ���ڷ� �޾Ƽ� ���, ��ο� �ִ� ���ϸ���
// �����ε��� �Լ��� ���ڷ� �־� ȣ���Ͽ� �̹����� �ε�. 
GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	// GameEngineString Ŭ������ �Լ��� ȣ���Ͽ�
	// ���ڷ� ���� �����̸��� �빮�ڷ� �����Ѵ�. 
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// �ߺ��̹����� �ε��Ϸ��� �Ѵٸ� assert 
	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert("�̹� �ε��� �̹����� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
		return nullptr;
	}

	// �̹��� Ŭ���� �����Ҵ�
	GameEngineImage* NewImage = new GameEngineImage();
	// ������ �̹����� �̹����ε�
	NewImage->ImageLoad(_Path);
	// GameEngineResources�� �����ϴ� map �� ����
	AllImage.insert(std::make_pair(UpperName, NewImage));

	// ���������� �̹����ε尡 �Ϸ� �Ǿ��� ������ true ��ȯ
	return NewImage;
}

GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	// �빮�ڷ� ����Ǿ� �ֱ� ������ �����̸��� �빮�ڷ� ��ȯ 
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// �̹����� �����ϰ� �ִ� �ʿ��� ���ڿ�Ű���� ���� �����͸� ã�´�. 
	std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

	// ���� �ʿ� �����Ͱ� ����Ǿ� ���� �ʴٸ� ������� ���� �̹����� ����Ϸ��� �� ��.
	if (AllImage.end() == FindIter)
	{
		MsgAssert("�ε����� ���� �̹����� ����Ϸ��� �߽��ϴ�" + UpperName);
		return nullptr;
	}

	// ���������� �̹����� ã�Ҵٸ� �����͸� ��ȯ�Ѵ�. 
	return FindIter->second;
}
