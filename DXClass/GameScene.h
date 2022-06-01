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

	// 課題3用の変数
	//---衝突と反発---//
	XMFLOAT2 pos1;
	XMFLOAT2 vec1;
	XMFLOAT2 pos2;
	XMFLOAT2 vec2;
	bool trigger;
	bool flag;
	float e;

	bool hit(XMFLOAT2 pos1,float r1, XMFLOAT2 pos2, float r2);
	//---------------//
};