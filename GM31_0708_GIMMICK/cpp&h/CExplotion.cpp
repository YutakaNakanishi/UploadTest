//=============================================================================
//
// CExplotionクラス [CExplotion.cpp]
// Author : 中西 裕
//
// 最終更新日 6/3
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CSceneBillboard.h"
#include "CExplotion.h"
#include "CRenderer.h"
#include "camera.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define EXPLOSION_TEX_BLOCK	(0.125f)
//コンストラクタ
CExplotion::CExplotion(int nPriority,OBJTYPE Type):CSceneBillboard(nPriority,Type)
{}
//デストラクタ
CExplotion::~CExplotion()
{}
//初期化
HRESULT CExplotion::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,BYTE R,BYTE G,BYTE B,BYTE A,int Time,char * filename,OBJTYPE Type)
{
	m_Time=Time;
	m_Color.r=R;
	m_Color.g=G;
	m_Color.b=B;
	m_Color.a=A;
	m_TimeBlock=Time/8;
	m_TexU=0;
	CSceneBillboard::Init(pRenderer,Pos,Rot,filename,Type);
	VERTEX_3D *pVtx;

	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	pVtx[0].diffuse= D3DCOLOR_RGBA(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	pVtx[1].diffuse= D3DCOLOR_RGBA(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	pVtx[2].diffuse= D3DCOLOR_RGBA(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	pVtx[3].diffuse= D3DCOLOR_RGBA(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
	m_pD3DVtxBuff->Unlock();

	return S_OK;
}
//終了
void	CExplotion::Uninit(void)
{
	CSceneBillboard::Uninit();
}
//更新
void	CExplotion::Update(void)
{

	m_Time--;
	if(m_Time%m_TimeBlock==0)
	{
		m_TexU+=EXPLOSION_TEX_BLOCK;
		VERTEX_3D *pVtx;
		m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
		pVtx[0].tex=D3DXVECTOR2(m_TexU,0);
		pVtx[1].tex=D3DXVECTOR2(m_TexU+EXPLOSION_TEX_BLOCK,0);
		pVtx[2].tex=D3DXVECTOR2(m_TexU,1);
		pVtx[3].tex=D3DXVECTOR2(m_TexU+EXPLOSION_TEX_BLOCK,1);
		m_pD3DVtxBuff->Unlock();
	}
	if(m_Time==0)
	{
		CExplotion::Uninit();
	}
}
//描画
void	CExplotion::Draw(void)
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
	
	m_pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);

	//加算合成
	m_pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//ポリゴン描画					描画方法		//ポリゴン数
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

			//加算合成
	m_pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	m_pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
}
//クリエート
CExplotion* CExplotion::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,BYTE R,BYTE G,BYTE B,BYTE A,int Time,char * filename,OBJTYPE Type)
{
	CExplotion* pExplotion;
	pExplotion=new CExplotion(4,Type);
	pExplotion->Init(pRenderer,Pos,Rot,R,G,B,A,Time,filename,Type);
	return pExplotion;
}