/*
* @file		TitleUIObserver.h
* @brief	タイトルUIオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitleUIObserver.h"

class TitleUIObserver
{
public:

	//		コンストラクタ
	TitleUIObserver();

	//		デストラクタ
	~TitleUIObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddObserver(ITitleUIObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeleteObserver(ITitleUIObserver* observer);

	/*
	*	下を選択した
	*
	*	@param	(processingTime)	処理時間
	*/
	void DownSelect(float processingTime);

	/*
	*	上を選択した
	*
	*	@param	(processingTime)	処理時間
	*/
	void UpSelect(float processingTime);

	//		全削除
	void Dalete();

private:

	//		オブザーバー
	std::vector<ITitleUIObserver*> m_observer;
};