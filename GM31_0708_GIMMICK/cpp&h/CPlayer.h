//=============================================================================
//
// CPlayerクラス [CPlayer.h]
// Author : 中西 裕
//
// 最終更新日 5/20
//=============================================================================
#ifndef _CPLAYER_H_
#define _CPLAYER_H_
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneX.h"
//=============================================================================
//クラス
//=============================================================================
class CPlayer:public CSceneX
{
	public:
		CPlayer(int nPriority,OBJTYPE Type);
		~CPlayer();
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		void	Uninit(void);
		void	Update(void);
		void	Draw(void);
		static  CPlayer* Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		void SetPositionOld(D3DXVECTOR3 PosOld){m_OldPos=PosOld;};
		D3DXVECTOR3 GetPositionOld(){return m_OldPos;};
		void SetRotationOld(D3DXVECTOR3 RotOld){m_OldRot=RotOld;};
		D3DXVECTOR3 GetRotationOld(){return 	m_OldRot;};
		void SetSpeed(D3DXVECTOR3 Speed){m_Speed=Speed;};
		void SetSpeedY(float SpeedY){m_Speed.y=SpeedY;};
		CScene* GetScenelink(void){return m_pScenelink;}
		CScene* m_pScenelink;
	private:
		D3DXVECTOR3		m_RotDest;
		D3DXVECTOR3		m_Speed;
		D3DXVECTOR3		m_OldPos;
		D3DXVECTOR3		m_OldRot;

};

#endif _CPLAYER_H_