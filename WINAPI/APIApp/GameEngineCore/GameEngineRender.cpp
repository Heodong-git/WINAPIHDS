#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineString.h>	
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

GameEngineActor* GameEngineRender::GetActor()
{
	return GetOwner<GameEngineActor>();
}


// ��½� ����� �̹��� ����
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	// ���ӿ��� ���ҽ� Ŭ�������� �̹����� ã�Ƽ� ����
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}

// ���ڷ� ���� ������ order ����
void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;
	// ���� �־��� �Ŀ� �������� ������ ������ Level �� ������ map �� �߰�
	Owner->GetLevel()->PushRender(this);
}

// �����Ӱ� ����
void GameEngineRender::SetFrame(int _Frame)
{
	// �̹����� ���ٸ�
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʴ� �������� �������� �����Ϸ��� �߽��ϴ�.");
	}

	// Cut �̹����� �ƴ϶�� 
	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	// Index ������ �Ѿ�ٸ� 
	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("�������� ���� �̹����ε��� �Դϴ�.");
	}

	Frame = _Frame;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	// ����ð����� ��ŸŸ���� �����Ͽ� ���־� 
	// ��µǴ� �ð��� �Ѿ���� Ȯ��
	CurrentTime -= _DeltaTime;

	// ��½ð��� �Ѿ�ٸ� 
	if (CurrentTime <= 0.0f)
	{
		// �����ε����� ++�Ͽ� ���� �̹����� ���
		++CurrentIndex;
		// ����, �����ε����� ����� Index �� �������� ũ�ų� ���ٸ� 
		if (FrameIndex.size() <= CurrentIndex)
		{
			// ���� �ִϸ��̼��� ��� ù��° �ε������� �ٽý���.
			if (true == Loop)
			{
				CurrentIndex = 0;
			}

			// ���� �ִϸ��̼��� �ƴ� ��� �ε����� ������ �ε����� �����Ѵ�.  
			else
			{
				CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
			}
		}

		CurrentTime = FrameTime[CurrentIndex];
	}
}
// ������
void GameEngineRender::Render(float _DeltaTime)
{
	// ���� �ִϸ��̼��� nullptr �� �ƴ϶��
	// �ִϸ��̼����� ����ؾ��Ѵ�. 
	if (nullptr != CurrentAnimation)
	{
		// ���� ������ �ִϸ��̼��� ����ȣ��
		CurrentAnimation->Render(_DeltaTime);
		// �������� ���� �ִϸ��̼ǿ� ����Ǿ� �ִ� ���� �ε�����
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		// �̹����� ����ִϸ��̼��� �̹����� �ȴ�. 
		Image = CurrentAnimation->Image;
	}

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	// ��µ� ��ǥ�� �������� ������ ������ ��ġ + �߰� �����ǰ�
	float4 RenderPos = GetActor()->GetPos() + Position - CameraPos;

	// Ŀ�õ� �̹������
	if (true == Image->IsImageCutting())
	{
		// �����Ӵ� Ʈ����ī�� ���
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale , TransColor);
	}
	// Ŀ�õ� �̹����� �ƴ϶��
	else
	{
		// �׳� �̹��� ��ü�� �Էµ� ũ��� ����Ѵ�. 
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, { 0, 0 }, Image->GetImageScale() , TransColor);
	}
}

// �ִϸ��̼� ����
void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	// ���ڷ� ���� Ű���� �̹����� ã�Ƽ� �޾ƿ´�. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
	}

	// �̹����� Ŀ�õǾ����� �ʴٸ� ������������ �Ұ����ϴ�. 
	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	// �ô빮�ڷ� ����
	std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

	// ���� �̸��� �ִϸ��̼��� �̹� �����Ѵٸ� assert 
	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼� �Դϴ�." + UpperName);
	}

	// �ʿ��� ���ڷε��� Ű���� �����͸� �޾ƿ´�. 
	// ���� ����, Ű������ �����Ͱ� �����Ѵٸ� �׳༮�� ��ȯ
	// �������� �ʴ´ٸ� �� Ű������ �����͸� �߰��Ѵ�. (?) Ȯ���ʿ� 
	FrameAnimation& NewAnimation = Animation[UpperName];

	NewAnimation.Image = Image;

	// ���ڷε��� ����ü�� �������ε��� �迭�� ũ�Ⱑ 0 �� �ƴ϶��
	if (0 != _Paramter.FrameIndex.size())
	{
		// �ε��� ���� �״�� ����
		NewAnimation.FrameIndex = _Paramter.FrameIndex;
	}
	else
	{
		// �������ε��� �迭�� ũ�Ⱑ 0 �̶��
		for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	// �� �����Ӻ� �ð��� ����Ѵ�.
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Paramter.InterTime);
		}
	}

	// Loop ����
	NewAnimation.Loop = _Paramter.Loop;
	// this �� �ִϸ��̼��� �θ�� ����
	NewAnimation.Parent = this;
}

// ü�����ִϸ��̼�
// �������� �ִϸ��̼��� ���ڷ� �־��� Ű���� �ش��ϴ� �ִϸ��̼����� ��ü�Ѵ�. 
void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName)
{
	// �빮�� ��ȯ
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	// ���ڷ� ���� Ű������ ������ Ű���� �������� �ʴ´ٸ� ����� �ִϸ��̼��� ���ٴ� �ǹ�. 
	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ�." + UpperName);
	}

	// ���� �����Ӱ� ���� �ִϸ��̼��� ����Ϸ��� �Ѵٸ� return
	// ������ ����� �ִϸ��̼��̶�� ������ �ε����� �����ϰ� �Ѵ�.
	if (CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	// ���� �ִϸ��̼��� ����� �ִϸ��̼����� ��ü
	CurrentAnimation = &Animation[UpperName];

	// �ִϸ��̼��� ��ü �Ǿ��� ������ �ε����� 0���� ����
	CurrentAnimation->CurrentIndex = 0;
	
	// �ִϸ��̼��� ����ð��� ����� �ִϸ��̼��� ������Ÿ������ ����
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}