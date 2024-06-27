/*
* @file		PlayerAnimation.cpp
* @brief	プレイヤーのアニメーション
* @author	Morita
* @date		2024/06/20
*/

#include "pch.h"

#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation()
	:
	m_IState{}
{
}

PlayerAnimation::~PlayerAnimation()
{
}

void PlayerAnimation::Initialize()
{
	//		モデルの作製
	CreateModel();

	//		プレイヤーのボーンの作製
	m_playerBons = std::make_unique<PlayerBons>();

	//		プレイヤーボーンの初期化
	m_playerBons->Initialize();

	//		歩くアニメーションの生成
	m_walk = std::make_unique<WalkAnimationState>(this);
	//		待機アニメーションの生成
	m_stay = std::make_unique<StayAnimationState>(this);
	//		しゃがみ待機アニメーションの生成
	m_crouchingStay = std::make_unique<CrouchingStayAnimationState>(this);
	//		しゃがみ歩きアニメーションの生成
	m_crouchingWalk = std::make_unique<CrouchingWalkAnimationState>(this);
	//		ダッシュアニメーションの生成
	m_dash = std::make_unique<DashAnimationState>(this);
	//		ジャンプアニメーションの生成
	m_jump = std::make_unique<JumpAnimationState>(this);
	//		スライディングアニメーションの生成
	m_sliding = std::make_unique<SlidingAnimationState>(this);
	//		スタートアニメーションの生成
	m_start = std::make_unique<StartAnimationState>(this);
	//		ワイヤージャンプアニメーションの生成
	m_wireJump = std::make_unique<WireJumpAnimationState>(this);
	//		壁歩きアニメーション
	m_wallWalk = std::make_unique<WallWalkAnimationState>(this);
	//		壁ジャンプアニメーション
	m_wallJump = std::make_unique<WallJumpAnimationState>(this);
	//		直立アニメーション
	m_upright = std::make_unique<UprightAnimationState>(this);
	//		初期アニメーションの設定
	m_IState = m_stay.get();

	//		初期化処理
	m_IState->Initialize();
}

void PlayerAnimation::Execute(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	m_IState->Update(speed, position, angle, height, m_playerBons->GetBonesInformation());

	//		ワールド座標の計算
	for (int i = 0; i < m_playerModel.size(); ++i)
	{
		m_world[i] = DirectX::SimpleMath::Matrix::CreateScale(2.6f);

		m_playerBons->ParentProcess(&m_world[i], (*m_playerBons->GetBonesInformation())[i].type);
	}
}

void PlayerAnimation::Render()
{
	for (int i = 0; i < m_playerModel.size(); ++i)
	{
		//DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(2.6f);

		//m_playerBons->ParentProcess(&world, (*m_playerBons->GetBonesInformation())[i].type);

		m_playerModel[i]->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			m_world[i], LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj());
	}
}

void PlayerAnimation::Finalize()
{
}

void PlayerAnimation::CreateModel()
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	LoadModel(L"Resources/Models/Body.cmo", m_effect);
	LoadModel(L"Resources/Models/BodyUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/LArmAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/LArmUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/LHand.cmo", m_effect);
	LoadModel(L"Resources/Models/RArmAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/RArmUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/RHand.cmo", m_effect);
	LoadModel(L"Resources/Models/LLeagAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/LLeagUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/LShoes.cmo", m_effect);
	LoadModel(L"Resources/Models/RLeagAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/RLeagUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/RShoes.cmo", m_effect);
	//LoadModel(L"Resources/Models/Head.cmo", m_effect);
}

void PlayerAnimation::LoadModel(const wchar_t* path, DirectX::EffectFactory* effect)
{
	m_playerModel.push_back(DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, *effect));

	//		ワールド座標
	m_world.push_back(DirectX::SimpleMath::Matrix::Identity);
}

void PlayerAnimation::AnimationMovement(BonsType type, std::vector<PlayerBonsInformation>* m_bonesInformation,
	DirectX::SimpleMath::Quaternion firstVal, DirectX::SimpleMath::Quaternion endVal, float transrationSpeed)
{
	if (transrationSpeed >= 0.0f)
		(*m_bonesInformation)[type].rotation = DirectX::SimpleMath::Quaternion::Lerp(firstVal, endVal, transrationSpeed);
	else
		(*m_bonesInformation)[type].rotation = firstVal;
}

void PlayerAnimation::AnimationLegInitialValue(std::vector<PlayerBonsInformation>* m_bonesInformation, float transrationSpeed)
{
	AnimationMovement(BonsType::LLegUp, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::LLegUp].rotation, transrationSpeed);
	AnimationMovement(BonsType::LLegDown, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::LLegDown].rotation, transrationSpeed);
	AnimationMovement(BonsType::RLegDown, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::RLegDown].rotation, transrationSpeed);
	AnimationMovement(BonsType::RLegUp, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::RLegUp].rotation, transrationSpeed);
	AnimationMovement(BonsType::BodyDown, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::BodyDown].rotation, transrationSpeed);
}

void PlayerAnimation::ChangeState(IPlayerAnimationState* IState)
{
	if (m_IState == IState)
	{
		return;
	}

	//		現在の状態の終了処理
	m_IState->Finalize();

	//		状態の更新
	m_IState = IState;

	//		新しい状態の初期化処理
	m_IState->Initialize();
}