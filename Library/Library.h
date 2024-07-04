/*
* @file		Library.h
* @brief	ライブラリ
* @author	Morita
* @date		2024/01/01
*/

#pragma once

namespace Library
{
	/*
	*	クランプ処理
	* 
	*	@param	(val)	値
	*	@param	(min)	最小値
	*	@param	(max)	最大値
	*	@return 値
	*/
	template<typename T>
	inline T Clamp(T val, T min, T max)
	{
		if (val >= max) return max;
		else if (val <= min) return min;

		return val;
	}

	/*
	*	ラープ処理
	* 
	*	@param	(val1)	値１
	*	@param	(val2)	値２
	*	@param	(time)	時間
	*	@return 値
	*/
	inline float Lerp(const float& val1, const float& val2, const float& time)
	{
		return val1 + time * (val2 - val1);
	}

	/*
	*	最大値を求める
	* 
	*	@param	(val1)	値１
	*	@param	(val2)	値２
	*	@param	(val3)	値３
	*	@return		最大値
	*/
	inline DirectX::SimpleMath::Vector3 Max(const DirectX::SimpleMath::Vector3& val1,
											const DirectX::SimpleMath::Vector3& val2,
											const DirectX::SimpleMath::Vector3& val3)
	{
		return DirectX::SimpleMath::Vector3
		(std::max(val1.x, std::max(val2.x,val3.x)),
		 std::max(val1.y, std::max(val2.y,val3.y)),
		 std::max(val1.z, std::max(val2.z,val3.z))
		);
	}

	/*
	*	最小値を求める
	*
	*	@param	(val1)	値１
	*	@param	(val2)	値２
	*	@param	(val3)	値３
	*	@return		最小値
	*/
	inline DirectX::SimpleMath::Vector3 Min(const DirectX::SimpleMath::Vector3& val1,
		const DirectX::SimpleMath::Vector3& val2,
		const DirectX::SimpleMath::Vector3& val3)
	{
		return DirectX::SimpleMath::Vector3
		(std::min(val1.x, std::min(val2.x, val3.x)),
		 std::min(val1.y, std::min(val2.y, val3.y)),
		 std::min(val1.z, std::min(val2.z, val3.z))
		);
	}

}
