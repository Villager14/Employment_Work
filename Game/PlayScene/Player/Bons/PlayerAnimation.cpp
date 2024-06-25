/*
* @file		PlayerAnimation.cpp
* @brief	�v���C���[�̃A�j���[�V����
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
	//		���f���̍쐻
	CreateModel();

	//		�v���C���[�̃{�[���̍쐻
	m_playerBons = std::make_unique<PlayerBons>();

	//		�v���C���[�{�[���̏�����
	m_playerBons->Initialize();

	//		�����A�j���[�V�����̐���
	m_walk = std::make_unique<WalkAnimationState>(this);
	//		�ҋ@�A�j���[�V�����̐���
	m_stay = std::make_unique<StayAnimationState>(this);
	//		���Ⴊ�ݑҋ@�A�j���[�V�����̐���
	m_crouchingStay = std::make_unique<CrouchingStayAnimationState>(this);
	//		���Ⴊ�ݕ����A�j���[�V�����̐���
	m_crouchingWalk = std::make_unique<CrouchingWalkAnimationState>(this);
	//		�_�b�V���A�j���[�V�����̐���
	m_dash = std::make_unique<DashAnimationState>(this);
	//		�W�����v�A�j���[�V�����̐���
	m_jump = std::make_unique<JumpAnimationState>(this);
	//		�X���C�f�B���O�A�j���[�V�����̐���
	m_sliding = std::make_unique<SlidingAnimationState>(this);
	//		�X�^�[�g�A�j���[�V�����̐���
	m_start = std::make_unique<StartAnimationState>(this);
	//		���C���[�W�����v�A�j���[�V�����̐���
	m_wireJump = std::make_unique<WireJumpAnimationState>(this);
	//		�Ǖ����A�j���[�V����
	m_wallWalk = std::make_unique<WallWalkAnimationState>(this);
	//		�ǃW�����v�A�j���[�V����
	m_wallJump = std::make_unique<WallJumpAnimationState>(this);
	//		�����A�j���[�V�����̐ݒ�
	m_IState = m_stay.get();

	//		����������
	m_IState->Initialize();
}

void PlayerAnimation::Execute(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	m_IState->Update(speed, position, angle, height, m_playerBons->GetBonesInformation());
}

void PlayerAnimation::Render()
{
	for (int i = 0; i < m_playerModel.size(); ++i)
	{
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(2.6f);

		m_playerBons->ParentProcess(&world, (*m_playerBons->GetBonesInformation())[i].type);

		m_playerModel[i]->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj());
	}
}

void PlayerAnimation::Finalize()
{
}

void PlayerAnimation::CreateModel()
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

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
	//LoadModel(L"Resources/Models/Head.cmo", m_effect);
}

void PlayerAnimation::LoadModel(const wchar_t* path, DirectX::EffectFactory* effect)
{
	m_playerModel.push_back(DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, *effect));
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

	//		���݂̏�Ԃ̏I������
	m_IState->Finalize();

	//		��Ԃ̍X�V
	m_IState = IState;

	//		�V������Ԃ̏���������
	m_IState->Initialize();
}

/*
void PlayerAnimation::AnimationValuReset()
{
	m_elapsedTime = 0.0f;
	m_animationTransitionTime = 1.0f;
	m_initialize = true;
}

void PlayerAnimation::Start(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{

	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll({DirectX::XMConvertToRadians(55.0f),
				DirectX::XMConvertToRadians(20.0f), 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll({DirectX::XMConvertToRadians(45.0f),
			DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll({DirectX::XMConvertToRadians(55.0f)
			, DirectX::XMConvertToRadians(-20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll( {DirectX::XMConvertToRadians(45.0f)
				, DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

	m_bonesInformation[BonsType::LArmUp].rotation = DirectX::SimpleMath::Quaternion::Lerp(LArmUp, DirectX::SimpleMath::Quaternion::Identity, m_animationTransitionTime);
	m_bonesInformation[BonsType::LArmDown].rotation = DirectX::SimpleMath::Quaternion::Lerp(LArmDown, DirectX::SimpleMath::Quaternion::Identity, m_animationTransitionTime);
	m_bonesInformation[BonsType::RArmUp].rotation = DirectX::SimpleMath::Quaternion::Lerp(RArmUp, DirectX::SimpleMath::Quaternion::Identity, m_animationTransitionTime);
	m_bonesInformation[BonsType::RArmDown].rotation = DirectX::SimpleMath::Quaternion::Lerp(RArmDown, DirectX::SimpleMath::Quaternion::Identity, m_animationTransitionTime);


	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::Walk(float speed, DirectX::SimpleMath::Vector3 position,
							DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * Library::Lerp(0.0f, 20.0f, speed / 70.0f);

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(65.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f});

	DirectX::SimpleMath::Quaternion  LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(65.0f),
				-cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });

	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::Stop(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(55.0f), DirectX::XMConvertToRadians(60.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp  =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(55.0f), DirectX::XMConvertToRadians(60.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });

	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::Jump(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 10.0f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(60.0f), DirectX::XMConvertToRadians(90.0f),
				m_elapsedTime), DirectX::XMConvertToRadians(50.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(60.0f), DirectX::XMConvertToRadians(90.0f),
				m_elapsedTime), DirectX::XMConvertToRadians(-50.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::Dash(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });


	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 6.0f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 2.0f);

	DirectX::SimpleMath::Quaternion LArmUp;
	DirectX::SimpleMath::Quaternion LArmDown;
	DirectX::SimpleMath::Quaternion RArmUp;
	DirectX::SimpleMath::Quaternion RArmDown;


	if (m_elapsedTime <= 1.0f)
	{
		LArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(-20.0f) , DirectX::XMConvertToRadians(0.0f) });

		LArmDown =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(10.0f), DirectX::XMConvertToRadians(70.0f) });

		RArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f });

		RArmDown =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-10.0f), DirectX::XMConvertToRadians(-60.0f) });
	}
	else
	{
		LArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ Library::Lerp(DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(90.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(-20.0f), DirectX::XMConvertToRadians(00.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-30.0f),m_elapsedTime - 1.0f) });

		LArmDown = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(10.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(70.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });


		RArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ Library::Lerp(DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(90.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(20.0f), DirectX::XMConvertToRadians(00.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(30.0f),m_elapsedTime - 1.0f) });


		RArmDown = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(-10.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(-60.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });
	}


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 7.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::CrouchingStop(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(55.0f), DirectX::XMConvertToRadians(60.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(55.0f), DirectX::XMConvertToRadians(60.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::CrouchingWalk(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * Library::Lerp(0.0f, 20.0f, speed / 70.0f);

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(65.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion  LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(65.0f),
				-cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::Sliding(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	if (m_initialize)
	{
		m_angle = -angle.x + 180.0f - 10.0f;
		m_initialize = false;
	}

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * Library::Lerp(0.0f, 20.0f, speed / 70.0f);

	DirectX::SimpleMath::Quaternion Body =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(m_angle),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion BodyDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(10.0f),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion LLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-45.0f),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion RLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-20.0f), DirectX::XMConvertToRadians(0.0f),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion RLegDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-90.0f), DirectX::XMConvertToRadians(-20.0f),
			DirectX::XMConvertToRadians(0.0f) });


	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(0.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(-90.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-45.0f),DirectX::XMConvertToRadians(0.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f) , 0.0f });


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationMovement(BonsType::LLegUp, &m_bonesInformation, LLegUp, m_bonesInformation[BonsType::LLegUp].rotation);
	AnimationMovement(BonsType::RLegUp, &m_bonesInformation, RLegUp, m_bonesInformation[BonsType::RLegUp].rotation);
	AnimationMovement(BonsType::RLegDown, &m_bonesInformation, RLegDown, m_bonesInformation[BonsType::RLegDown].rotation);
	AnimationMovement(BonsType::BodyDown, &m_bonesInformation, BodyDown, m_bonesInformation[BonsType::BodyDown].rotation);
	AnimationMovement(BonsType::Body, &m_bonesInformation, Body, m_bonesInformation[BonsType::Body].rotation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::WallWalk(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;

	DirectX::SimpleMath::Quaternion Body = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, -angle.x - DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(45.0f * angle.y)});


	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * Library::Lerp(0.0f, 20.0f, speed / 70.0f);


	DirectX::SimpleMath::Quaternion LLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(-10.0f), DirectX::XMConvertToRadians(30.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(0.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LLegDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(-30.0f), DirectX::XMConvertToRadians(-10.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(0.0f) , 0.0f });


	DirectX::SimpleMath::Quaternion RLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(-10.0f), DirectX::XMConvertToRadians(30.0f),
				-cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(0.0f) , 0.0f });


	DirectX::SimpleMath::Quaternion RLegDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(-30.0f), DirectX::XMConvertToRadians(-10.0f),
				-cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(0.0f) , 0.0f });




	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(65.0f),
				cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion  LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(50.0f), DirectX::XMConvertToRadians(65.0f),
				-cosf(m_elapsedTime) + 1.0f / 2.0f), DirectX::XMConvertToRadians(-20.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });

	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);

	AnimationMovement(BonsType::RLegUp, &m_bonesInformation, RLegUp, m_bonesInformation[BonsType::RLegUp].rotation);
	AnimationMovement(BonsType::LLegUp, &m_bonesInformation, LLegUp, m_bonesInformation[BonsType::LLegUp].rotation);
	AnimationMovement(BonsType::RLegDown, &m_bonesInformation, RLegDown, m_bonesInformation[BonsType::RLegDown].rotation);
	AnimationMovement(BonsType::LLegDown, &m_bonesInformation, LLegDown, m_bonesInformation[BonsType::LLegDown].rotation);

	AnimationMovement(BonsType::Body, &m_bonesInformation, Body, m_bonesInformation[BonsType::Body].rotation);


	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::WallJump(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 10.0f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	DirectX::SimpleMath::Quaternion Body =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(60.0f), DirectX::XMConvertToRadians(90.0f),
				m_elapsedTime), DirectX::XMConvertToRadians(50.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(60.0f), DirectX::XMConvertToRadians(90.0f),
				m_elapsedTime), DirectX::XMConvertToRadians(-50.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });


	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);

	AnimationMovement(BonsType::Body, &m_bonesInformation, Body, m_bonesInformation[BonsType::Body].rotation);


	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::WireJump(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height)
{
	std::vector<PlayerBonsInformation> m_bonesInformation = m_playerBons->GetBonesInformation();

	m_bonesInformation[BonsType::Body].position = position;
	m_bonesInformation[BonsType::Body].position.y += height - 1.8f;
	m_bonesInformation[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 6.0f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 2.0f);

	DirectX::SimpleMath::Quaternion LArmUp;
	DirectX::SimpleMath::Quaternion LArmDown;
	DirectX::SimpleMath::Quaternion RArmUp;
	DirectX::SimpleMath::Quaternion RArmDown;


	if (m_elapsedTime <= 1.0f)
	{
		LArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f) , DirectX::XMConvertToRadians(-90.0f) });

		LArmDown =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f) });

		RArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f) , DirectX::XMConvertToRadians(90.0f) });

		RArmDown =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f) });
	}
	else
	{
		LArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(angle.y) + DirectX::XMConvertToRadians(120.0f), m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-10.0f), m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(-90.0f), DirectX::XMConvertToRadians(0.0f), m_elapsedTime - 1.0f) });

		LArmDown = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-90.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });


		RArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(angle.y) + DirectX::XMConvertToRadians(120.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(10.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });


		RArmDown = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(90.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });
	}

	m_animationTransitionTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransitionTime = Library::Clamp(m_animationTransitionTime, 0.0f, 1.0f);

	AnimationMovement(BonsType::LArmUp, &m_bonesInformation, LArmUp, m_bonesInformation[BonsType::LArmUp].rotation);
	AnimationMovement(BonsType::LArmDown, &m_bonesInformation, LArmDown, m_bonesInformation[BonsType::LArmDown].rotation);
	AnimationMovement(BonsType::RArmUp, &m_bonesInformation, RArmUp, m_bonesInformation[BonsType::RArmUp].rotation);
	AnimationMovement(BonsType::RArmDown, &m_bonesInformation, RArmDown, m_bonesInformation[BonsType::RArmDown].rotation);
	AnimationLegInitialValue(&m_bonesInformation);

	m_playerBons->SetBonsInformation(m_bonesInformation);
}

void PlayerAnimation::AnimationMovement(BonsType type, std::vector<PlayerBonsInformation>* m_bonesInformation,
	DirectX::SimpleMath::Quaternion firstVal, DirectX::SimpleMath::Quaternion endVal)
{
	if (m_animationTransitionTime >= 0.0f)
	(*m_bonesInformation)[type].rotation = DirectX::SimpleMath::Quaternion::Lerp(firstVal, endVal, m_animationTransitionTime);
	else
	(*m_bonesInformation)[type].rotation = firstVal;
}

void PlayerAnimation::AnimationLegInitialValue(std::vector<PlayerBonsInformation>* m_bonesInformation)
{
	AnimationMovement(BonsType::LLegUp, m_bonesInformation,   DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::LLegUp].rotation);
	AnimationMovement(BonsType::LLegDown, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::LLegDown].rotation);
	AnimationMovement(BonsType::RLegDown, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity,   (*m_bonesInformation)[BonsType::RLegDown].rotation);
	AnimationMovement(BonsType::RLegUp, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::RLegUp].rotation);
	AnimationMovement(BonsType::BodyDown, m_bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*m_bonesInformation)[BonsType::BodyDown].rotation);
}
*/