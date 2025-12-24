#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"

// グローバル変数宣言
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	KamataEngine::Initialize(L"LC1A_28_フルカワ_ユウキ_AL2_05_03");

	// インスタンス取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	// ゲームシーンのインスタンス生成
	GameScene* gameScene = new GameScene();

	// ゲームシーンの初期化
	gameScene->Initialize();

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		//==========Update=========
		imguiManager->Begin();
		gameScene->Update();
		imguiManager->End();

		//==========Draw=========
		dxCommon->PreDraw();
		gameScene->Draw();
		AxisIndicator::GetInstance()->Draw();
		imguiManager->Draw();
		dxCommon->PostDraw();
	}

	KamataEngine::Finalize();
	delete gameScene;
	gameScene = nullptr;
	return 0;
}
