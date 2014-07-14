//=============================================================================
//
// メッシュ地面の処理 [CSceneField.h]
// Author : yutaka nakanishi
//
// 2014/5/21
//=============================================================================
#ifndef _CSENEFIELD_H_
#define _CSCNEFIELD_H_
//=============================================================================
//インクルード
//=============================================================================
#include "CScene.h"
#include "main.h"

//=============================================================================
//クラス
//=============================================================================
class CRenderer;		//前方宣言
class CSceneField:public CScene
{
	public:
		//引数コンストラクタ
		CSceneField(int nPriority,OBJTYPE Type);
		//デストラクタ
		~CSceneField();
		//純粋仮想関数用
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
		//メッシュ初期化
		HRESULT Init(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);

		//終了処理
		void Uninit();
		//更新処理
		void Update();
		//描画処理
		void Draw();
		//頂点情報のセット
		void SetVertexPolygon();//純粋仮想関数用

		void SetVertexPolygon(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
		//座標の設定
		void						SetPos(D3DXVECTOR3 Pos){m_Pos=Pos;};
		//座標の取得
		D3DXVECTOR3					GetPos(void){return m_Pos;};
		//回転の設定
		void						SetRot(D3DXVECTOR3 Rot){m_Rot=Rot;};
		//回転の取得
		D3DXVECTOR3					GetRot(void){return m_Rot;};
		//オブジェクト生成
		static CSceneField*			Create(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
		//高さ取得処理
		static float				GetHeight(D3DXVECTOR3 Pos);

private:
		LPDIRECT3DTEXTURE9			m_pD3DTex;		// Direct3D テクスチャポインター
		static LPDIRECT3DVERTEXBUFFER9		m_pD3DVtxBuff;	// Direct3D 頂点バッファポインター
		LPDIRECT3DDEVICE9			m_pDevice;
		D3DXVECTOR3					m_Pos;			//ポリゴン座標
		D3DXVECTOR3					m_Rot;			//ポリゴン角度
		D3DXVECTOR3					m_Scl;
		D3DXMATRIX					m_MtxWorld;
		D3DXMATRIX					m_MtxScl,m_MtxRot,m_MtxTranslate;
		D3DXMATRIX					m_MtxView;
		float						m_fLength;		//中心から頂点までの距離
		float						m_fAngle;		//中心から頂点への角度
		//インデックスバッフア
		LPDIRECT3DINDEXBUFFER9		m_pD3DIndexBuff;
		int							m_nNumVertexIndex;				// 頂点の総インデックス数
		static int					m_nNumBlockX, m_nNumBlockZ;		// ブロック数
		int							m_nNumVertex;					// 総頂点数
		int							m_nNumPolygon;					// 総ポリゴン数
		static float				m_fSizeBlockX, m_fSizeBlockZ;	// ブロックサイズ
		
};


#endif _CSCENEFIELD_H_