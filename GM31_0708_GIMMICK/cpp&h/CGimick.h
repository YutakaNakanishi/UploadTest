//=============================================================================
//
// CEnemyクラス [CGimick.h]
// Author : 中西 裕
//
// 最終更新日 5/20
//=============================================================================
#ifndef _CGIMICK_H_
#define _CGIMICK_H_
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneX.h"
//=============================================================================
//クラス
//=============================================================================
class CGimick:public CSceneX
{
	public:
		CGimick(int nPriority,OBJTYPE Type);
		~CGimick();
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		void	Uninit(void);
		void	Update(void);
		void	Draw(void);
		static  CGimick* Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		D3DXVECTOR3 GetVertexMin(){return m_vtxMin;};
		D3DXVECTOR3 GetVertexMax(){return m_vtxMax;};
		void SetRotationOld(){D3DXVECTOR3 OldRot;};
		D3DXVECTOR3 GetRotationOld(){return m_OldRot;};
		void SetPositionOld(){D3DXVECTOR3 OldPos;};
		D3DXVECTOR3 GetPositionOld(){return m_OldPos;};
	private:
		D3DXVECTOR3 m_vtxMin;
		D3DXVECTOR3 m_vtxMax;
		D3DXVECTOR3	m_OldPos;
		D3DXVECTOR3	m_OldRot;

};

#endif _CGIMICK_H_