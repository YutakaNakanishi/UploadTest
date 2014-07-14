//=============================================================================
//
// CRenderクラス [CScene.h]
// Author : 中西 裕
//
// 最終更新日 4/21
//=============================================================================
#ifndef _CSCENE_H_
#define _CSCENE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_PRIORITY	(8)
typedef enum
		{
			OBJTYPE_NONE=0,
			OBJTYPE_2D,
			OBJTYPE_3D,
			OBJTYPE_X,
			OBJTYPE_BILLBOARD,
			OBJTYPE_SQHERE,
			OBJTYPE_DOME,
			OBJTYPE_CYLINDER,
			OBJTYPE_FIELD,
			OBJTYPE_WALL,
			OBJTYPE_ENEMY,
			OBJTYPE_PLAYER,
			OBJTYPE_EXPLOTION,
			OBJTYPE_BULLET,
			OBJTYPE_GIMICK,
			OBJTYPE_MAX
		}OBJTYPE;
//=============================================================================
// クラス
//=============================================================================
class CRenderer;
class CScene
{
	public:
		
		//引数コンストラクタ
		CScene(int nPriority=3,OBJTYPE Type=OBJTYPE_NONE);
		//デストラクタ
		virtual ~CScene();
		//初期化処理
		virtual HRESULT			Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)=0;
		//終了処理
		virtual void			Uninit()=0;
		//更新処理
		virtual void			Update()=0;
		//描画処理
		virtual void			Draw()=0;
		//頂点情報のセット
		virtual void			SetVertexPolygon()=0;
		//リンク追加処理
		void LinkList(void);						//自身をリンクにつなげる
		//リンクから外す処理
		void UnlinkList(void);						//リストから削除（外すというイメージでデータは削除しない）
		//座標の設定
		virtual void			SetPos(D3DXVECTOR3 Pos)=0;
		//座標の取得
		virtual D3DXVECTOR3		GetPos(void)=0;
		//回転の設定
		virtual void			SetRot(D3DXVECTOR3 Rot)=0;
		//回転の取得
		virtual D3DXVECTOR3		GetRot(void)=0;
		OBJTYPE GetObjType(){return m_ObjType;};
		virtual void SetPositionOld(D3DXVECTOR3 PosOld){};
		virtual D3DXVECTOR3 GetPositionOld(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual void SetRotationOld(D3DXVECTOR3 RotOld){};
		virtual D3DXVECTOR3 GetRotationOld(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual D3DXVECTOR3 GetVertexMin(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual D3DXVECTOR3 GetVertexMax(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		//全部更新
		static void UpdateAll(void);
		//全部描画
		static void DrawAll(void);
		//全部解放
		static void ReleaseAll(void);
		//解放
		void Release(void);


	private:
		//リスト構造用
		static CScene*	m_pTop[NUM_PRIORITY];		//リストの先頭アドレス
		static CScene*	m_pCur[NUM_PRIORITY];		//リストの終端アドレス
		CScene*			m_pPrev;					//前のオブジェクトへのポインタ(アドレス)
		CScene*			m_pNext;					//次のオブジェクトへのポインタ(アドレス)
		int				m_nPriority;				//描画優先順位
		bool			m_bDelete;					//オブジェクト削除フラグ
		OBJTYPE			m_ObjType;
};

#endif _CSCENE_H_