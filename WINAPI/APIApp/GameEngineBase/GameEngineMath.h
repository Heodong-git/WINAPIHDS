#pragma once

// final Ű���� : �ش� Ű���尡 �ԷµǾ� �ִٸ� �� Ŭ������ ����� ������ ���Ѵ�.
class GameEngineMath final
{
public:
	static const float PIE;
	static const float PIE2;

private:
	// �Ҹ��ڸ� ���������Լ��� �����������ν� 
	// �� Ŭ������ ��ӺҰ�, ��ü�����Ұ��� ���°� �Ǿ� 
	// ������ ������ ����ϱ� ���� �뵵�θ� ����Ѵ�. 
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
	// w �ุ �� 1.0 ������ 3d ��. ( ���� 3d���� ���� ) 


	// float Ÿ���� x,y,z,w ���� ���� static_cast�� int Ÿ������ ����ȯ�Ͽ� ��ȯ�Ѵ�. 
	int ix() {
		return static_cast<int>(x);
	}

	int iy() {
		return static_cast<int>(y);
	}

	int iz() {
		return static_cast<int>(z);
	}

	int iw() {
		return static_cast<int>(w);
	}
};