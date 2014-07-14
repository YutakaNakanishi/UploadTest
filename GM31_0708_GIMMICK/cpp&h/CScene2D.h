//=============================================================================
//
// CRenderクラス [CScene2D.h]
// Author : 中西 裕
//
// 最終更新日 4/21
//=============================================================================
#ifndef _CSCENE2D_H_
#define _CSCENE2D_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "CScene.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// クラス
//=============================================================================
class CRenderer;
class CScene2D:public CScene
{
	public:

		//引数コンストラクタ
		CScene2D(int nPriority,OBJTYPE Type);
		//デストラクタ
		~CScene2D();
		//初期化処理
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		//終了処理
		void Uninit();
		//更新処理
		void Update();
		//描画処理
		void Draw();
		//頂点情報のセット
		void SetVertexPolygon();
		//座標の設定
		void						SetPos(D3DXVECTOR3 Pos);
		//座標の取得
		D3DXVECTOR3					GetPos(void);
		//回転の設定
		void						SetRot(D3DXVECTOR3 Rot);
		//回転の取得
		D3DXVECTOR3					GetRot(void);
		//オブジェクト生成
		static CScene2D*			Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
	private:
		LPDIRECT3DTEXTURE9			m_pD3DTex;		// Direct3D テクスチャポインター
		LPDIRECT3DVERTEXBUFFER9		m_pD3DVtxBuff;	// Direct3D 頂点バッファポインター
		LPDIRECT3DDEVICE9			m_pDevice;
		D3DXVECTOR3					m_Pos;			//ポリゴン座標
		D3DXVECTOR3					m_Rot;			//ポリゴン角度
		float						m_fLength;		//中心から頂点までの距離
		float						m_fAngle;		//中心から頂点への角度

};

#endif _SCENE2D_H_

