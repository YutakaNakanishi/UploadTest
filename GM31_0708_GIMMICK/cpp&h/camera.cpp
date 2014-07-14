//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : yutaka nakanishi
//
//=============================================================================
#include "camera.h"
#include "CInputKeyboad.h"
#include "CManager.h"
#include "CPlayer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_MOVE_X (1)
#define CAMERA_MOVE_Z (1)
#define CAMERA_MOVE_Y (1)
#define REVI_X			(0)
#define REVI_Y			(20)
#define REVI_Z			(-50)
#define REVI_HALF		(40)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXMATRIX CCamera::m_mtxView;
D3DXVECTOR3		CCamera::m_rotCamera;
D3DXVECTOR3		OldPos;
//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{}
//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{}

//=============================================================================
// カメラの初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_posCameraP=D3DXVECTOR3(0,7,-30);
	m_posCameraR=D3DXVECTOR3(0,0,0);
	m_vecCameraU=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rotCamera.y=0;
	m_rotCamera.x=-D3DX_PI/6.0f;
	m_vecDir=D3DXVECTOR3(0,0,0);
	m_vecDir=(m_posCameraR-m_posCameraP);
	m_fLength=(m_posCameraR.z-m_posCameraP.z);
	m_fAngle=atan2f(-m_vecDir.z,m_vecDir.x);
	m_fradian=REVI_HALF;
	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	CPlayer *pPlayer=CManager::GetPlayer();
	D3DXVECTOR3	Pos=pPlayer->GetPos();
	D3DXVECTOR3	Rot=pPlayer->GetRot();

	m_posCameraPDest.x=Pos.x-(REVI_HALF*cosf(m_rotCamera.x)*sinf(m_rotCamera.y));
	m_posCameraPDest.y=Pos.y-(REVI_HALF*sinf(m_rotCamera.x)+10);
	m_posCameraPDest.z=Pos.z-(REVI_HALF*cosf(m_rotCamera.x)*cosf(m_rotCamera.y));
	m_rotDestCamera.y=Rot.y+D3DX_PI;
	if(m_rotDestCamera.y>D3DX_PI)
	{
		m_rotDestCamera.y-=2*D3DX_PI;
	}
	if(m_rotDestCamera.y<-D3DX_PI)
	{
		m_rotDestCamera.y+=2*D3DX_PI;
	}
	m_posCameraRDest.x=Pos.x-(sin(Rot.y)*3);
	m_posCameraRDest.y=Pos.y;
	m_posCameraRDest.z=Pos.z-(cos(Rot.y)*3);

	if((OldPos.x-Pos.x)<0.001f && (OldPos.x-Pos.x)>-0.001f
		&& (OldPos.y-Pos.y)<0.001f && (OldPos.y-Pos.y)>-0.001f
		&& (OldPos.z-Pos.z)<0.001f && (OldPos.z-Pos.z)>-0.001f)
	{
		float a=m_rotDestCamera.y-m_rotCamera.y;
		if(a>D3DX_PI)
		{
			a-=2*D3DX_PI;
		}
		if(a<-D3DX_PI)
		{
			a+=2*D3DX_PI;
		}
		m_rotCamera.y+=a*0.2;
		if(m_rotCamera.y>D3DX_PI)
		{
			m_rotCamera.y-=2*D3DX_PI;
		}
		if(m_rotCamera.y<-D3DX_PI)
		{
			m_rotCamera.y+=2*D3DX_PI;
		}
		
	}
	
	m_posCameraP.x+=(m_posCameraPDest.x-m_posCameraP.x)*0.2;
	m_posCameraP.y+=(m_posCameraPDest.y-m_posCameraP.y)*0.2;
	m_posCameraP.z+=(m_posCameraPDest.z-m_posCameraP.z)*0.2;
					 					
	m_posCameraR.x+=(m_posCameraRDest.x-m_posCameraR.x)*0.3;
	m_posCameraR.y+=(m_posCameraRDest.y-m_posCameraR.y)*0.3;
	m_posCameraR.z+=(m_posCameraRDest.z-m_posCameraR.z)*0.3;


	OldPos=Pos;
	//if(CInputKeyboard::GetPress(DIK_W))
	//{
	//	m_vecDir=(m_posCameraR-m_posCameraP);
	//	m_fAngle=atan2f(-m_vecDir.x,m_vecDir.z);

	//	m_fAngle-=m_rotCamera.y;
	//	
	//	//視点
	//	m_posCameraP.x -= sinf(m_rotCamera.y+m_fAngle)*1.0f;
	//	m_posCameraP.z += cosf(m_rotCamera.y+m_fAngle)*1.0f;

	//	//注視点
	//	m_posCameraR.x = m_posCameraP.x-sinf(m_rotCamera.y+m_fAngle)*m_fLength;
	//	m_posCameraR.z = m_posCameraP.z+cosf(m_rotCamera.y+m_fAngle)*m_fLength;

	//	
	//}
	//if(CInputKeyboard::GetPress(DIK_S))
	//{
	//	m_vecDir=(m_posCameraR-m_posCameraP);
	//	m_fAngle=atan2f(-m_vecDir.x,m_vecDir.z);

	//	m_fAngle-=m_rotCamera.y;
	//	
	//	//視点
	//	m_posCameraP.x += sinf(m_rotCamera.y+m_fAngle)*1.0f;
	//	m_posCameraP.z -= cosf(m_rotCamera.y+m_fAngle)*1.0f;

	//	//注視点
	//	m_posCameraR.x = m_posCameraP.x-sinf(m_rotCamera.y+m_fAngle)*m_fLength;
	//	m_posCameraR.z = m_posCameraP.z+cosf(m_rotCamera.y+m_fAngle)*m_fLength;

	//	
	//}
	//if(CInputKeyboard::GetPress(DIK_D))
	//{
	//	m_vecDir=(m_posCameraR-m_posCameraP);
	//	m_fAngle=atan2f(-m_vecDir.x,m_vecDir.z);

	//	m_fAngle-=m_rotCamera.y;
	//	
	//	//視点
	//	m_posCameraP.x += cosf(m_rotCamera.y+m_fAngle)*1.0f;
	//	m_posCameraP.z += sinf(m_rotCamera.y+m_fAngle)*1.0f;

	//	//注視点
	//	m_posCameraR.x = m_posCameraP.x-sinf(m_rotCamera.y+m_fAngle)*m_fLength;
	//	m_posCameraR.z = m_posCameraP.z+cosf(m_rotCamera.y+m_fAngle)*m_fLength;

	//	
	//}

	//if(CInputKeyboard::GetPress(DIK_A))
	//{
	//	m_vecDir=(m_posCameraR-m_posCameraP);
	//	m_fAngle=atan2f(-m_vecDir.x,m_vecDir.z);

	//	m_fAngle-=m_rotCamera.y;
	//	
	//	//視点
	//	m_posCameraP.x -= cosf(m_rotCamera.y+m_fAngle)*1.0f;
	//	m_posCameraP.z -= sinf(m_rotCamera.y+m_fAngle)*1.0f;

	//	//注視点
	//	m_posCameraR.x = m_posCameraP.x-sinf(m_rotCamera.y+m_fAngle)*m_fLength;
	//	m_posCameraR.z = m_posCameraP.z+cosf(m_rotCamera.y+m_fAngle)*m_fLength;

	//}

	//if(CInputKeyboard::GetPress(DIK_Y))
	//{
	//	m_posCameraP.y++;
	//}
	//if(CInputKeyboard::GetPress(DIK_N))
	//{
	//	m_posCameraP.y--;
	//}
	////

	//左旋回
	if(CInputKeyboard::GetPress(DIK_Z))
	{
		//if(OldPos==Pos)
		//{
			m_fAngle=D3DX_PI;
			m_rotCamera.y=Rot.y+D3DX_PI;
			if(m_rotCamera.y>D3DX_PI)
			{
				m_rotCamera.y-=2*D3DX_PI;
			}
			if(m_rotCamera.y<-D3DX_PI)
			{
				m_rotCamera.y+=2*D3DX_PI;
			}
	
		//}


	}
	//右旋回
	if(CInputKeyboard::GetPress(DIK_C))
	{
		m_fAngle=D3DX_PI;
		m_rotCamera.y=m_rotCamera.y-D3DX_PI*0.01;
		if(m_rotCamera.y>D3DX_PI)
		{
			m_rotCamera.y-=2*D3DX_PI;
		}
		if(m_rotCamera.y<-D3DX_PI)
		{
			m_rotCamera.y+=2*D3DX_PI;
		}
	}

	////注視点の移動
	//if(GetKeyboardPress(DIK_Q))
	//{
	//	g_fAngle=0;
	//	g_rotCamera.y=g_rotCamera.y-D3DX_PI*0.005;
	//	if(g_rotCamera.y>D3DX_PI)
	//	{
	//		g_rotCamera.y+=2*D3DX_PI;
	//	}
	//	
	//	g_posCameraR.x= g_posCameraP.x+sinf(g_rotCamera.y+g_fAngle)*1.0f*g_fLength;
	//	g_posCameraR.z= g_posCameraP.z+cosf(g_rotCamera.y+g_fAngle)*1.0f*g_fLength;
	//}
	////注視点の移動
	//if(GetKeyboardPress(DIK_E))
	//{
	//	g_fAngle=0;
	//	g_rotCamera.y=g_rotCamera.y+D3DX_PI*0.005;
	//	if(g_rotCamera.y>D3DX_PI)
	//	{
	//		g_rotCamera.y+=2*D3DX_PI;
	//	}
	//	
	//	g_posCameraR.x= g_posCameraP.x+sinf(g_rotCamera.y+g_fAngle)*1.0f*g_fLength;
	//	g_posCameraR.z= g_posCameraP.z+cosf(g_rotCamera.y+g_fAngle)*1.0f*g_fLength;
	//}

	////注視点の上下
	//if(CInputKeyboard::GetPress(DIK_T))
	//{
	//	m_posCameraR.y++;
	//}
	//if(CInputKeyboard::GetPress(DIK_B))
	//{
	//	m_posCameraR.y--;
	//}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	//ビューマトリックス
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,
						&m_posCameraR,
						&m_vecCameraU);
	pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);
	//プロジェクションマトリックス
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DX_PI/(float)4,
								(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
								10.0f,
								10000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

}

//=============================================================================
// カメラの向きを取得
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rotCamera;
}

//=============================================================================
// カメラの方向
//=============================================================================
D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}
