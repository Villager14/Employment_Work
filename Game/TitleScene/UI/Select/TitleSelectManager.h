/*
* @file		TitleSelectManager.h
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "ITitleSelect.h"

#include "State/SelectPlayState.h"

#include "Game/PlayScene/UIManager/UIRender.h"

class SelectPlayState;

class TitleSelectManager
{
public:

	enum UIType
	{
		Play,
		End,
		Setting
	};


public:

	//		�R���X�g���N�^
	TitleSelectManager();

	//		�f�X�g���N�^
	~TitleSelectManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(ITitleSelect* state);

	/*
	*	���S�����ւ̏���
	* 
	*	@bool (direction)	true : ��ֈړ����� false : ���S�ֈړ�����
	*/
	void CentreUP(bool direction, float time, UIType type);

	/*
	*	���S���牺�ւ̏���
	* 
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void CenterUnder(bool direction, float time, UIType type);

	/*
	*	���S���牺�ւ̏���
	*
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void UPUnder(bool direction, float time, UIType type);


	/*
	*	UI��ǉ�����
	* 
	*	@param	(path)		�e�N�X�`���t�@�C���p�X
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*/
	void AddRenderUI(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size);

private:

	//		�I��
	ITitleSelect* m_state;

	//		�v���C���
	std::unique_ptr<SelectPlayState> m_selectPlayState;

public:

	/*
	*	�v���C�I����Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	SelectPlayState* GetSelectPlayState() { return m_selectPlayState.get(); }

private:

	//		���S�n�_
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		���n�_
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		��n�_
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

private:

	//		UI�}�l�[�W���[
	std::vector<std::unique_ptr<UIRender>> m_uiRender;

	//		UI�̍��W
	std::vector<DirectX::SimpleMath::Vector2> m_uiPosition;

	//		UI�̃T�C�Y
	std::vector<DirectX::SimpleMath::Vector2> m_uiSize;

public:

	/*
	*	���W��ݒ肷��
	* 
	*	@parma	(position)	���W
	*	@param	(type)		UI�̃^�C�v
	*/
	void SetUIPosition(const DirectX::SimpleMath::Vector2& position, UIType type) { m_uiPosition[type] = position; }

	/*
	*	UI���W��ݒ肷��
	* 
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetUIPosition() { return m_uiPosition; }

	/*
	*	�T�C�Y��ݒ肷��
	*
	*	@parma	(size)	�T�C�Y
	*	@param	(type)	UI�̃^�C�v
	*/
	void SetUISize(const DirectX::SimpleMath::Vector2& size, UIType type) { m_uiSize[type] = size; }

	/*
	*	UI�T�C�Y��ݒ肷��
	*
	*	@return �T�C�Y
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetUISize() { return m_uiSize; }

	/*
	*	���S�|�C���g���󂯎��
	* 
	*	@return ���S�|�C���g
	*/
	const DirectX::SimpleMath::Vector2& GetCenterPoint() { return CENTER_POINT; }

	/*
	*	���|�C���g���󂯎��
	*
	*	@return ���|�C���g
	*/
	const DirectX::SimpleMath::Vector2& GetUnderPoint() { return UNDER_POINT; }

	/*
	*	��|�C���g���󂯎��
	*
	*	@return ��|�C���g
	*/
	const DirectX::SimpleMath::Vector2& GetUPPoint() { return UP_POINT; }


};