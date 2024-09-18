/*
* @file		AnimationManager.cpp
* @brief	�A�j���[�V�����}�l�[�W���[
* @author	Morita
* @date		2024/08/25
*/

#include "pch.h"

#include "AnimationManager.h"

AnimationManager::AnimationManager(CharactorType type)
	:
	m_charaType(type)
{
	//		�A�j���[�V�����̏��
	m_information = std::make_unique<AnimationInformation>();

	//		���ʏ���
	m_commonProcess = std::make_unique<AnimationCommonProcess>(this);

	bool createHead = false;

	if (m_charaType == CharactorType::Player)
	{
		m_animaInformation.insert({ AnimationState::Stay, std::make_unique<StayAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Walk, std::make_unique<WalkAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::CrouchingStay, std::make_unique<CrouchingStayAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::CrouchingWalk, std::make_unique<CrouchingWalkAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Dash, std::make_unique<DashAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Jump, std::make_unique<JumpAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Sliding, std::make_unique<SlidingAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Start, std::make_unique<StartAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Wire, std::make_unique<WireJumpAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::WallWalk, std::make_unique<WallWalkAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::WallJump, std::make_unique<WallJumpAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Upright, std::make_unique<UprightAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Fall, std::make_unique<FallAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Death, std::make_unique<DropDeadAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Attack, std::make_unique<AttackAnimationState>(this) });
	}
	else if (m_charaType == CharactorType::Result)
	{
		m_animaInformation.insert({ AnimationState::Upright, std::make_unique<UprightAnimationState>(this) });
		
		//		���C���[�t���[���ɂ���
		m_information->SetWireJudgement(true);

		createHead = true;
	}
	else if (m_charaType == CharactorType::CommonEnemy)
	{
		m_animaInformation.insert({ AnimationState::HandGunStayA, std::make_unique<HandGunStay>(this) });
		m_animaInformation.insert({ AnimationState::HandGunStyleA, std::make_unique<HandGunStyle>(this) });

		createHead = true;

		//		�e���g��
		m_information->SetGunModelJudgement(true);
	}

	//		�{�[���̏���
	m_bons = std::make_unique<ModelBones>(createHead, m_information->GetGunModelJudgement());

	//		���f���̍쐻
	CreateModel(createHead);
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::Initialize()
{
	//		�v���C���[
	if (m_charaType == CharactorType::Player)
	{
		m_animationState = AnimationState::Start;

		m_istate = m_animaInformation[m_animationState].get();
	}
	//		���U���g
	else if (m_charaType == CharactorType::Result)
	{
		m_animationState = AnimationState::Upright;

		m_istate = m_animaInformation[m_animationState].get();
	}
	//		�G�i�ʏ�j
	else if (m_charaType == CharactorType::CommonEnemy)
	{
		m_animationState = AnimationState::HandGunStayA;

		m_istate = m_animaInformation[m_animationState].get();
	}
}

void AnimationManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_model.size());
		 i < max; ++i)
	{
		m_model[i]->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			*m_information->GetWorld(i), LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), m_information->GetWireJudgement());
	}
}

void AnimationManager::Execute(float speed, DirectX::SimpleMath::Vector3 position,
							   DirectX::SimpleMath::Vector2 angle, float height)
{
	m_istate->Update(speed, position, angle, height, m_bons->GetBonesInformation());

	//		���[���h���W�̌v�Z
	for (int i = 0, max = static_cast<int>(m_model.size());
		i < max; ++i)
	{
		*m_information->GetWorld(i) = DirectX::SimpleMath::Matrix::CreateScale(2.6f);

		m_bons->ParentProcess(m_information->GetWorld(i), (*m_bons->GetBonesInformation())[i].type);
	}
}

void AnimationManager::CreateModel(bool createHead)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models/CharaTexture/Player");

	//		���f���̓ǂݍ���
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
	if (m_information->GetGunModelJudgement()) LoadModel(L"Resources/Models/HandGun.cmo", m_effect);
}

void AnimationManager::LoadModel(const wchar_t* path, DirectX::EffectFactory* effect)
{
	m_model.push_back(DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, *effect));

	//		���[���h���W
	m_information->SetModelWorld(DirectX::SimpleMath::Matrix::Identity);
}

void AnimationManager::ChangeState(AnimationState State)
{
	if (m_animationState == State)
	{
		return;
	}

	//		���݂̏�Ԃ̏I������
	m_istate->Finalize();

	//		���������A�j���[�V�����������ꍇ
	if (m_animationState == AnimationState::Fall)
	{
		m_information->SetLandingTime(0.0f);

		//		��������Ԃɂ���
		m_information->SetFallJudgement(true);
	}

	m_animationState = State;

	//		��Ԃ̍X�V
	m_istate = m_animaInformation[m_animationState].get();

	//		�V������Ԃ̏���������
	m_istate->Initialize();
}
