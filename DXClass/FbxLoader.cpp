#include "FbxLoader.h"

/// <summary>
/// 静的メンバ変数の実態
/// </summary>
const std::string FbxLoader::baseDirectory = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Init(ID3D12Device* device)
{
    // 引数からメンバ変数に代入
    this->device = device;
    // FBXマネージャの生成
    fbxManager = FbxManager::Create();
    // FBXマネージャの入出力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    // FBXインポータの生成
    fbxImporter = FbxImporter::Create(fbxManager,"");
}

void FbxLoader::Final()
{
    // 各種FBXインスタンスの破棄
    fbxImporter->Destroy();
    fbxManager->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
    // モデルとおんなじ名前のフォルダから読み込む
    const string directoryPath = baseDirectory + modelName + "/";
    //拡張子.fbxを付加
    const string fileName = modelName + ".fbx";
    // 連結してフルパスを得る
    const string fullpath = directoryPath + fileName;

    // ファイル名を指定してFBXファイルを読み込む
    if (!fbxImporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings()))
    {
        assert(0);
    }

    // シーン生成
    FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

    // ファイルからロードしたFBXの情報をシーンにインポート
    fbxImporter->Import(fbxScene);
}

void FbxLoader::ParseNodeRecursive(Model* model, FbxNode* fbxNode)
{

}
