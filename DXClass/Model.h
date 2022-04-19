#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Mesh.h"

struct Node
{

};

class Model
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// フレンドクラス
	friend class FbxLoader;

private:
	static const std::string baseDirectory;

private:
	static ID3D12Device* dev;
	static UINT descriptorHandleIncrementSize;

public:
	static void StaticInit(ID3D12Device* dev); //初期化
	static Model* CreateFromOBJ(const std::string& modelname, bool smoothing = false); // OBJファイルからメッシュ生成

public:
	~Model();
	void Init(const std::string& modelname, bool smoothing); // 初期化
	void Draw(ID3D12GraphicsCommandList* cmdList); // 描画

private:
	std::string name; // 名前
	std::vector<Mesh*> meshes; // メッシュコンテナ
	std::unordered_map<std::string, Material*> materials; // マテリアルコンテナ
	Material* defaultMaterial = nullptr; // デフォルトマテリアル
	ComPtr<ID3D12DescriptorHeap> descHeap; // デスクリプタヒープ

private:
	void LoadMaterial(const std::string& directoryPath, const std::string& filename); // マテリアル読み込み
	void AddMaterial(Material* material); // マテリアル登録
	void CreateDescriptorHeap(); // デスクリプタヒープの生成
	void LoadTextures(); // テクスチャ読み込み
};

