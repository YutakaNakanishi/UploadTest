//=============================================================================
//
// CBulletクラス [CBullet.h]
// Author : 中西 裕
//
// 最終更新日 5/27
//=============================================================================
#ifndef _CBULLET_H_
#define _CBULLET_H_
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneBillboard.h"
//=============================================================================
//クラス
//=============================================================================
class CBullet:public CSceneBillboard
{
	public:
		CBullet(int nPriority,OBJTYPE Type);
		~CBullet();
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot, D3DXVECTOR3 Speed,char * filename,OBJTYPE Type);
		void	Uninit(void);
		void	Update(void);
		void	Draw(void);
		static  CBullet* Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,D3DXVECTOR3 Speed,char * filename,OBJTYPE Type);
	private:	
		D3DXVECTOR3 m_Speed;
};

#endif _CBULLET_H_