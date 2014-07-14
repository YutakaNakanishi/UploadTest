//=============================================================================
//
// ビルボード [CSceneBillboard.h]
// Author : yutaka nakanishi
//
// 2014/5/21
//=============================================================================
#ifndef _CSCENEBILLBOARD_H_
#define _CSCENEBILLBOARD_H_

#include "main.h"
#include "CScene.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class CRenderer;			//前方宣言
class CSceneBillboard:public CScene
{
	public:
		//コンストラクタ
		CSceneBillboard(int nPriority,OBJTYPE Type);
		//デストラクタ
		~CSceneBillboard();
		//初期化処理
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
		//終了処理
		void Uninit();
		//更新処理
		void Update();
		//描画処理
		void Draw();
		//頂点情報のセット
		void						SetVertexPolygon();
		//座標の設定
		void						SetPos(D3DXVECTOR3 Pos){m_Pos=Pos;};
		//座標の取得
		D3DXVECTOR3					GetPos(void){return m_Pos;};
		//回転の設定
		void						SetRot(D3DXVECTOR3 Rot){m_Rot=Rot;};
		//回転の取得
		D3DXVECTOR3					GetRot(void){return m_Rot;};
		//オブジェクト生成
		static CSceneBillboard*				Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
	protected:
		LPDIRECT3DTEXTURE9		m_pD3DTex;
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;
		LPDIRECT3DDEVICE9		m_pDevice;
		D3DXVECTOR3				m_Pos;
		D3DXVECTOR3				m_Rot;
		D3DXVECTOR3				m_Scl;
		D3DXMATRIX				m_MtxWorld;
		D3DXMATRIX				m_MtxScl,m_MtxRot,m_MtxTranslate;
		D3DXMATRIX				m_MtxView;
		float					m_fLength;		//中心から頂点までの距離
		float					m_fAngle;		//中心から頂点への角度
};
#endif _CSCENEBILLBOARD_H_