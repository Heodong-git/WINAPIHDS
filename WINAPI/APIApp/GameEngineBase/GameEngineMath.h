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
	static const float4 Zero;
	static const float4 Null;

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
	// w �ุ �� 1.0 ������ 3d ��. ( ���� 3d���� ���� ) 


	// float Ÿ���� x,y,z,w ���� ���� static_cast�� int Ÿ������ ����ȯ�Ͽ� ��ȯ�Ѵ�. 
	int ix() const  
	{
		return static_cast<int>(x);
	}

	int iy() const 
	{
		return static_cast<int>(y);
	}

	int iz() const  
	{
		return static_cast<int>(z);
	}

	int iw() const  
	{
		return static_cast<int>(w);
	}

	// ������ �� ���� ������ ���� ��ȯ
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	// ����
	// half �Լ��� ȣ���ϸ� this �� x, y, z ���� �������� �Ͽ� �� ���� ��ȯ�Ѵ�. 
	float4 half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.f, w };
	}

	// ��� ���� ���� 0���� üũ
	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	// ���۷����� *
	// const ��ü�� �� �Լ��� ȣ�� �� �� �ֵ��� �ϱ� ���� �ڿ� const Ű���带 �ٿ��ش�. 
	float4 operator *(const float& _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;

		return Return;
	}

	float4 operator +(const float4 _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}


	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}


	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}

	// ���۷����� +=
	float4 operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}
};