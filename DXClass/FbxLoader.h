#pragma once

#include "fbxsdk.h"
#include "Model.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <assert.h>

class FbxLoader
{
private:
	// std::���ȗ�
	using string = std::string;

public:	// �萔
	// ���f���i�[���[�g�p�X
	static const string baseDirectory;
public:
	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device">D3D12�f�o�C�X
	void Init(ID3D12Device* device);

	/// <summary>
	/// ��n��
	/// </summary>
	void Final();

	/// <summary>
	/// �t�@�C������FBX���f���ǂݍ���
	/// </summary>
	/// <param name="modelName"></param>
	void LoadModelFromFile(const string& modelName);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"�ǂݍ��ݐ惂�f���I�u�W�F�N�g</param>
	/// <param name="fbxNode">��͑Ώۂ̃m�[�h</param>
	void ParseNodeRecursive(Model* model, FbxNode* fbxNode);

private:
	// private�ȃR���X�g���N�^�i�V���O���g���p�^�[���j
	FbxLoader() = default;
	// private�ȃf�X�g���N�^�i�V���O���g���p�^�[���j
	~FbxLoader() = default;
	// �R�s�[�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	FbxLoader(const FbxLoader& obj) = delete;
	// �R�s�[������Z�q���֎~�i�V���O���g���p�^�[���j
	void operator=(const FbxLoader& obj) = delete;
	// D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	// FBX�}�l�[�W��
	FbxManager* fbxManager = nullptr;
	// FBX�C���|�[�^
	FbxImporter* fbxImporter = nullptr;
};