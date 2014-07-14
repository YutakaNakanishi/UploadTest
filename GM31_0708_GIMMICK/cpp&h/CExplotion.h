//=============================================================================
//
// CExplotionクラス [CExplotion.h]
// Author : 中西 裕
//
// 最終更新日 6/3
//=============================================================================
#ifndef _CEXPLOTION_H_
#define _CEXPLOTION_H_
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneBillboard.h"
#include "main.h"
//=============================================================================
//クラス
//=============================================================================
class CExplotion:public CSceneBillboard
{
	public:
		CExplotion(int nPriority,OBJTYPE Type);
		~CExplotion();
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,BYTE R,BYTE G,BYTE B,BYTE A,int Time,char * filename,OBJTYPE Type);
		void	Uninit(void);
		void	Update(void);
		void	Draw(void);
		static  CExplotion* Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,BYTE R,BYTE G,BYTE B,BYTE A,int Time,char * filename,OBJTYPE Type);
	private:
		COLORRGBA	m_Color;
		int			m_Time;
		int			m_TimeBlock;
		float			m_TexU;
		

};

#endif _CEXPLOTION_H_