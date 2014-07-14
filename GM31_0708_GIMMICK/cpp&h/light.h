//=============================================================================
//
// ライト処理 [light.h]
// Author : yutaka nakanishi
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class CLight
{
	public:
		//コンストラクタ
		CLight();
		//デストラクタ
		~CLight();
		//初期化処理
		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);
		//終了処理
		void	Uninit(void);
		//更新処理
		void	Update(void);
	private:
		//ライト
		D3DLIGHT9				m_aLight[3];
		D3DXVECTOR3				m_aVecDir[3];

};

#endif
