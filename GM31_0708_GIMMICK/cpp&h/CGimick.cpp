//=============================================================================
//
// CEnemyクラス [CGimick.cpp]
// Author : 中西 裕
//
// 最終更新日 5/20
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CGimick.h"
#include "CSceneX.h"
#include "CInputKeyboad.h"
#include "CPlayer.h"
#include "CManager.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
//=============================================================================
//引数コンストラクタ
//=============================================================================
CGimick::CGimick(int nPriority,OBJTYPE Type):CSceneX(nPriority,Type)
{
	m_vtxMax=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vtxMin=D3DXVECTOR3(0.0f,0.0f,0.0f);
}
//=============================================================================
//デストラクタ
//=============================================================================
CGimick::~CGimick()
{
}
//=============================================================================
//ギミック初期化
//=============================================================================
HRESULT CGimick::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CSceneX::Init(pRenderer,Pos,Rot,filename,Type);
	m_vtxMax=D3DXVECTOR3(10.0f,1.0f,10.0f);
	m_vtxMin=D3DXVECTOR3(-10.0f,-1.0f,-10.0f);

	return S_OK;
}

//=============================================================================
//エネミー解放
//=============================================================================
void CGimick::Uninit(void)
{
	CSceneX::Uninit();
}
//=============================================================================
//エネミー更新
//=============================================================================
void CGimick::Update(void)
{
	D3DXVECTOR3 Pos=GetPos();
	D3DXVECTOR3 Rot=GetRot();
	m_OldPos=Pos;
	m_OldRot=Rot;
	CPlayer *pPlayer=CManager::GetPlayer();
	D3DXVECTOR3 OffSet(0.0f,0.0f,0.0f);
	D3DXVECTOR3 P[4];
	D3DXVECTOR3 Target(0.0f,0.0f,0.0f);
	if(CInputKeyboard::GetPress(DIK_U))
	{
		Pos.z+=1;
	}
	if(CInputKeyboard::GetPress(DIK_J))
	{
		Pos.z-=1;
	}
	if(CInputKeyboard::GetPress(DIK_H))
	{
		Pos.x-=1;
	}								
	if(CInputKeyboard::GetPress(DIK_K))
	{
		Pos.x+=1;
	}								
	if(CInputKeyboard::GetPress(DIK_O))
	{
		Pos.y+=1;
	}								
	if(CInputKeyboard::GetPress(DIK_L))
	{
		Pos.y-=1;
	}								
	if(CInputKeyboard::GetPress(DIK_F))
	{
		Rot.y+=D3DX_PI*0.01f;
	}								
	if(CInputKeyboard::GetPress(DIK_G))
	{
		Rot.y-=D3DX_PI*0.01f;
	}

	CSceneX::Update();
	P[0]=D3DXVECTOR3(Pos.x+m_vtxMin.x,0.0f,Pos.z+m_vtxMax.z);
	P[1]=D3DXVECTOR3(Pos.x+m_vtxMax.x,0.0f,Pos.z+m_vtxMax.z);
	P[2]=D3DXVECTOR3(Pos.x+m_vtxMax.x,0.0f,Pos.z+m_vtxMin.z);
	P[3]=D3DXVECTOR3(Pos.x+m_vtxMin.x,0.0f,Pos.z+m_vtxMin.z);
	OffSet=pPlayer->GetPos()-Pos;
	Target=D3DXVECTOR3(Pos.x+(cos(-Rot.y)*OffSet.x)+(sin(-Rot.y)*OffSet.z),0.0f,Pos.z+(cos(-Rot.y)*OffSet.x)+(sin(-Rot.y)*OffSet.x));
	
	D3DXVECTOR3 VecLine=P[1]-P[0];
	D3DXVECTOR3 VecToTarget=pPlayer->GetPos()-P[0];
	if(VecToTarget.x*VecLine.z-VecToTarget.z*VecLine.x>=0)
	{
		VecLine=P[2]-P[1];
		VecToTarget=pPlayer->GetPos()-P[1];
		if(VecToTarget.x*VecLine.z-VecToTarget.z*VecLine.x>=0)
		{
			VecLine=P[3]-P[2];
			VecToTarget=pPlayer->GetPos()-P[2];
			if(VecToTarget.x*VecLine.z-VecToTarget.z*VecLine.x>=0)
			{
				VecLine=P[0]-P[3];
				VecToTarget=pPlayer->GetPos()-P[3];
				if(VecToTarget.x*VecLine.z-VecToTarget.z*VecLine.x>=0)
				{
					if((Pos.y+m_vtxMax.y)>pPlayer->GetPos().y &&
						(m_OldPos.y+m_vtxMax.y)<=pPlayer->GetPositionOld().y)
					{
						pPlayer->SetSpeedY(0.0f);
						pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x,Pos.y+m_vtxMax.y,pPlayer->GetPos().z));
					}
					else if((Pos.y+m_vtxMin.y)<pPlayer->GetPos().y+5 &&
						(m_OldPos.y+m_vtxMin.y)>=pPlayer->GetPositionOld().y+5)
					{
						pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x,Pos.y+m_vtxMin.y-5,pPlayer->GetPos().z));
						pPlayer->SetSpeedY(0.0f);
					}
				}
			}
		}
	}

	SetPos(Pos);
	SetRot(Rot);

}
//=============================================================================
//エネミー描画
//=============================================================================
void CGimick::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//エネミー生成
//=============================================================================
CGimick* CGimick::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CGimick* pGimick;
	pGimick=new CGimick(3,Type);
	pGimick->Init(pRenderer,Pos,Rot,filename,Type);
	return pGimick;

}