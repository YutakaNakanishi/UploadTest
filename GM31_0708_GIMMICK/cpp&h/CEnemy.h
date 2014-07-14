//=============================================================================
//
// CEnemyクラス [CEnemy.h]
// Author : 中西 裕
//
// 最終更新日 5/20
//=============================================================================
#ifndef _CENEMY_H_
#define _CENEMY_H_
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneX.h"
//=============================================================================
//クラス
//=============================================================================
class CEnemy:public CSceneX
{
	public:
		CEnemy(int nPriority,OBJTYPE Type);
		~CEnemy();
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		void	Uninit(void);
		void	Update(void);
		void	Draw(void);
		static  CEnemy* Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
};

#endif _CENEMY_H_