#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
using namespace DirectX;

GameScene::GameScene()
{
	circlePos = { 1280.0f / 2.0f,720.0f / 2.0f };
	linePos = { 1280.0f / 2.0f + 16.0f,720.0f / 2.0f - 200.0f };
	y = 0.0f;
	mass = 10.1f;
	k = 0.3f;
	damp = 0.97f;
	velY = 0.0f;
	accel = 0.0f;
	force = 0.0f;
	posY = 200.0f;
	trigger = false;
}

GameScene::~GameScene()
{
	safe_delete(sprite1);
	safe_delete(sprite2);
	safe_delete(sprite3);
	safe_delete(particleMan);
	safe_delete(objSample);
	safe_delete(modelSample);
	safe_delete(light);
}

void GameScene::Init(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}

	// �f�o�b�O�e�L�X�g������
	debugText.Init(debugTextTexNumber);
	
	// ����������
	srand(time(NULL));

	// �J��������
	camera = new CameraSub(WindowApp::winWidth, WindowApp::winHeight, input);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/circle.png"))
	{
		assert(0);
		return;
	}

	if (!Sprite::LoadTexture(2, L"Resources/circlePink.png"))
	{
		assert(0);
		return;
	}

	if (!Sprite::LoadTexture(3, L"Resources/line.png"))
	{
		assert(0);
		return;
	}

	// �w�i�X�v���C�g����

	// ���̑��̃X�v���C�g����
	sprite1 = Sprite::Create(1, { 0.0f,0.0f });
	sprite2 = Sprite::Create(2, { 0.0f,0.0f });
	sprite3 = Sprite::Create(3, { 0.0f,0.0f });

	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::Create(dxCommon->GetDev(), camera);

	// ���f���ǂݍ���
	modelSample = Model::CreateFromOBJ("taiyaki");

	// 3D�I�u�W�F�N�g����
	objSample = Object3d::Create(modelSample);

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(10.0f);

	objSample->SetPosition({ 0,0,0 });

	//���C�g�̐���
	light = Light::Create();

	Audio::SoundData sound = audio->SoundLoadWave("Resources/bgm1.wav");
	//audio->SoundPlayWava(sound,true);

	// ���f�������w�肵�ăt�@�C���ǂݍ���
	FbxLoader::GetInstance()->LoadModelFromFile("cube");
}

void GameScene::Update()
{
	// �p�[�e�B�N������
	CreateParticles();

	//�I�u�W�F�N�g�̉�]
	XMFLOAT3 rot = objSample->GetRotation();

	//��������������
	static XMVECTOR lightDir = { 0,1,5,0 };
	light->SetLightDir(lightDir);

	std::ostringstream debugstr;
	debugstr.str("");
	debugstr.clear();
	const XMFLOAT3& cameraPos = camera->GetEye();
	/*debugstr << "cameraPos("
		<< std::fixed << std::setprecision(2)
		<< cameraPos.x << ","
		<< cameraPos.y << ","
		<< cameraPos.z << ")";*/

	debugText.Print(debugstr.str(), 50, 90, 2.0f);
	debugText.Print("BANE", 70, 50, 2.0f);
	debugText.Print("SPACE : RESET", 70, 80, 2.0f);

	float distY = posY - y;
	force = k * distY;
	accel = force / mass;
	velY = damp * (velY + accel);

	if (input->PushKey(DIK_SPACE))
	{
		trigger = true;
	}

	else
	{
		trigger = false;
	}

	if (trigger == true)
	{
		y++;
	}

	else if (trigger == false)
	{
		y += velY;
	}

	sprite1->SetPosition({ circlePos.x, linePos.y + y });
	sprite3->SetPosition(linePos);
	sprite3->SetSize({ 1,y });

	//camera->Update();
	particleMan->Update();
	objSample->Update();

	//���C�g�̐F��ݒ�
	light->SetLightColor({ 1,1,1 });
	//3D�I�u�W�F�N�g�Ƀ��C�g��ݒ�
	Object3d::SetLight(light);

	//light->Update();
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	// �w�i�X�v���C�g�`��O����
	Sprite::BeforeDraw(cmdList);

	// �w�i�X�v���C�g�`��S
	sprite1->Draw();
	//sprite2->Draw();
	sprite3->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::AfterDraw();

	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();

	// 3D�I�u�W�F�N�g�̕`��
	Object3d::BeforeDraw(cmdList);
	//objSample->Draw();
	Object3d::AfterDraw();

	// �p�[�e�B�N���̕`��
	//particleMan->Draw(cmdList);

	// �O�i�X�v���C�g�`��O����
	Sprite::BeforeDraw(cmdList);

	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::AfterDraw();
}

void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++)
	{
		// X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;
		//�F�������_���ɕ��z
		XMFLOAT4 color;
		color.w = 1;
		color.x = (float)rand() / RAND_MAX * 1;
		color.y = (float)rand() / RAND_MAX * 1;
		color.z = (float)rand() / RAND_MAX * 1;

		// �ǉ�
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}