//=============================================================================
//
// CPlayerクラス [CPlayer.cpp]
// Author : 中西 裕
//
// 最終更新日 5/27
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CPlayer.h"
#include "CSceneX.h"
#include "CInputKeyboad.h"
#include "camera.h"
#include "CBullet.h"
#include "CManager.h"
#include "CSceneField.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED (0.1f)
//プロトタイプ宣言
//BOOL HitCheckTri (D3DXVECTOR3 P1,D3DXVECTOR3 P2,D3DXVECTOR3 P3,D3DXVECTOR3 Pos);
/*float GetHeightPolygon(const D3DXVECTOR3& P0,
						const D3DXVECTOR3& P1,
						const D3DXVECTOR3& P2,
						const D3DXVECTOR3& Pos);*/
//=============================================================================
//グローバル変数
//=============================================================================
//D3DXVECTOR3 P[4];
//BOOL		HitFlag;
//D3DXVECTOR3 Vec1,Vec2;
//D3DXVECTOR3 NorVec[2];
//=============================================================================
//引数コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority,OBJTYPE Type):CSceneX(nPriority,Type)
{
	m_pScenelink=NULL;
}
//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
//エネミー初期化
//=============================================================================
HRESULT CPlayer::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CSceneX::Init(pRenderer,Pos,Rot,filename,Type);
	m_Speed=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//P[0]=D3DXVECTOR3(-10,0,10);
	//P[1]=D3DXVECTOR3(10,2,10);
	//P[2]=D3DXVECTOR3(-10,2,-10);
	//P[3]=D3DXVECTOR3(10,0,-10);
	return S_OK;
}

