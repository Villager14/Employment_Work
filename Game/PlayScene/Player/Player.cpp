/*
* 
* @file		Player.cpp
* @brief	�v���C���[�̏���
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"
#include "Player.h"

#include <bitset>

Player::Player(GameManager* gameManager)
	:
	m_state{},
	m_collitionInformation(),
	m_gameManager(gameManager)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//		�v���C���[�̏��𐶐�����
	m_information = std::make_unique<PlayerInformation>();

	//		�v���C���[�ҋ@��Ԃ̐���
	m_playerStay = std::make_unique<PlayerStay>(this);

	//		�v���C���[������Ԃ̐���
	m_playerWalk = std::make_unique<PlayerWalk>(this);

	//		�v���C���[�̂��Ⴊ�ݏ�Ԃ̐���
	m_playerCrouching = std::make_unique<PlayerCrouching>(this);

	//		�v���C���[�̃W�����v��Ԃ𐶐�
	m_playerJump = std::make_unique<PlayerJump>(this);

	//		�v���C���[�̃X���C�f�B���O��Ԃ̐���
	m_playerSliding = std::make_unique<PlayerSliding>(this);

	//		�v���C���[�̃_�b�V����Ԃ𐶐�
	m_playerDash = std::make_unique<PlayerDash>(this);

	//		�v���C���[�̒ᑬ��Ԃ𐶐�
	m_playerSlowTime = std::make_unique<PlayerSlowTime>(this);

	//		�v���C���[�̕Ǖ�����Ԃ̐���
	m_playerWallWalk = std::make_unique<PlayerWallWalk>(this);

	//		�v���C���[�̃��C���[��Ԃ̐���
	m_playerWire = std::make_unique<PlayerWire>(this);

	//		�v���C���[�̕ǃW�����v��Ԃ𐶐�
	m_playerWallJump = std::make_unique<PlayerWallJump>(this);

	//		�v���C���[�̎��S��Ԃ𐶐�����
	m_playerDeath = std::make_unique<PlayerDeath>(this);

	//		�v���C���[�̃X�^�[�g��Ԃ𐶐�����
	m_playerStart = std::make_unique<PlayerStart>(this);

	//		�������
	m_state = m_playerStart.get();

	//		��Ԃ�����������
	m_state->Initialize();

	//		�����Ă��鍂�������Ă���
	m_information->SetPlayerHeight(DirectX::SimpleMath::Vector3(0.0f, m_information->GetStandingHeight(), 0.0f));

	//		�v���C���[�̍U���̐���
	m_playerAttack = std::make_unique<PlayerAttack>(this);

	//		�v���C���[�̍U���̏�����
	m_playerAttack->Initialize();

	//		�����蔻��p�v���C���[�̏��𐶐�����
	m_playerInformationCollition = std::make_unique<PlayerInformationCollition>();

	//		�����蔻��p�v���C���[�̏��𐶐�����
	//m_playerInformationCamera = std::make_unique<PlayerInformationCamera>();

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
}

void Player::Update(PlayerCameraInformation* cameraInformation)
{
	m_cameraInformation = cameraInformation;

	//		�X�V����
	m_state->Update();

	WireActionJudgement();

	m_playerInformationCollition->SetPlayerPosition(m_information->GetPlanPosition());
	m_playerInformationCollition->SetPlayerHeight(m_information->GetPlayerHeight());

	//		
	if (!m_information->GetDashJudgement())
	{
		//		�N�[���^�C��
		float coolTime = m_information->GetDashCoolTime();

		//		�o�ߎ���
		coolTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		//		��莞�Ԃ�������
		if (coolTime >= 2.0f)
		{
			m_information->SetDashJudgement(true);
			coolTime = 0.0f;
		}

		//		�N�[���^�C����ݒ肷��
		m_information->SetDashCoolTime(coolTime);
	}

	m_information->SetWallWalkNormalize(m_playerInformationCollition->GetWallWalkNormalize());
}

void Player::MeshUpdate()
{
	//		�ړ�����
	m_state->Move();
}

void Player::Render()
{
	//		�`�揈��
	m_state->Render();

	//		���W
	LibrarySingleton::GetInstance()->DebugFont(L"PositionX", m_information->GetPosition().x, 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionY", m_information->GetPosition().y, 0, 20);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionZ", m_information->GetPosition().z, 0, 40);

	//		���x
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_information->GetAcceleration().Length(), 0, 80);

	//		�d��
	LibrarySingleton::GetInstance()->DebugFont(L"gravity", m_information->GetGravity(), 0, 100);

	if (m_collitionInformation->GetWallHitVelocity().size() != 0)
	{
		//		�߂荞��
		LibrarySingleton::GetInstance()->DebugFont(L"wallX", m_collitionInformation->GetWallHitVelocity()[0].x, 0, 140);
		LibrarySingleton::GetInstance()->DebugFont(L"wallZ", m_collitionInformation->GetWallHitVelocity()[0].y, 0, 160);
	}
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
		ChangeState(m_playerDeath.get());
	}
}

void Player::ChangeState(IPlayer* state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_state->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		�V������Ԃ̏���������������
	m_state->Initialize();
}

DirectX::SimpleMath::Vector3 Player::Direction(bool* keyPressjudgement)
{
	std::bitset<4> directionbit;

	//		�L�[�{�[�hState�̎擾
	DirectX::Keyboard::State m_keyboard = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::W))
	{
		directionbit.set(0, 1);

		direction.z += 1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::S))
	{
		directionbit.set(1, 1);

		direction.z += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::D))
	{
		directionbit.set(2, 1);

		direction.x += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::A))
	{
		directionbit.set(3, 1);

		direction.x += 1.0f;
	}

	if (directionbit != 0)
	{
		//		�L�[��������Ă���
		*keyPressjudgement = true;
	}

	return direction;
}

DirectX::SimpleMath::Vector3 Player::MoveDirection
(const DirectX::SimpleMath::Vector3 direction)
{
	//		�J�����̌���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_information->GetCameraAngle().x));

	//		�ړ��������
	return DirectX::SimpleMath::Vector3::Transform(
		direction, matrixY.Invert());
}

void Player::Gravity(bool weekJudgement)
{
	float speed = 2.0f;

	//		�������Ԃ��󂯎��
	float fallTime = m_information->GetFallTime();

	if (weekJudgement)
	{
		speed = 1.0f;

		//		�d�͉����x
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;

		m_information->SetGravity(m_information->GetGravitationalAcceleration() * (fallTime * fallTime));

	}
	else
	{
		//		�d�͉����x
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed * (m_information->GetTimeSpeed()* m_information->GetTimeSpeed());

		m_information->SetGravity(m_information->GetGravitationalAcceleration() * (fallTime * fallTime));
	}

	//		�������Ԃ�ݒ肷��
	m_information->SetFallTime(fallTime);

	m_information->SetPlanPosition({ m_information->GetPlanPosition().x,
									 m_information->GetPlanPosition().y - m_information->GetGravity() * 
									LibrarySingleton::GetInstance()->GetElpsedTime()
									* m_information->GetTimeSpeed(),
									 m_information->GetPlanPosition().z});


}

bool Player::FloorMeshHitJudgement()
{
	//		���ɓ������Ă��邩
	if (m_collitionInformation->GetFloorMeshHitPoint().size() != 0)
	{
		//		���b�V����Y���W���󂯎��
		m_information->SetPlanPosition({ m_information->GetPlanPosition().x,
			m_collitionInformation->GetFloorMeshHitPoint()[0].y,
			m_information->GetPlanPosition().z });

		//		�������Ԃ��O�ɂ���
		m_information->SetFallTime(0.0f);

		//		�W�����v�ł����Ԃɂ���
		m_information->SetJumpJudgement(false);

		return true;
	}

	return false;
}

bool Player::WallMeshHitJudgement()
{
	if (m_collitionInformation->GetWallHitVelocity().size() > 0)
	{
		DirectX::SimpleMath::Vector3 planePosition = m_information->GetPlanPosition();

		planePosition.x = m_collitionInformation->GetWallHitVelocity()[0].x;
		planePosition.z = m_collitionInformation->GetWallHitVelocity()[0].y;

		m_information->SetPlanPosition(planePosition);

		return true;
	}

	return false;
}

void Player::PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed)
{
	DirectX::SimpleMath::Vector3 headPosition = m_information->GetPosition();

	float heightTime = m_information->GetHeightTime();

	//		��ȏ�Ȃ珈�������Ȃ�
	if (heightTime < 1.0f)
	{
		//		�J�ڑ��x
		heightTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;

		//		��ȏ�ɂȂ�Ȃ��悤�ɂ���
		heightTime = Library::Clamp(heightTime, 0.0f, 1.0f);

		//		easeOutQuart
		float move = 1.0f - pow(1.0f - heightTime, 4.0f);

		m_information->SetHeightTime(heightTime);

		//		���[�v�ŏ����̍������痧���̍�����
		headPosition.y = Library::Lerp(firstHeight, endHeight, move);
	}
	else
	{
		headPosition.y = endHeight;
	}

	if (m_information->GetHeadMove() > 0.0f)
	{
		float headMove = m_information->GetHeadMove();

		//		�ړ����x
		headMove -= m_information->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		�ړ��ʂ̐���
		headMove = Library::Clamp(headMove, 0.0f, m_information->GetHeadMoveMAX());

		//		���̈ړ��ʂ𑫂�
		headPosition.x += m_playerInformationCollition->GetWallWalkNormalize().x * headMove;
		headPosition.z += m_playerInformationCollition->GetWallWalkNormalize().z * headMove;

		m_information->SetHeadMove(headMove);
	}

	//		������ݒ肷��
	m_information->SetPlayerHeight(headPosition);
}

bool Player::WireActionJudgement()
{
	//		���C���[�̍��W���Ȃ��ꍇ���������Ȃ�
	if (m_information->GetWirePosition().size() == 0) return false;

	//		���C���[�̂������
	DirectX::SimpleMath::Vector3 wireDirection = m_information->GetWirePosition()[0] - m_information->GetPlayerHeight();

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 viewDirection = m_information->GetViewVelocity();

	//		���K��
	wireDirection.Normalize();
	viewDirection.Normalize();

	//		���ς����
	float dot = wireDirection.Dot(viewDirection);

	//		���C���[�̕����������Ă�����
	if (dot < 0.9f) return false;

	//		�}�E�X�g���b�J�[�̒l���󂯎��
	DirectX::Mouse::ButtonStateTracker* mouse = LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		�}�E�X�������ꂽ�ꍇ
	if (mouse->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		�ړ����C���[�̍��W��ݒ肷��
		DirectX::SimpleMath::Vector3 wireMovePosition = m_information->GetWirePosition()[0];

		wireMovePosition.y -= 12.0f;

		//		�ړ����C���[���W��ݒ肷��
		m_information->SetWireMovePosition(wireMovePosition);

		//		��Ԃ�J�ڂ���i�j
		ChangeState(m_playerWire.get());
		
		return true;
	}

	return false;
}

void Player::WallWalkJudgement()
{
	//		�ǂɓ������Ă���ꍇ
	if (m_collitionInformation->GetMeshWallNormalize().size() == 1)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_information->GetAcceleration();

		acceleation.Normalize();

		float dot = m_collitionInformation->GetMeshWallNormalize()[0].Dot(acceleation);

		//		�v���C���[�����̊p�x�������Ă���ꍇ����������
		if (dot <= -0.1f && dot >= -0.9f)
		{
			//		�@����������
			m_playerInformationCollition->SetWallWalkNormalize(m_collitionInformation->GetMeshWallNormalize()[0]);

			//		��Ԃ�؂�ւ���(�Ǖ������)
			ChangeState(m_playerWallWalk.get());

			return;
		}
	}
}
