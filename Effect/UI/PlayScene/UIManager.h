/*
* @file		UIManager.h
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/StandardShader.h"

#include "Game/PlayScene/Player/Observer/IPObserver.h"
#include "Game/PlayScene/Player/Observer/SpeedObserver/IPSpeedObserver.h"

class ClockManager;
class CoolTime;
class GameOverManager;
class GameClearManager;
class SpeedLine;
class GameStart;
class CountDown;

class UIManager : public IPObserver, public IPSpeedObserver
{
public:
	//		�R���X�g���N�^
	UIManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~UIManager();

	//		��������
	void Initialize();

	//		����
	void Generation();

	//		�X�V����
	void Update();

	//		�I������
	void Finalize();

	void FrontRender();

	void BackRender();

	//		UI�e�N�X�`���̍쐻
	void CreateStandardUITexture();

	
	/*
	*	�_�b�V���N�[���^�C��
	* 
	*	@param	(coolTime)	�N�[���^�C��
	*/
	void DashCoolTime(float coolTime) override;

	/*
	*	���݃v���C���[�̑��x
	* 
	*	@param	(speed)	���x
	*/
	void NowSpeed(float speed) override;

public:

	enum UIType
	{
		ClockBackGround,		//		���v�̔w�i
		ClockColon,				//		���v�̃R����
		CloolTimeBackGround,	//		�N�[���^�C���̔w�i
		GameOver,				//		�Q�[���I�[�o�[
		GameOverContinue,		//		�Q�[���I�[�o�[�̃R���e�B�j���[
		NextInduction,			//		���̏�Ԃ̗U��
		ScreenRay,				//		�X�N���[���̃��C
		GameClearBarUnder,		//		�Q�[���N���A�̃o�[
		GameClearBarUp,			//		�Q�[���N���A�̃o�[		
		GameClearBackGround,	//		�Q�[���N���A�̔w�i
		GameStartTimeLimit,		//		�Q�[���X�^�[�g�^�C�����~�b�g
		GameStartTimeTen		//		�Q�[���X�^�[�g�^�C�����~�b�g�̓_
	}; 

public:

	//		���v�w�i���W
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_GROUND_POSITION = { 480.0f, 200.0f };

	//		���v���Ԕw�i���W
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_TIME_GROUND_POSITION = { 539.0f, 0.0f };

	//		���̏�ԗU�����W
	const DirectX::SimpleMath::Vector2 NEXT_INDCCTION = { 0.0f, 200.0f };

	//		���b�Z�[�W�o�[��̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_UP = { 0.0f, 13.0f };

	//		���b�Z�[�W�o�[���̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_DOWN = { 0.0f, -13.0f };

	//		���v�w�i�e�N�X�`���p�X
	const wchar_t* CLOCK_BACK_GROUND_PAHT = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		�N���b�N�w�i�e�N�X�`���p�X
	const wchar_t* CLOCK_COLON_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockColon.png";

	//		�N�[���^�C���w�i�e�N�X�`���p�X
	const wchar_t* COOL_TIME_BACK_TEXTURE_PATH = L"Resources/Texture/UI/CoolTime/CoolTimeBack.png";

	//		�Q�[���I�[�o�[�e�N�X�`���p�X
	const wchar_t* GAME_OVER_TEXTURE_PATH = L"Resources/Texture/UI/GameOver/GameOver.png";

	//		�R���e�j���[�e�N�X�`���p�X
	const wchar_t* CONTINUE_TEXTURE_PATH = L"Resources/Texture/UI/GameOver/Continue.png";

	//		�{�^���e�N�X�`���p�X
	const wchar_t* BUTTON_TEXTURE_PATH = L"Resources/Texture/UI/GameOver/button.png";

	//		�X�N���[�����C�e�N�X�`���p�X
	const wchar_t* SCREEN_RAY_TEXTURE_PATH = L"Resources/Texture/UI/ScreenRay/ScreenRay.png";

	//		���b�Z�[�W�o�[�e�N�X�`���p�X
	const wchar_t* MESSAGE_BAR_TEXTURE_PATH = L"Resources/Texture/UI/GameClear/messegeBer.png";

	//		�^�C�����~�b�g�e�N�X�`���p�X
	const wchar_t* TIME_LIMIT_TEXTURE_PATH = L"Resources/Texture/UI/GameStart/TimeLimit.png";

	//		�_�e�N�X�`���p�X
	const wchar_t* TEN_TEXTURE_PATH = L"Resources/Texture/UI/GameStart/Ten.png";


	//		���b�Z�[�W�w�i�̃t�@�C���p�X
	const wchar_t* MESSAGE_BACK_FILE_PATH = L"Resources/Texture/UI/GameClear/messegeBack.png";

private:
	//		���v�̔w�i
	std::unique_ptr<ClockManager> m_clockManager;

	//		�N�[���^�C��
	std::unique_ptr<CoolTime> m_coolTime;

	//		�J�E���g�_�E��
	std::unique_ptr<CountDown> m_countDonw;
		
	//		�Q�[���I�[�o�[
	std::unique_ptr<GameOverManager> m_gameOver;

	//		�X�s�[�h���C��
	std::unique_ptr<SpeedLine> m_speedLine;

	//		�Q�[���X�^�[�g
	std::unique_ptr<GameStart> m_gameStart;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		�Q�[���N���A�}�l�[�W���[
	std::unique_ptr<GameClearManager> m_clearManager;

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	�X�^���_�[�h�V�F�[�_�[���󂯎��
	* 
	*	@return �X�^���_�[�h�V�F�[�_�[���󂯎��
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	GameManager* GetGameManager() { return m_gameManager; }
};