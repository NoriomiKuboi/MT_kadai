#include "FbxLoader.h"

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
const std::string FbxLoader::baseDirectory = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Init(ID3D12Device* device)
{
    // �������烁���o�ϐ��ɑ��
    this->device = device;
    // FBX�}�l�[�W���̐���
    fbxManager = FbxManager::Create();
    // FBX�}�l�[�W���̓��o�͐ݒ�
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    // FBX�C���|�[�^�̐���
    fbxImporter = FbxImporter::Create(fbxManager,"");
}

void FbxLoader::Final()
{
    // �e��FBX�C���X�^���X�̔j��
    fbxImporter->Destroy();
    fbxManager->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
    // ���f���Ƃ���Ȃ����O�̃t�H���_����ǂݍ���
    const string directoryPath = baseDirectory + modelName + "/";
    //�g���q.fbx��t��
    const string fileName = modelName + ".fbx";
    // �A�����ăt���p�X�𓾂�
    const string fullpath = directoryPath + fileName;

    // �t�@�C�������w�肵��FBX�t�@�C����ǂݍ���
    if (!fbxImporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings()))
    {
        assert(0);
    }

    // �V�[������
    FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

    // �t�@�C�����烍�[�h����FBX�̏����V�[���ɃC���|�[�g
    fbxImporter->Import(fbxScene);
}

void FbxLoader::ParseNodeRecursive(Model* model, FbxNode* fbxNode)
{

}
