/*
* @file		Player.cpp
* @brief	�v���C���[�̏���
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"
#include "Player.h"

Player::Player(GameManager* gameManager)
	:
	m_state{},
	m_collitionInformation(),
	m_gameManager(gameManager),
	m_cameraInformation(),
	m_playerState{},
	m_menuUseJudgement(false)
{
	Generation();
}

Player::~Player()
{
}

void Player::Initialize()
{
	//		���̏�����
	m_information->Initialize();

	//		�v���C���[�̃A�j���[�V�����̏�����
	m_playerAnimation->Initialize();

	//		�������
	m_playerState = PlayerState::Start;

	//		�������
	m_state = m_stateInformation[PlayerState::Start].get();

	//		��Ԃ�����������
	m_state->Initialize();

	//		�����Ă��鍂�������Ă���
	m_information->SetPlayerHeight(DirectX::SimpleMath::Vector3(0.0f, m_information->GetStandingHeight(), 0.0f));

	/*
	//		�v���C���[�̍U���̐���
	m_playerAttack = std::make_unique<PlayerAttack>(this);

	//		�v���C���[�̍U���̏�����
	m_playerAttack->Initialize();
	*/

	//m_information->SetPosition({ 0.0f, 500.0f, 0.0f });
}

void Player::Generation()
{
	//		�v���C���[�̏��𐶐�����
	m_information = std::make_unique<PlayerInformation>();

	//		�h���N���X�̐���
	m_stateInformation.insert({ PlayerState::Stay, std::make_unique<PlayerStay>(this) });
	m_stateInformation.insert({ PlayerState::Walk, std::make_unique<PlayerWalk>(this) });
	m_stateInformation.insert({ PlayerState::Jump, std::make_unique<PlayerJump>(this) });
	m_stateInformation.insert({ PlayerState::Crouching, std::make_unique<PlayerCrouching>(this) });
	m_stateInformation.insert({ PlayerState::Dash, std::make_unique<PlayerDash>(this) });
	m_stateInformation.insert({ PlayerState::WallWalk, std::make_unique<PlayerWallWalk>(this) });
	m_stateInformation.insert({ PlayerState::WallJump, std::make_unique<PlayerWallJump>(this) });
	m_stateInformation.insert({ PlayerState::Sliding, std::make_unique<PlayerSliding>(this) });
	m_stateInformation.insert({ PlayerState::Wire, std::make_unique<PlayerWire>(this) });
	m_stateInformation.insert({ PlayerState::Start, std::make_unique<PlayerStart>(this) });
	m_stateInformation.insert({ PlayerState::Death, std::make_unique<PlayerDeath>(this) });
	m_stateInformation.insert({ PlayerState::Goal, std::make_unique<PlayerGoal>(this) });
	m_stateInformation.insert({ PlayerState::Fall, std::make_unique<PlayerFall>(this) });

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_playerObject = DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		L"Resources/Models/Player.cmo", *m_effect);

	//		�v���C���[�̃A�j���[�V�����̐���
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Player);

	//		�����蔻��p�v���C���[�̏��𐶐�����
	m_playerInformationCollition = std::make_unique<PlayerInformationCollition>();

	//		�v���C���[�̋��ʏ���
	m_commonProcessing = std::make_unique<PlayerCommonProcessing>(this);
}

void Player::Update(PlayerCameraInformation* cameraInformation)
{
	m_cameraInformation = cameraInformation;

	//		�X�V����
	m_state->Update();

	m_playerInformationCollition->SetPlayerPosition(m_information->GetPlanPosition());
	m_playerInformationCollition->SetPlayerHeight(m_information->GetPlayerHeight());

	//		�_�b�V���̃N�[���^�C���̏���
	m_commonProcessing->DashCoolTime();

	m_information->SetWallWalkNormalize(m_playerInformationCollition->GetWallWalkNormalize());

	//		�f�o�b�N�p
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Enter))
	{
		m_gameManager->TrueFlag(GameManager::EndJudgement);
	}
}

void Player::MeshUpdate()
{
	//		�ړ�����
	m_state->Move();
}

void Player::AnimationUpdate()
{
	m_state->Animation();
}

void Player::Render(Shadow* hontai)
{
	DirectX::SimpleMath::Matrix world;

	//		�R���e�L�X�g
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->
		GetD3DDeviceContext();

	m_playerObject->Draw(
		context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		world, hontai->GetDepthView(),
		hontai->GetDpethProj(), 
		false,
		[&]
		{
			//context->VSSetShader(hontai->GetShadowVSShader().Get(), nullptr, 0);
			//context->PSSetShader(hontai->GetShadowPSShader().Get(), nullptr, 0);
		});

}

void Player::ModelRender()
{
	//		�{�[���̕`��
	m_playerAnimation->Render();
}

void Player::DebugRender()
{
	//		���W
	LibrarySingleton::GetInstance()->DebugFont(L"PositionX", m_information->GetPosition().x, 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionY", m_information->GetPosition().y, 0, 20);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionZ", m_information->GetPosition().z, 0, 40);

	//		���x
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_information->GetAcceleration().Length(), 0, 80);

	//		�d��
	LibrarySingleton::GetInstance()->DebugFont(L"gravity", m_information->GetGravity(), 0, 100);
}

void Player::Finalize()
{
}

void Player::DeathJudgement()
{
	//		�ȈՎ��S����
	if (m_information->GetPosition().y < -150.0f)
	{
		//		���S��Ԃɐ؂�ւ���
		ChangeState(PlayerState::Death);

		//		�����������Ă���
		//m_gameManager->SetFallDeadJudgement(true);
		m_gameManager->TrueFlag(GameManager::FallDead);
	}

	//		�I�u�W�F�N�g�ɓ����莀�S���Ă���ꍇ
	if (m_gameManager->FlagJudgement(GameManager::DamageObjectHit))
	{
		//		���S��Ԃɐ؂�ւ���
		ChangeState(PlayerState::Death);
	}
}

void Player::ChangeState(PlayerState state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_playerState == state) return;

	//		���݂̏�Ԃ̏I������������
	m_state->Finalize();

	//		��Ԃ�؂�ւ���
	m_playerState = state;

	//		��Ԃ̕ύX
	m_state = m_stateInformation[m_playerState].get();

	//		�V������Ԃ̏���������������
	m_state->Initialize();
}

void Player::ChangeWireState(int index)
{
	//		��Ԃ�J�ڂ���
	m_state->Finalize();

	//		���C���[��Ԃɂ���
	m_playerState = PlayerState::Wire;

	m_state = m_stateInformation[m_playerState].get();

	(*m_wireInformation)[index].m_actionJudgement = true;

	m_state->Initialize();
}
