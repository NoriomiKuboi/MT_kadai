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

	// �p�[�e�B�N��
	ParticleManager* particleMan = nullptr;

	// 3dObj
	Model* modelSample = nullptr;
	Object3d* objSample = nullptr;

	// ���C�g
	Light* light = nullptr;

	// �ۑ�1�p�̕ϐ�
	//---���R����---//
	const float gravity = 9.8f / 60.0f;
	XMFLOAT2 pos1;
	XMFLOAT2 vec1;
	bool trigger1;
	//-------------//

	//---�Ε�����---//
	const float p = 3.141592f;
	const float deg = 45.0f;
	const float angle = deg * p / 180.0f;
	const float v0 = 10.0f;
	XMFLOAT2 pos2;
	XMFLOAT2 vec2;
	bool trigger2;
	//-------------//
};