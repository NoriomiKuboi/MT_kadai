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
	// �t�����h�N���X
	friend class FbxLoader;

private:
	static const std::string baseDirectory;

private:
	static ID3D12Device* dev;
	static UINT descriptorHandleIncrementSize;

public:
	static void StaticInit(ID3D12Device* dev); //������
	static Model* CreateFromOBJ(const std::string& modelname, bool smoothing = false); // OBJ�t�@�C�����烁�b�V������

public:
	~Model();
	void Init(const std::string& modelname, bool smoothing); // ������
	void Draw(ID3D12GraphicsCommandList* cmdList); // �`��

private:
	std::string name; // ���O
	std::vector<Mesh*> meshes; // ���b�V���R���e�i
	std::unordered_map<std::string, Material*> materials; // �}�e���A���R���e�i
	Material* defaultMaterial = nullptr; // �f�t�H���g�}�e���A��
	ComPtr<ID3D12DescriptorHeap> descHeap; // �f�X�N���v�^�q�[�v

private:
	void LoadMaterial(const std::string& directoryPath, const std::string& filename); // �}�e���A���ǂݍ���
	void AddMaterial(Material* material); // �}�e���A���o�^
	void CreateDescriptorHeap(); // �f�X�N���v�^�q�[�v�̐���
	void LoadTextures(); // �e�N�X�`���ǂݍ���
};

