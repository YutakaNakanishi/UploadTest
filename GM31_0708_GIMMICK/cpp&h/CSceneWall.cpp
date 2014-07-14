//=============================================================================
//
// ���b�V���n�ʂ̏��� [CSceneWall.cpp]
// Author : yutaka nakanishi
//
// 2014/5/21
//=============================================================================
#include "CSceneWall.h"
#include "CRenderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define TEX_SIZE_X		(1)			// �e�N�X�`���̃T�C�Y�̓|���S�������u���b�N����
#define TEX_SIZE_Z		(1)			// �e�N�X�`���̃T�C�Y�̓|���S���c���u���b�N����

//�����R���X�g���N�^
CSceneWall::CSceneWall(int nPriority,OBJTYPE Type):CScene(nPriority,Type)
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

//�f�X�g���N�^
CSceneWall::~CSceneWall()
{}
//�������z�֐��p
HRESULT CSceneWall::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)
{
	//�����Ă邾���Ŏg���܂���I�I
	return S_OK;
}
//���b�V��������
HRESULT CSceneWall::Init(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)
{
	m_pDevice=pRenderer->GetDevice();
	//�����_��
	m_nNumVertex=(nNumBlockX+1)*(nNumBlockZ+1);
	//�|���S����
	m_nNumPolygon=nNumBlockX*nNumBlockZ*2+(nNumBlockZ-1)*4;
		//�C���f�b�N�X����
	m_nNumVertexIndex = (nNumBlockX+1)*(nNumBlockZ+1)+(nNumBlockZ-1)*(3+nNumBlockX);
	//�n�ʃ|���S���̐ݒ��������
	m_Pos	= Pos;
	m_Rot	= Rot;
	m_fLength=sqrt(nNumBlockX*fSizeBlockX*nNumBlockX*fSizeBlockX+nNumBlockZ*fSizeBlockZ*nNumBlockZ*fSizeBlockZ);
	float num1=(m_fLength/2.0f)*sin(Rot.z);
	float num2=(m_fLength/2.0f)*cos(D3DX_PI/4+Rot.z);


	//�|���S���ݒ�
	//���_������
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pD3DVtxBuff,
										NULL)))
	{
		return E_FAIL;
	}
	//�C���f�b�N�X������
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
		//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pDevice,filename,&m_pD3DTex);	
	return S_OK;

}

//�I������
void CSceneWall::Uninit()
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
//�X�V����
void CSceneWall::Update()
{}
//�`�揈��
void CSceneWall::Draw()
{
		//���[���h�g�����X�t�H�[��
	D3DXMatrixIdentity(&m_MtxWorld);
	//�g�k
	D3DXMatrixScaling(&m_MtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxScl);
	//��]
	D3DXMatrixRotationYawPitchRoll(&m_MtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&m_MtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxTranslate);
	m_pDevice->SetTransform(D3DTS_WORLD,&m_MtxWorld);

//	m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);			// ���C���[�t���[��
//	 m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//�f�[�^��n��
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pDevice->SetIndices(m_pD3DIndexBuff);
	//FVF�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);
//	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_FORCE_DWORD);			// ���C���[�t���[��
}
//���_���̃Z�b�g
void CSceneWall::SetVertexPolygon()
{
	//�������z�֐��p�Ȃ̂Ŏg��Ȃ�
}

//���_���̃Z�b�g
void CSceneWall::SetVertexPolygon(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	//���_���v�Z�p
	float fPosX,fPosZ;
	float fTexU,fTexV;
	int nNum =0;
	VERTEX_3D *pVtx;
		//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	// i�st��ɒ��_�ݒ�
	for(int i = 0; i <= nNumBlockZ; i++)
	{
		fTexU = 0;
		fTexV = (float)i/TEX_SIZE_Z;
		for(int j = 0; j <= nNumBlockX; j++)
		{
			nNum = i * (nNumBlockX+1) + j;
			fPosX = float(-fSizeBlockX * nNumBlockX/2 + j*fSizeBlockX);
			fPosZ = float(fSizeBlockZ * nNumBlockZ/2 - i*fSizeBlockZ);
			fTexU = (float)-j/TEX_SIZE_X;
			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosZ, 0.0f);
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ���v��1.0f�ɂȂ�悤�ɂ��Ȃ��ƃ_��
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[nNum].tex = D3DXVECTOR2(fTexU, fTexV);
		}
	}


	//�A�����b�N
	m_pD3DVtxBuff->Unlock();
	
	//�C���f�b�N�X�ݒ�
	WORD *pIndex;
	// xIndex�sxzIndex��
	int xIndex = 0;
	int zIndex = 0;


	m_pD3DIndexBuff->Lock(0,0,(void**)&pIndex,0);	//���b�N
	
	for(int i = 0; i < m_nNumVertexIndex; i++)
	{

		// �k�ރ|���S���_
		if(i == 2*(nNumBlockX+1)+zIndex*(2*(nNumBlockX+1)+2))
		{
			pIndex[i] =  (xIndex -1) + zIndex*(nNumBlockX+1);
			pIndex[i+1] = xIndex + (zIndex+1)*(nNumBlockX+1);

			// �i���ς��
			i += 2;
			zIndex++;
			xIndex = 0;
		}

		// ���̓_
		if(i % 2 == 0)
		{
			pIndex[i] = xIndex + (zIndex+1)*(nNumBlockX+1);

		}
		// ��̓_
		else
		{
			pIndex[i] = xIndex + zIndex*(nNumBlockX+1);
			xIndex++;
		}
	}

	m_pD3DIndexBuff->Unlock();	//�A�����b�N



}

CSceneWall*	CSceneWall::Create(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)
{
	CSceneWall* pSceneWall=NULL;
	pSceneWall=new CSceneWall(3,Type);
	pSceneWall->Init(pRenderer,nNumBlockX,nNumBlockZ,fSizeBlockX,fSizeBlockZ,Pos,Rot,filename,Type);
	return pSceneWall;
}   