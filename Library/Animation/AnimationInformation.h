/*
* @file		AnimationInformation.h
* @brief	�A�j���[�V�����̏��
* @author	Morita
* @date		2024/08/25
*/

#pragma once

#include "pch.h"

class AnimationInformation
{
public:

	//		�R���X�g���N�^
	AnimationInformation() :
		m_wireJudgement(false),
		m_landingTime(0.0f),
		m_fallJudgement(false)
	{};

	//		�f�X�g���N�^
	~AnimationInformation() {};

private:

	//		���C���[�t���[���ɂ��邩�ǂ���
	bool m_wireJudgement;

	//		���[���h���W
	std::vector<DirectX::SimpleMath::Matrix> m_world;

	//		�������Ă������ǂ���
	bool m_fallJudgement;

	//		���n����
	float m_landingTime;

public:

	/*
	*	���C���[�t���[���ɂ��邩�󂯎��
	*
	*	@reutrn true : �t���[���ɂ��� false : �t���[���ɂ��Ȃ�
	*/
	bool GetWireJudgement() { return m_wireJudgement; }

	/*
	*	���C���[�t���[���ɂ��邩��ݒ�
	*
	*	@param	(judgement)	true : �t���[���ɂ��� false : �t���[���ɂ��Ȃ�
	*/
	void SetWireJudgement(bool judgement) { m_wireJudgement = judgement; }

	/*
	*	���f���̃��[���h�s���ݒ肷��
	*
	*	@param	(world)	�s��
	*/
	void SetModelWorld(DirectX::SimpleMath::Matrix world) { m_world.push_back(world); }

	/*
	*	���f���̃��[���h���W���󂯎��
	*
	*	@return �s��
	*/
	DirectX::SimpleMath::Matrix* GetWorld(int index) { return &m_world[index]; }

	/*
	*	�������Ă��邩�󂯎��
	*
		@return true : �������Ă���@false : �������Ă��Ȃ�
	*/
	bool GetFallJudgement() { return m_fallJudgement; }

	/*
	*	�������Ă��邩�ݒ肷��
	*
	*	@param	(judgement)	true : �������Ă���@false : �������Ă��Ȃ�
	*/
	void SetFallJudgement(bool judgement) { m_fallJudgement = judgement; }

	/*
	*	���n���Ԃ��󂯎��
	*
	*	@return ����
	*/
	float GetLandingTime() { return m_landingTime; }

	/*
	*	���n���Ԃ�ݒ肷��
	*
	*	@param	(time)	����
	*/
	void SetLandingTime(float time) { m_landingTime = time; }
};