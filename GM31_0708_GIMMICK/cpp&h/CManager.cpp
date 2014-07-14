//=============================================================================
//
// CManager処理 [CManager.cpp]
// Author : 中西 裕
//
// 最終更新日 5/7
//=============================================================================
//=============================================================================
//インクルード
//=============================================================================
#include "CManager.h"
#include "CRenderer.h"
#include "CScene.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CSceneX.h"
#include "CSceneBillboard.h"
#include "CSceneField.h"
#include "CSceneWall.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "camera.h"
#include "light.h"
#include "CInputKeyboad.h"
#include "CMeshCylinder.h"
#include "CMeshDome.h"
#include "CGimick.h"
//=============================================================================
//マクロ定義
//=============================================================================
//=============================================================================
//グローバル変数
//=============================================================================
CRenderer *CManager::m_pRenderer;
CCamera			*g_pCamera;
CLight			*g_pLight;
CInputKeyboard	*g_Keyboard;
static CPlayer			*g_pPlayer;


//コンストラクタ
CManager::CManager()
{	
	m_pRenderer=new CRenderer();
	g_pCamera=new CCamera();
	g_pLight=new CLight();
	g_Keyboard=new CInputKeyboard();
}
//デストラクタ
CManager::~CManager()
{
	delete g_Keyboard;
	delete g_pLight;
	delete g_pCamera;
	delete m_pRenderer;

}
//初期化処理
HRESULT		CManager::Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{

	m_pRenderer->Init(hWnd,bWindow);
	//キーボード初期化
	g_Keyboard->Init(hInstance,hWnd);
	//ライトの初期化
	g_pLight->Init(m_pRenderer->GetDevice());
	//カメラの初期化
	g_pCamera->Init();
	
	//	CScene3D::Create(m_pRenderer,D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
//	CEnemy::Create(m_pRenderer,D3DXVECTOR3(0,60,70),D3DXVECTOR3(-D3DX_PI/10,0,0),"data/MODEL/BigSpaceShip.x");

	CEnemy::Create(m_pRenderer,D3DXVECTOR3(30,10,-20),D3DXVECTOR3(D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(30,20,-30),D3DXVECTOR3(D3DX_PI/8,0,0),"data/MODEL/SpaceShip_bule.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-50,10,50),D3DXVECTOR3(D3DX_PI/10,D3DX_PI+(D3DX_PI/4),0),"data/MODEL/SpaceShip.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-30,20,70),D3DXVECTOR3(D3DX_PI/10,D3DX_PI+(D3DX_PI/4),0),"data/MODEL/SpaceShip_bule.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-20,25,15),D3DXVECTOR3(D3DX_PI/6,D3DX_PI-(D3DX_PI/4),0),"data/MODEL/SpaceShip.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-35,40,35),D3DXVECTOR3(D3DX_PI/6,D3DX_PI-(D3DX_PI/4),0),"data/MODEL/SpaceShip_bule.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(0,10,30),D3DXVECTOR3(D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x",OBJTYPE_ENEMY);
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(00,20,20),D3DXVECTOR3(D3DX_PI/8,0,0),"data/MODEL/SpaceShip_bule.x",OBJTYPE_ENEMY);
	/*CEnemy::Create(m_pRenderer,D3DXVECTOR3(20,10,20),D3DXVECTOR3(-D3DX_PI/10,0,0),"data/MODEL/SpaceShip.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-20,10,20),D3DXVECTOR3(-D3DX_PI/10,0,0),"data/MODEL/SpaceShip.x");


	CEnemy::Create(m_pRenderer,D3DXVECTOR3(0,15,30),D3DXVECTOR3(-D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(10,15,25),D3DXVECTOR3(-D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-10,15,25),D3DXVECTOR3(-D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(20,15,20),D3DXVECTOR3(-D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-20,15,20),D3DXVECTOR3(-D3DX_PI/8,0,0),"data/MODEL/SpaceShip.x");*/


	g_pPlayer=CPlayer::Create(m_pRenderer,D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),"data/MODEL/robot.x",OBJTYPE_PLAYER);

	CEnemy::Create(m_pRenderer,D3DXVECTOR3(0,3,-20),D3DXVECTOR3(0,D3DX_PI,0),"data/MODEL/robot_bule.x",OBJTYPE_ENEMY);
	//CEnemy::Create(m_pRenderer,D3DXVECTOR3(0,60,-70),D3DXVECTOR3(-D3DX_PI/10,D3DX_PI,0),"data/MODEL/BigSpaceShip_bule.x");


	/*CEnemy::Create(m_pRenderer,D3DXVECTOR3(20,10,-20),D3DXVECTOR3(-D3DX_PI/10,D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-20,10,-20),D3DXVECTOR3(-D3DX_PI/10,-D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");


	CEnemy::Create(m_pRenderer,D3DXVECTOR3(0,15,-30),D3DXVECTOR3(-D3DX_PI/8,D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(10,15,-25),D3DXVECTOR3(-D3DX_PI/8,D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-10,15,-25),D3DXVECTOR3(-D3DX_PI/8,D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(20,15,-20),D3DXVECTOR3(-D3DX_PI/8,D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");
	CEnemy::Create(m_pRenderer,D3DXVECTOR3(-20,15,-20),D3DXVECTOR3(-D3DX_PI/8,D3DX_PI,0),"data/MODEL/SpaceShip_bule.x");*/






	CSceneX::Create(m_pRenderer,D3DXVECTOR3(20	,-5	,-70),D3DXVECTOR3(-D3DX_PI/10,0,D3DX_PI/8),"data/MODEL/building.x",OBJTYPE_X);
	CSceneX::Create(m_pRenderer,D3DXVECTOR3(70	,-5	,50),D3DXVECTOR3(0,0,-D3DX_PI/10),"data/MODEL/building.x",OBJTYPE_X);
	CSceneX::Create(m_pRenderer,D3DXVECTOR3(-30	,-5	,-50),D3DXVECTOR3(0,0,D3DX_PI/7),"data/MODEL/building.x",OBJTYPE_X);
	CSceneX::Create(m_pRenderer,D3DXVECTOR3(0	,-5	,70),D3DXVECTOR3(-D3DX_PI/10,0,-D3DX_PI/10),"data/MODEL/building.x",OBJTYPE_X);
	CSceneX::Create(m_pRenderer,D3DXVECTOR3(-70	,-5	,30),D3DXVECTOR3(0,0,-D3DX_PI/5),"data/MODEL/building.x",OBJTYPE_X);
	CSceneX::Create(m_pRenderer,D3DXVECTOR3(40	,-5	,10),D3DXVECTOR3(0,0,-D3DX_PI/5),"data/MODEL/building.x",OBJTYPE_X);
	CGimick::Create(m_pRenderer,D3DXVECTOR3(20	,0	,0),D3DXVECTOR3(0,0,0),"data/MODEL/gimick.x",OBJTYPE_GIMICK);
	CSceneField::Create(m_pRenderer,100,100,5,5,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0.0f,0.0f,0.0f),"data/texture/field000.jpg",OBJTYPE_FIELD);
	CMeshDome::Create(m_pRenderer,100,100,100,100,D3DXVECTOR3(0,-100,0),D3DXVECTOR3(0.0f,0.0f,0.0f),450.0f,"data/texture/stars.jpg",OBJTYPE_DOME);
	CMeshCylinder::Create(m_pRenderer,300,40,5,5,D3DXVECTOR3(0,160,0),D3DXVECTOR3(-D3DX_PI/2,0.0f,0.0f),400.0f,"data/texture/darkbuilding.png",OBJTYPE_CYLINDER);

	CSceneWall::Create(m_pRenderer,2,2,100,10,D3DXVECTOR3(100,0,0),D3DXVECTOR3(0.0f,D3DX_PI/2.0f,0.0f),"data/texture/wall000.jpg",OBJTYPE_WALL);
	CSceneWall::Create(m_pRenderer,2,2,100,10,D3DXVECTOR3(-100,0,0),D3DXVECTOR3(0.0f,-D3DX_PI/2.0f,0.0f),"data/texture/wall000.jpg",OBJTYPE_WALL);
	CSceneWall::Create(m_pRenderer,2,2,100,10,D3DXVECTOR3(0,0,100),D3DXVECTOR3(0.0f,0.0f,0.0f),"data/texture/wall000.jpg",OBJTYPE_WALL);
	CSceneWall::Create(m_pRenderer,2,2,100,10,D3DXVECTOR3(0,0,-100),D3DXVECTOR3(0.0f,D3DX_PI,0.0f),"data/texture/wall000.jpg",OBJTYPE_WALL);
//	CSceneX::Create(m_pRenderer,D3DXVECTOR3(-5.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
//	CPlayer::Create(m_pRenderer,D3DXVECTOR3(0.0f,10.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI,0.0f));
//	CSceneBillboard::Create(m_pRenderer,D3DXVECTOR3(-5.0f,3.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));



	return S_OK;
}
//終了処理
void						CManager::Uninit(void)
{
	//キーボード初期化
	g_Keyboard->Uninit();
	//ライトの終了
	g_pLight->Uninit();
	//カメラの終了
	g_pCamera->Uninit();
	m_pRenderer->Uninit();
	CScene::ReleaseAll();

}
//更新処理
void						CManager::Update(void)
{
	g_Keyboard->Update();
	m_pRenderer->Update();
	g_pCamera->Update();
	

}
//描画処理
void						CManager::Draw(void)
{	
	//カメラのセット
	g_pCamera->SetCamera(m_pRenderer->GetDevice());
	m_pRenderer->Draw();

}

CPlayer*	CManager::GetPlayer()
{
	return g_pPlayer;
}