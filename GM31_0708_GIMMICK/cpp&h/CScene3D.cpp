//=============================================================================
//
// Scene3Dクラス [Scene3D.cpp]
// Author : 中西 裕
//
// 最終更新日 4/16
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CScene3D.h"
#include "CRenderer.h"
#include "camera.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define POLYGON_WIDTH	(10)
#define POLYGON_HEIGHT	(10)
#define ROTATION_SPEED	(0.01f)
//=============================================================================
//グローバル変数
//=============================================================================
D3DXVECTOR3 Vec[2][2];
D3DXVECTOR3 AnsVec[2];
D3DXVECTOR3 NorVec;
//=============================================================================
//コンストラクタ
//=============================================================================
CScene3D::CScene3D(int nPriority,OBJTYPE Type):CScene(nPriority,Type)
{
	m_pD3DTex=NULL;
	m_pD3DVtxBuff=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);		
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);		
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_fLength=0;
	m_fAngle=0;

}


//=============================================================================
//デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CScene3D::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	//まずは三角形のどこかを中心にしたベクトルを作る
	Vec[0][0]=D3DXVECTOR3(-POLYGON_WIDTH,2,-POLYGON_HEIGHT)-D3DXVECTOR3(-POLYGON_WIDTH,0,POLYGON_HEIGHT);
	Vec[0][1]=D3DXVECTOR3(POLYGON_WIDTH,2,POLYGON_HEIGHT)-D3DXVECTOR3(-POLYGON_WIDTH,0,POLYGON_HEIGHT);
	Vec[1][0]=D3DXVECTOR3(-POLYGON_WIDTH,2,-POLYGON_HEIGHT)-D3DXVECTOR3(POLYGON_WIDTH,0,-POLYGON_HEIGHT);
	Vec[1][1]=D3DXVECTOR3(POLYGON_WIDTH,2,POLYGON_HEIGHT)-D3DXVECTOR3(POLYGON_WIDTH,0,-POLYGON_HEIGHT);


	//次に外積で法線ベクトルを作る
	D3DXVec3Cross(&AnsVec[0],&Vec[0][0],&Vec[0][1]);
	D3DXVec3Cross(&AnsVec[1],&Vec[1][0],&Vec[1][1]);
	//長さが適当なのでノーマライズする
	D3DXVec3Normalize(&AnsVec[0],&AnsVec[0]);
	D3DXVec3Normalize(&AnsVec[1],&AnsVec[1]);
	NorVec=(AnsVec[0]+AnsVec[1])/2;
	//終わり
	m_Pos=Pos;
	m_Rot=Rot;
	m_pDevice=pRenderer->GetDevice();
	if(FAILED(m_pDevice->CreateVertexBuffer
			(sizeof(VERTEX_3D)*4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pD3DVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}
	SetVertexPolygon();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pDevice,filename,&m_pD3DTex);
	return S_OK;
}
//=============================================================================
//終了処理
//=============================================================================
void CScene3D::Uninit()
{
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	if(m_pD3DVtxBuff!=NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}

	Release();
}
//=============================================================================
//更新処理
//=============================================================================
void CScene3D::Update()
{
	//m_Rot.y+=D3DX_PI*ROTATION_SPEED;
	
}
//=============================================================================
//描画処理
//=============================================================================
void CScene3D::Draw()
{
	//m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//ワールドトランスフォーム
	D3DXMatrixIdentity(&m_MtxWorld);


	D3DXMatrixScaling(&m_MtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxScl);
	//回転
	D3DXMatrixRotationYawPitchRoll(&m_MtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxRot);
	D3DXMatrixTranslation(&m_MtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxTranslate);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);			// ワイヤーフレーム
	

	m_pDevice->SetTransform(D3DTS_WORLD,&m_MtxWorld);

	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pDevice->SetFVF(FVF_VERTEX_3D);
	m_pDevice->SetTexture(0,m_pD3DTex);
	
	//ポリゴン描画					描画方法		//ポリゴン数
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);


	//m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_FORCE_DWORD);			// ワイヤーフレーム

}


//=============================================================================
//頂点情報のセット
//=============================================================================
void	CScene3D::SetVertexPolygon(void)
{
	VERTEX_3D *pVtx;

	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//ポリゴン
	pVtx[0].vtx = D3DXVECTOR3(-POLYGON_WIDTH,0,POLYGON_HEIGHT);
	pVtx[1].vtx = D3DXVECTOR3(POLYGON_WIDTH,2,POLYGON_HEIGHT);
	pVtx[2].vtx = D3DXVECTOR3(-POLYGON_WIDTH,2,-POLYGON_HEIGHT);
	pVtx[3].vtx = D3DXVECTOR3(POLYGON_WIDTH,0,-POLYGON_HEIGHT);
	pVtx[0].nor = AnsVec[0];
	pVtx[1].nor = NorVec;
	pVtx[2].nor = NorVec;
	pVtx[3].nor = AnsVec[1];
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[0].tex = D3DXVECTOR2(0,0);
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);

	m_pD3DVtxBuff->Unlock();


}

//=============================================================================
//座標の設定
//=============================================================================
void	CScene3D::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos=Pos;
}
//=============================================================================
//座標の取得
//=============================================================================
D3DXVECTOR3	CScene3D::GetPos(void)
{
	return m_Pos;
}
//=============================================================================
//回転の設定
//=============================================================================
void	CScene3D::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot=Rot;
}
//=============================================================================
//回転の取得
//=============================================================================
D3DXVECTOR3	CScene3D::GetRot(void)
{
	return m_Rot;
}


//=============================================================================
//オブジェクト生成
//=============================================================================
CScene3D* CScene3D::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CScene3D* pScene3D=NULL;
	pScene3D=new CScene3D(3,Type);
	pScene3D->Init(pRenderer,Pos,Rot,filename,Type);
	return pScene3D;
}