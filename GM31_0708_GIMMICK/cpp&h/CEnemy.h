//=============================================================================
//
// CEnemy�N���X [CEnemy.h]
// Author : ���� �T
//
// �ŏI�X�V�� 5/20
//=============================================================================
#ifndef _CENEMY_H_
#define _CENEMY_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CSceneX.h"
//=============================================================================
//�N���X
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