//=============================================================================
//エネミー解放
//=============================================================================
void CPlayer::Uninit(void)
{
	CSceneX::Uninit();
}
//=============================================================================
//エネミー更新
//=============================================================================
void CPlayer::Update(void)
{
	CScene* pSceneLinkOld=m_pScenelink;
	m_pScenelink=NULL;
	D3DXVECTOR3 Pos=GetPos();
	D3DXVECTOR3 Rot=GetRot();
	m_OldPos=Pos;
	m_OldRot=Rot;
	float fDiffRotY;
	if(CInputKeyboard::GetPress(DIK_D))
	{
		m_Speed.x+=sinf(CCamera::GetRot().y+(D3DX_PI/2.0f))*PLAYER_SPEED;
		m_Speed.z+=cosf(CCamera::GetRot().y+(D3DX_PI/2.0f))*PLAYER_SPEED;
		m_RotDest.y=(CCamera::GetRot().y-(D3DX_PI/2.0f));
	}
	if(CInputKeyboard::GetPress(DIK_A))
	{
		m_Speed.x+=sinf(CCamera::GetRot().y-(D3DX_PI/2.0f))*PLAYER_SPEED;
		m_Speed.z+=cosf(CCamera::GetRot().y-(D3DX_PI/2.0f))*PLAYER_SPEED;
		m_RotDest.y=(CCamera::GetRot().y+(D3DX_PI/2.0f));
	}
	//if(CInputKeyboard::GetPress(DIK_UP))
	//{
	//	Pos.y--;
	//}
	if(CInputKeyboard::GetPress(DIK_S))
	{
		m_Speed.x+=sinf(CCamera::GetRot().y+(D3DX_PI))*PLAYER_SPEED;
		m_Speed.z+=cosf(CCamera::GetRot().y+(D3DX_PI))*PLAYER_SPEED;
		m_RotDest.y=CCamera::GetRot().y;
	}
	if(CInputKeyboard::GetPress(DIK_W))
	{
		m_Speed.x+=sinf(CCamera::GetRot().y)*PLAYER_SPEED;
		m_Speed.z+=cosf(CCamera::GetRot().y)*PLAYER_SPEED;
		m_RotDest.y=(CCamera::GetRot().y+(D3DX_PI));
	}
		if(CInputKeyboard::GetPress(DIK_A) && CInputKeyboard::GetPress(DIK_S))
	{
		m_RotDest.y=CCamera::GetRot().y+D3DX_PI/4;
	}
	if(CInputKeyboard::GetPress(DIK_S) && CInputKeyboard::GetPress(DIK_D))
	{
		m_RotDest.y=CCamera::GetRot().y-D3DX_PI/4;
	}
	if(CInputKeyboard::GetPress(DIK_D) && CInputKeyboard::GetPress(DIK_W))
	{
		m_RotDest.y=CCamera::GetRot().y-D3DX_PI*((float)3/(float)4);
		
		
	}
	if(CInputKeyboard::GetPress(DIK_W) && CInputKeyboard::GetPress(DIK_A))
	{
		m_RotDest.y=CCamera::GetRot().y+D3DX_PI*((float)3/(float)4);
	
	
	}
	if(CInputKeyboard::GetTrig(DIK_UP))
	{
		m_Speed.y=2.0f;
	}
	Pos.x+=m_Speed.x;
	Pos.z+=m_Speed.z;
	m_Speed.x+=(0.0f-m_Speed.x)*0.1f;
	m_Speed.y+=(-20.0f-m_Speed.y)*0.01f;
	m_Speed.z+=(0.0f-m_Speed.z)*0.1f;
	Pos.y+=m_Speed.y;

		if(Pos.y<=CSceneField::GetHeight(Pos))
	{
		m_Speed.y=0.0f;
		Pos.y=CSceneField::GetHeight(Pos);
	}
	//m_Speed.y+=(-40.0f-m_Speed.y)*0.005;
	//Pos.y+=m_Speed.y;
	//目標角度へ向く
	fDiffRotY=m_RotDest.y-Rot.y;
	if(fDiffRotY>D3DX_PI)
	{
		fDiffRotY-=2*D3DX_PI;
	}
	if(fDiffRotY<-D3DX_PI)
	{
		fDiffRotY+=2*D3DX_PI;
	}
	Rot.y+=fDiffRotY*0.1f;
	if(Rot.y>D3DX_PI)
	{
		Rot.y-=2*D3DX_PI;
	}
	if(Rot.y<-D3DX_PI)
	{
		Rot.y+=2*D3DX_PI;
	}
	


	//if((g_OldposModel.x-g_posModel.x)>0.05f || (g_OldposModel.x-g_posModel.x)<-0.05f
	//	|| (g_OldposModel.y-g_posModel.y)>0.05f || (g_OldposModel.y-g_posModel.y)<-0.05f
	//	|| (g_OldposModel.z-g_posModel.z)>0.05f || (g_OldposModel.z-g_posModel.z)<-0.05f)
	//{
	//	g_OldposModel.y=g_posModel.y+5;
	//	SetEffect(255,10,10,255,g_OldposModel,D3DXVECTOR3(4.0f,4.0f,4.0f),40);
	//	SetEffect(10,10,255,255,g_OldposModel,D3DXVECTOR3(2.0f,2.0f,2.0f),40);
	//}
	if(CInputKeyboard::GetTrig(DIK_SPACE))
	{
		CBullet::Create(CManager::GetRenderer(),D3DXVECTOR3(Pos.x,Pos.y+3,Pos.z),D3DXVECTOR3(0,0,0),D3DXVECTOR3(-sin(Rot.y)*2,0.0f,-cos(Rot.y)*2),"data/TEXTURE/bullet000.png",OBJTYPE_BULLET);
	}
	//if(HitCheckTri(P[0],P[1],P[2],Pos))
	//{
	//	HitFlag=true;
	//	Pos.y=GetHeightPolygon(P[0],P[1],P[2],Pos);
	//	
	//}
	//if(!HitFlag)
	//{
	//	HitFlag=HitCheckTri(P[1],P[2],P[3],Pos);
	//	Pos.y=GetHeightPolygon(P[1],P[2],P[3],Pos);
	//}




	SetPos(Pos);
	SetRot(Rot);
//	HitFlag=false;
}
//=============================================================================
//エネミー描画
//=============================================================================
void CPlayer::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//エネミー生成
//=============================================================================
CPlayer* CPlayer::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CPlayer* pPlayer;
	pPlayer=new CPlayer(3,Type);
	pPlayer->Init(pRenderer,Pos,Rot,filename,Type);
	return pPlayer;

}





//float GetHeightPolygon(const D3DXVECTOR3& P0,
//						const D3DXVECTOR3& P1,
//						const D3DXVECTOR3& P2,
//						const D3DXVECTOR3& Pos)
//{
//	D3DXVECTOR3 Vec1,Vec2;
//	D3DXVECTOR3 NorVec;
//	Vec1=P0-P1;
//	Vec2=P2-P1;
//	D3DXVec3Cross(&NorVec,&Vec1,&Vec2);
//	D3DXVec3Normalize(&NorVec,&NorVec);
//	if(NorVec.y==0.0f)
//	{
//		return 0.0f;
//	}
//	return (P0.y-((NorVec.x*(Pos.x-P0.x))+(NorVec.z*(Pos.z-P0.z)))/NorVec.y);
//}
