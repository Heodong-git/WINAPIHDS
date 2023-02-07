#pragma once
#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

// 설명 : Image로 숫자출력을 해주는 클래스
//        세팅되는 이미지는 무조건 10개로 컷팅되어있어야 한다.
//        넣어줘야할건 무조건 Actor계열이여야 합니다.
class GameEngineActor;
class NumberRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	NumberRenderObject();
	~NumberRenderObject();

	// delete Function
	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;

	// 
	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order);
	void SetValue(int _Value);

protected:

private:
	int Order;
	float4 NumberScale;
	float4 Pos;
	int Value = 0;
	// GameEngineImage* NumberImage;

	std::string_view ImageName;

	std::vector<GameEngineRender*> NumberRenders;
};

