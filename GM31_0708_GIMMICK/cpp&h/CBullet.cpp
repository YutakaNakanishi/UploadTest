//=============================================================================
//
// CBulletクラス [CBullet.cpp]
// Author : 中西 裕
//
// 最終更新日 5/27
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CBullet.h"
#include "CSceneBillboard.h"
#include "CExplotion.h"
#include "CManager.h"
//=============================================================================
//クラス
//=============================================================================
CBullet::CBullet(int nPriority,OBJTYPE Type):CSceneBillboard(nPriority,Type)
{

}
CBullet::~CBullet()
{

}
HRESULT CBullet::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,D3DXVECTOR3 Speed,char * filename,OBJTYPE Type)
{
	CSceneBillboard::Init(pRenderer,Pos,Rot,filename,Type);
	m_Speed=Speed;

	return S_OK;
}
void	CBullet::Uninit(void)
{
	CSceneBillboard::Uninit();
}
void	CBullet::Update(void)
{
	D3DXVECTOR3 Pos;
	Pos=GetPos();
	D3DXVECTOR2 wall[5];
	wall[0]=D3DXVECTOR2(-100.0f,100.0f);
	wall[1]=D3DXVECTOR2(100.0f,100.0f);
	wall[2]=D3DXVECTOR2(100.f,-100.0f);
	wall[3]=D3DXVECTOR2(-100.0f,-100.0f);
	wall[4]=D3DXVECTOR2(-100.0f,100.0f);
	CExplotion::Create(CManager::GetRenderer(),Pos,D3DXVECTOR3(0,0,0),255,10,10,255,100,"data/TEXTURE/shadow000.jpg",OBJTYPE_EXPLOTION);
	D3DXVECTOR2 Vecline[4],VecToTarget[4];
	Vecline[0]=wall[1]-wall[0];
	VecToTarget[0].x=Pos.x-wall[0].x;
	VecToTarget[0].y=Pos.z-wall[0].y;
	if(VecToTarget[0].x*Vecline[0].y-VecToTarget[0].y*Vecline[0].x<0)
	{
		CExplotion::Create(CManager::GetRenderer(),Pos,D3DXVECTOR3(0,0,0),255,10,10,255,100,"data/TEXTURE/explosion000.png",OBJTYPE_EXPLOTION);
		Uninit();
	}
	Vecline[1]=wall[2]-wall[1];
	VecToTarget[1].x=Pos.x-wall[1].x;
	VecToTarget[1].y=Pos.z-wall[1].y;
	if(VecToTarget[1].x*Vecline[1].y-VecToTarget[1].y*Vecline[1].x<0)
	{
		CExplotion::Create(CManager::GetRenderer(),Pos,D3DXVECTOR3(0,0,0),255,10,10,255,100,"data/TEXTURE/explosion000.png",OBJTYPE_EXPLOTION);
		Uninit();
	}
	Vecline[2]=wall[3]-wall[2];
	VecToTarget[2].x=Pos.x-wall[2].x;
	VecToTarget[2].y=Pos.z-wall[2].y;
	if(VecToTarget[2].x*Vecline[2].y-VecToTarget[2].y*Vecline[2].x<0)
	{
		CExplotion::Create(CManager::GetRenderer(),Pos,D3DXVECTOR3(0,0,0),255,10,10,255,100,"data/TEXTURE/explosion000.png",OBJTYPE_EXPLOTION);
		Uninit();
	}
	Vecline[3]=wall[4]-wall[3];
	VecToTarget[3].x=Pos.x-wall[3].x;
	VecToTarget[3].y=Pos.z-wall[3].y;
	if(VecToTarget[3].x*Vecline[3].y-VecToTarget[3].y*Vecline[3].x<0)
	{
		CExplotion::Create(CManager::GetRenderer(),Pos,D3DXVECTOR3(0,0,0),255,10,10,255,100,"data/TEXTURE/explosion000.png",OBJTYPE_EXPLOTION);
		Uninit();
	}

	

	Pos+=m_Speed;
	SetPos(Pos);
}
void	CBullet::Draw(void)
{
	CSceneBillboard::Draw();
}
CBullet* CBullet::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,D3DXVECTOR3 Speed,char * filename,OBJTYPE Type)
{
	CBullet* pBullet;
	pBullet=new CBullet(3,Type);
	pBullet->Init(pRenderer,Pos,Rot,Speed,filename,Type);
	return pBullet;
}