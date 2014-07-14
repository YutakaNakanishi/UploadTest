//=============================================================================
//
// ビルボード [CSceneBillboard.cpp]
// Author : yutaka nakanishi
//
// 2014/5/21
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneBillboard.h"
#include "CRenderer.h"
#include "camera.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BILLBOARD_WIDTH		(2)
#define BILLBOARD_HEIGHT	(2)

//コンストラクタ
CSceneBillboard::CSceneBillboard(int nPriority,OBJTYPE Type):CScene(nPriority,Type)
{
	m_pD3DTex=NULL;
	m_pD3DVtxBuff=NULL;
	m_pDevice=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);;
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);;
	m_fLength=0;		//中心から頂点まで
	m_fAngle=0;		//中心から頂点への
}

//デストラクタ
CSceneBillboard::~CSceneBillboard()
{

}

//初期化処理
HRESULT CSceneBillboard::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char *filename,OBJTYPE Type)
{
	m_pDevice=pRenderer->GetDevice();
	//ビルボード初期化
	m_Pos=Pos;
	m_Rot=Rot;

	//頂点情報の設定
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

//終了処理
void CSceneBillboard::Uninit()
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

//更新処理
void CSceneBillboard::Update()
{

}

//描画処理
void CSceneBillboard::Draw()
{
	m_MtxView=CCamera::GetMtxView();
	m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DXMatrixIdentity(&m_MtxWorld);
	
	D3DXMatrixInverse(&m_MtxWorld,NULL,&m_MtxView);
	m_MtxWorld._41=0.0f;
	m_MtxWorld._42=0.0f;
	m_MtxWorld._43=0.0f;

	D3DXMatrixScaling(&m_MtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxScl);
	D3DXMatrixTranslation(&m_MtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxTranslate);

	

	m_pDevice->SetTransform(D3DTS_WORLD,&m_MtxWorld);

	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pDevice->SetFVF(FVF_VERTEX_3D);
	m_pDevice->SetTexture(0,m_pD3DTex);
	
	//ポリゴン描画					描画方法		//ポリゴン数
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);


}

//頂点情報のセット
void CSceneBillboard::SetVertexPolygon()
{
	VERTEX_3D *pVtx;

	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	//ポリゴン
	pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_WIDTH,BILLBOARD_HEIGHT,0);
	pVtx[1].vtx = D3DXVECTOR3(BILLBOARD_WIDTH,BILLBOARD_HEIGHT,0);
	pVtx[2].vtx = D3DXVECTOR3(-BILLBOARD_WIDTH,-BILLBOARD_HEIGHT,0);
	pVtx[3].vtx = D3DXVECTOR3(BILLBOARD_WIDTH,-BILLBOARD_HEIGHT,0);
	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
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

CSceneBillboard* CSceneBillboard::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char *filename,OBJTYPE Type)
{
	CSceneBillboard* pSceneBillboard=NULL;
	pSceneBillboard=new CSceneBillboard(3,Type);
	pSceneBillboard->Init(pRenderer,Pos,Rot,filename,Type);
	return pSceneBillboard;
}