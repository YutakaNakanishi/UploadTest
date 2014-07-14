//=============================================================================
//
// メッシュ地面の処理 [CSceneCylinder.cpp]
// Author : yutaka nakanishi
//
// 2014/6/10
//=============================================================================
#include "CMeshCylinder.h"
#include "CRenderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define TEX_SIZE_X		(100.0f)			// テクスチャのサイズはポリゴン横何ブロック分か
#define TEX_SIZE_Z		(20.0f)			// テクスチャのサイズはポリゴン縦何ブロック分か

//引数コンストラクタ
CMeshCylinder::CMeshCylinder(int nPriority,OBJTYPE Type):CScene(nPriority,Type)
{
	m_pD3DTex=NULL;
	m_pD3DVtxBuff=NULL;
	m_pDevice=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_pD3DIndexBuff=NULL;
	m_nNumVertexIndex=NULL;
	m_nNumBlockX=0;
	m_nNumBlockZ=0;
	m_nNumVertex=0;
	m_nNumPolygon=0;
	m_fSizeBlockX=0;
	m_fSizeBlockZ=0;

}

//デストラクタ
CMeshCylinder::~CMeshCylinder()
{}
//純粋仮想関数用
HRESULT CMeshCylinder::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)
{
	//書いてるだけで使いません！！
	return S_OK;
}
//メッシュ初期化
HRESULT CMeshCylinder::Init(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float fRadius,char* filename,OBJTYPE Type)
{
	m_pDevice=pRenderer->GetDevice();
	//総頂点数
	m_nNumVertex=(nNumBlockX+1)*(nNumBlockZ+1);
	//ポリゴン数
	m_nNumPolygon=nNumBlockX*nNumBlockZ*2+(nNumBlockZ-1)*4;
		//インデックス総数
	m_nNumVertexIndex = (nNumBlockX+1)*(nNumBlockZ+1)+(nNumBlockZ-1)*(3+nNumBlockX);
	//地面ポリゴンの設定を初期化
	m_Pos	= Pos;
	m_Rot	= Rot;
	m_radius=fRadius;



	//ポリゴン設定
	//頂点初期化
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pD3DVtxBuff,
										NULL)))
	{
		return E_FAIL;
	}
	//インデックス初期化
	if(FAILED(m_pDevice->CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&m_pD3DIndexBuff,
										NULL)))
	{
		return E_FAIL;
	}
	SetVertexPolygon(nNumBlockX,nNumBlockZ,fSizeBlockX,fSizeBlockZ);
		//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pDevice,filename,&m_pD3DTex);	

	return S_OK;

}

//終了処理
void CMeshCylinder::Uninit()
{
	if(m_pD3DVtxBuff != NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}
	if(m_pD3DTex!=NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	if(m_pD3DIndexBuff!=NULL)
	{
		m_pD3DIndexBuff->Release();
		m_pD3DIndexBuff=NULL;
	}
	Release();
}
//更新処理
void CMeshCylinder::Update()
{}
//描画処理
void CMeshCylinder::Draw()
{
		//ワールドトランスフォーム
	D3DXMatrixIdentity(&m_MtxWorld);
	//拡縮
	D3DXMatrixScaling(&m_MtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxScl);
	//回転
	D3DXMatrixRotationYawPitchRoll(&m_MtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxRot);
	//平行移動
	D3DXMatrixTranslation(&m_MtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxTranslate);
	m_pDevice->SetTransform(D3DTS_WORLD,&m_MtxWorld);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);			// ワイヤーフレーム
//	 m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//データを渡す
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pDevice->SetIndices(m_pD3DIndexBuff);
	//FVFの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);
//	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//	m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_FORCE_DWORD);			// ワイヤーフレーム
}
//頂点情報のセット
void CMeshCylinder::SetVertexPolygon()
{
	//純粋仮想関数用なので使わない
}

//頂点情報のセット
void CMeshCylinder::SetVertexPolygon(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	//頂点情報計算用
	float fPosX,fPosY,fPosZ;
	float fTexU,fTexV;
	float fRot=0.0f;
	float fAddRot=(2*D3DX_PI)/nNumBlockX;
	int nNum =0;
	VERTEX_3D *pVtx;
		//ロック
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	// i行t列に頂点設定
	for(int i = 0; i <= nNumBlockZ; i++)
	{
		fTexU = 0;
		fTexV = (float)i/nNumBlockZ;
		for(int j = 0; j <= nNumBlockX; j++)
		{
			nNum = i * (nNumBlockX+1) + j;
			fPosX = float(m_radius*cos(fRot));
			fPosY = float(m_radius*sin(fRot));
			fPosZ = float(m_fSizeBlockZ * nNumBlockZ/2 - i*fSizeBlockZ);
			fTexU = (float)-j/(nNumBlockX/3);
			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 合計が1.0fになるようにしないとダメ
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[nNum].tex = D3DXVECTOR2(fTexU, fTexV);
			fRot+=fAddRot;
		}
		fRot=0;
	}


	//アンロック
	m_pD3DVtxBuff->Unlock();
	
	//インデックス設定
	WORD *pIndex;
	// xIndex行xzIndex列
	int xIndex = 0;
	int zIndex = 0;


	m_pD3DIndexBuff->Lock(0,0,(void**)&pIndex,0);	//ロック
	
	for(int i = 0; i < m_nNumVertexIndex; i++)
	{

		// 縮退ポリゴン点
		if(i == 2*(nNumBlockX+1)+zIndex*(2*(nNumBlockX+1)+2))
		{
			pIndex[i] =  (xIndex -1) + zIndex*(nNumBlockX+1);
			pIndex[i+1] = xIndex + (zIndex+1)*(nNumBlockX+1);

			// 段が変わる
			i += 2;
			zIndex++;
			xIndex = 0;
		}

		// 下の点
		if(i % 2 == 0)
		{
			pIndex[i] = xIndex + (zIndex+1)*(nNumBlockX+1);

		}
		// 上の点
		else
		{
			pIndex[i] = xIndex + zIndex*(nNumBlockX+1);
			xIndex++;
		}
	}

	m_pD3DIndexBuff->Unlock();	//アンロック



}

CMeshCylinder*	CMeshCylinder::Create(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float fRadius,char* filename,OBJTYPE Type)
{
	CMeshCylinder* pMeshCylinder=NULL;
	pMeshCylinder=new CMeshCylinder(3,Type);
	pMeshCylinder->Init(pRenderer,nNumBlockX,nNumBlockZ,fSizeBlockX,fSizeBlockZ,Pos,Rot,fRadius,filename,Type);
	return pMeshCylinder;
}   