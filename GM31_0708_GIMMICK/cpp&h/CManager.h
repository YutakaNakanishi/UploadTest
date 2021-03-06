//=============================================================================
//
// CManagerクラス [CManager.h]
// Author : 中西 裕
//
// 最終更新日 4/15
//=============================================================================
#ifndef _CMANAGER_H_
#define _CMANAGER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
//=============================================================================
// マクロ定義
//=============================================================================
//=============================================================================
// クラス
//=============================================================================
class CRenderer;
class CPlayer;
class CManager
{
	public:
		//コンストラクタ
		CManager();
		//デストラクタ
		~CManager();
		//初期化処理
		HRESULT			Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
		//終了処理
		void			Uninit(void);
		//更新処理
		void			Update(void);
		//描画処理
		void			Draw(void);
		//デバイス取得
		static			CRenderer* GetRenderer(void){return m_pRenderer;};
		static			CPlayer*	GetPlayer();
	private:
		static			CRenderer* m_pRenderer;

};

#endif
