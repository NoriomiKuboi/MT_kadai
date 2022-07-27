#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DebugText.h"
#include "Audio.h"
#include "CameraSub.h"
#include "Light.h"
#include "FbxLoader.h"

class GameScene
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	static const int debugTextTexNumber = 0;

public:
	GameScene();
	~GameScene();

	void Init(DirectXCommon* dxCommon, Input* input, Audio* audio); // ������
	void Update(); // �X�V
	void Draw(); // �`��
	void CreateParticles(); // �p�[�e�B�N������

private:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	// �Q�[���V�[���p
	// �J����
	CameraSub* camera = nullptr;

	// �X�v���C�g
	Sprite* sprite1 = nullptr;
	Sprite* sprite2 = nullptr;
	Sprite* sprite3 = nullptr;

	// �p�[�e�B�N��
	ParticleManager* particleMan = nullptr;

	// 3dObj
	Model* modelSample = nullptr;
	Object3d* objSample = nullptr;

	// ���C�g
	Light* light = nullptr;

	// �ۑ�6�p�̕ϐ�
	//---���ρE�O��---//
	XMFLOAT2 circlePos;
	XMFLOAT2 linePos;
	const float vec2 = 2.0f;
	bool trigger;

	const XMFLOAT2 center = { 1280.0f / 2.0f ,720.0f / 2.0f };

	const float circleRadius = 16.0f;
	XMFLOAT2 start;
	XMFLOAT2 end;
	float NormalizeVector(XMFLOAT2 vec);
	//---------------//
};