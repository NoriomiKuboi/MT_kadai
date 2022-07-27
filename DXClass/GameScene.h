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

	void Init(DirectXCommon* dxCommon, Input* input, Audio* audio); // 初期化
	void Update(); // 更新
	void Draw(); // 描画
	void CreateParticles(); // パーティクル生成

private:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	// ゲームシーン用
	// カメラ
	CameraSub* camera = nullptr;

	// スプライト
	Sprite* sprite1 = nullptr;
	Sprite* sprite2 = nullptr;
	Sprite* sprite3 = nullptr;

	// パーティクル
	ParticleManager* particleMan = nullptr;

	// 3dObj
	Model* modelSample = nullptr;
	Object3d* objSample = nullptr;

	// ライト
	Light* light = nullptr;

	// 課題6用の変数
	//---内積・外積---//
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