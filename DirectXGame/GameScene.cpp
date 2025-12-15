#include "GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//delete sprite_;
	delete model_;
	delete debugCamera_;
};


void GameScene::Initialize() {
	worldTransform_.Initialize();
	camera_.Initialize();
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向の表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	textureHandle_ = TextureManager::Load("images/mario.png");
	model_ = Model::Create();
	//sprite_ = Sprite::Create(textureHandle_, {100, 50});

	soundDataHandle_ = Audio::GetInstance()->LoadWave("sounds/se_hammer.wav");
	Audio::GetInstance()->PlayWave(soundDataHandle_);
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);
};

void GameScene::Update() {
	/*
	//スプライト座標取得
	Vector2 pos = sprite_->GetPosition();

	pos.x += 2.0f;
	pos.y += 1.0f;

	// スプライト座標設定
	sprite_->SetPosition(pos);
	*/

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}

	#ifdef _DEBUG
	ImGui::Begin("Debug1");
	//ImGui::Text("Furukawa Yuki %d.%d.%d", 2006, 05, 21);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();

	ImGui::ShowDemoWindow();
	#endif

	//デバッグカメラ
	debugCamera_->Update();
};

void GameScene::Draw() {
	/*
	Sprite::PreDraw();

	sprite_->Draw();

	Sprite::PostDraw();
	*/

	Model::PreDraw();

	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0, 1.0f});

	Model::PostDraw();

};