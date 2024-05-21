/*
* @file		CommonEnemy.cpp
* @brief	一般的な敵
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemy.h"

CommonEnemy::CommonEnemy()
	:
	m_state{ nullptr },
	m_rotation(0.0f),
	m_attackJudgement(false),
	m_timeSpeed(0.0f)
{
}

CommonEnemy::~CommonEnemy()
{
}

void CommonEnemy::Initialize()
{
	m_position = { 10.0f, 0.0f, 0.0f };

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_model = DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Enemy.cmo", *m_effect);

	//		待機状態の生成
	m_stay = std::make_unique<CommonEnemyStay>(this);

	//		警戒状態の生成
	m_vigilance = std::make_unique<CommonEnemyVigilance>(this);

	//		チャージ状態の生成
	m_charge = std::make_unique<CommonEnemyCharge>(this);

	//		攻撃状態の生成
	m_attack = std::make_unique<CommonEnemyAttack>(this);

	//		初期状態
	m_state = m_stay.get();

	//		状態の初期化
	m_state->Initialize();
}

void CommonEnemy::Update(const DirectX::SimpleMath::Vector3& playerPosition,
						 float timeSpeed)
{
	m_playerPosition = playerPosition;
	m_timeSpeed = timeSpeed;

	//		状態の更新処理
	m_state->Update();
}

void CommonEnemy::Render()
{
	//		状態の描画
	m_state->Render();
}

void CommonEnemy::Finalize()
{
}
