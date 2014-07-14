//=============================================================================
//
// CRenderクラス [CRenderer.h]
// Author : 中西 裕
//
// 最終更新日 4/15
//=============================================================================
#ifndef _CRENDERER_H_
#define _CRENDERER_H_

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
class CScene;
class CCamera;
class CRenderer
{
	public:
		//コンストラクタ
		CRenderer();
		//デストラクタ
		~CRenderer();
		//初期化処理
		HRESULT						Init(HWND hWnd,BOOL bWindow);
		//終了処理
		void						Uninit(void);
		//更新処理
		void						Update(void);
		//描画処理
		void						Draw(void);
		//登録用関数
		void						AddScene(CScene *pScene);
		//デバイス取得
		LPDIRECT3DDEVICE9			GetDevice(void);
	private:
		//デバックのために
		void DrawFPS(void);

		//以下メンバー変数
		LPDIRECT3D9					m_pD3D;			// Direct3D オブジェクトポインター
		LPDIRECT3DDEVICE9			m_pD3DDevice;	// Direct3D デバイスポインター
		CScene						*m_apScenes[SCENE_MAX];
		int							m_nCountScene;
};

#endif

