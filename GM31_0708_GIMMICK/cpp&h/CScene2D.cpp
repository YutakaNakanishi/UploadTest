//=============================================================================
//
// Scene2Dクラス [Scene2D.cpp]
// Author : 中西 裕
//
// 最終更新日 4/16
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CScene2D.h"
#include "CRenderer.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define POLYGON_WIDTH	(100)
#define POLYGON_HEIGHT	(200)
#define ROTATION_SPEED	(0.1f)
//=============================================================================
//グローバル変数
//=============================================================================

//=============================================================================
//引数コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority,OBJTYPE Type):CScene(nPriority,Type)
{

	m_pD3DTex=NULL;
	m_pD3DVtxBuff=NULL;
	m_Pos=D3DXVECTOR3(0,0,0);
	m_Rot=D3DXVECTOR3(0,0,0);
	m_fLength=0;
	m_fAngle=0;

}


//=============================================================================
//デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CScene2D::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	m_Pos=Pos;
	m_Rot=Rot;
	m_fLength=sqrtf(POLYGON_WIDTH*POLYGON_WIDTH+POLYGON_HEIGHT*POLYGON_HEIGHT);
	m_fAngle=atan2f(POLYGON_WIDTH,POLYGON_HEIGHT);
	m_pDevice=pRenderer->GetDevice();
	if(FAILED(m_pDevice->CreateVertexBuffer
			(sizeof(VERTEX_2D)*4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pD3DVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}
	SetVertexPolygon();
		//テクスチャ読み込み
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),filename,&m_pD3DTex);
	return S_OK;
}
//=============================================================================
//終了処理
//=============================================================================
void CScene2D::Uninit()
{
	
	if(m_pD3DTex)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	if(m_pD3DVtxBuff)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}
	Release();
}
//=============================================================================
//更新処理
//=============================================================================
void CScene2D::Update()
{
	m_Rot.z+=D3DX_PI*ROTATION_SPEED;
	
	SetVertexPolygon();
}
//=============================================================================
//描画処理
//=============================================================================
void CScene2D::Draw()
{
		m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_2D));
		m_pDevice->SetFVF(FVF_VERTEX_2D);
		m_pDevice->SetTexture(0,m_pD3DTex);
	
		//ポリゴン描画					描画方法		//ポリゴン数
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}


//=============================================================================
//頂点情報のセット
//=============================================================================
void	CScene2D::SetVertexPolygon(void)
{
	VERTEX_2D *pVtx;

	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//ポリゴン
	pVtx[0].vtx = D3DXVECTOR3(m_Pos.x-sinf(m_fAngle+m_Rot.z)*m_fLength,m_Pos.y-cosf(m_fAngle+m_Rot.z)*m_fLength,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(m_Pos.x+sinf(m_fAngle-m_Rot.z)*m_fLength,m_Pos.y-cosf(m_fAngle-m_Rot.z)*m_fLength,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(m_Pos.x-sinf(m_fAngle-m_Rot.z)*m_fLength,m_Pos.y+cosf(m_fAngle-m_Rot.z)*m_fLength,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(m_Pos.x+sinf(m_fAngle+m_Rot.z)*m_fLength,m_Pos.y+cosf(m_fAngle+m_Rot.z)*m_fLength,0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,0,0,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(0,255,0,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(0,0,255,255);
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
void	CScene2D::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos=Pos;
}
//=============================================================================
//座標の取得
//=============================================================================
D3DXVECTOR3	CScene2D::GetPos(void)
{
	return m_Pos;
}
//=============================================================================
//回転の設定
//=============================================================================
void	CScene2D::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot=Rot;
}
//=============================================================================
//回転の取得
//=============================================================================
D3DXVECTOR3	CScene2D::GetRot(void)
{
	return m_Rot;
}

//=============================================================================
//オブジェクト生成
//=============================================================================
CScene2D* CScene2D::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CScene2D* pScene2D=NULL;
	pScene2D=new CScene2D(3,Type);
	pScene2D->Init(pRenderer,Pos,Rot,filename,Type);
	return pScene2D;
}