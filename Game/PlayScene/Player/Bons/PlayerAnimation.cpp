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
	m_IState{},
	m_animationState(),
	m_fallJudgement(false),
	m_landingTime(0.0f)
{
}

PlayerAnimation::~PlayerAnimation()
{
}

void PlayerAnimation::Initialize(bool createHead)
{
	//		モデルの作製
	CreateModel(createHead);

	//		プレイヤーのボーンの作製
	m_playerBons = std::make_unique<PlayerBons>();

	//		プレイヤーボーンの初期化
	m_playerBons->Initialize(createHead);

	m_animationStateInformation.insert({ AnimationState::Stay, std::make_unique<StayAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Walk, std::make_unique<WalkAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::CrouchingStay, std::make_unique<CrouchingStayAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::CrouchingWalk, std::make_unique<CrouchingWalkAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Dash, std::make_unique<DashAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Jump, std::make_unique<JumpAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Sliding, std::make_unique<SlidingAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Start, std::make_unique<StartAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Wire, std::make_unique<WireJumpAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::WallWalk, std::make_unique<WallWalkAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::WallJump, std::make_unique<WallJumpAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Upright, std::make_unique<UprightAnimationState>(this) });
	m_animationStateInformation.insert({ AnimationState::Fall, std::make_unique<FallAnimationState>(this) });

	m_animationState = AnimationState::Start;

	//		初期アニメーションの設定
	m_IState = m_animationStateInformation[m_animationState].get();

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

void PlayerAnimation::Render(bool wireJudgement)
{
	for (int i = 0; i < m_playerModel.size(); ++i)
	{
		m_playerModel[i]->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			m_world[i], LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), wireJudgement);
	}
}

void PlayerAnimation::Finalize()
{
}

void PlayerAnimation::CreateModel(bool createHead)
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
	if (createHead) LoadModel(L"Resources/Models/Head.cmo", m_effect);
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

void PlayerAnimation::Landing(float height)
{
	m_landingTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

	m_landingTime = Library::Clamp(m_landingTime, 0.0f, 1.0f);

	float val = sinf(DirectX::XMConvertToRadians(Library::Lerp(0.0f, 180.0f, m_landingTime)));

	float lo = Library::Lerp(0.0f, -0.2f, val);

	(*m_playerBons->GetBonesInformation())[BonsType::Body].position.y += height - 1.8f + lo;

	if (m_landingTime >= 1.0f)
	{
 		m_fallJudgement = false;
	}
}

void PlayerAnimation::ChangeState(AnimationState State)
{
	if (m_animationState == State)
	{
		return;
	}

	//		現在の状態の終了処理
	m_IState->Finalize();

	//		もし落下アニメーションだった場合
	if (m_animationState == AnimationState::Fall)
	{
		m_landingTime = 0.0f;

		//		落下中状態にする
		m_fallJudgement = true;
	}

	m_animationState = State;

	//		状態の更新
	m_IState = m_animationStateInformation[m_animationState].get();

	//		新しい状態の初期化処理
	m_IState->Initialize();

}
