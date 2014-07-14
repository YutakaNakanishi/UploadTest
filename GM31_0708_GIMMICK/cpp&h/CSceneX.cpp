//=============================================================================
//
// SceneX�N���X [SceneX.cpp]
// Author : ���� �T
//
// �ŏI�X�V�� 4/28
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CSceneX.h"
#include "CRenderer.h"
#include "camera.h"
#include "CInputKeyboad.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define POLYGON_WIDTH	(100)
#define POLYGON_HEIGHT	(200)
#define ROTATION_SPEED	(0.01f)
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
//�R���X�g���N�^
CSceneX::CSceneX(int nPriority,OBJTYPE Type):CScene(nPriority,Type)
{
	m_pD3DTex=NULL;		
	m_pD3DBuffMat=NULL;	
	m_pD3DXMesh=NULL;
	m_nNumMat=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);			
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);;			
	m_Scl=D3DXVECTOR3(0.5f,0.5f,0.5f);;
	m_fLength=0.0f;		
	m_fAngle=0.0f;		
}
//�f�X�g���N�^
CSceneX::~CSceneX()
{

}
//����������
HRESULT CSceneX::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)
{
	m_Pos=Pos;
	m_Rot=Rot;
	m_pDevice=pRenderer->GetDevice();
	if(FAILED(D3DXLoadMeshFromX(filename,
								D3DXMESH_SYSTEMMEM,
								m_pDevice,
								NULL,
								&m_pD3DBuffMat,
								NULL,
								&m_nNumMat,
								&m_pD3DXMesh)))
	{
		return E_FAIL;
	}
	return S_OK;

}
//�I������
void CSceneX::Uninit()
{
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	if(m_pD3DBuffMat!=NULL)
	{
		m_pD3DBuffMat->Release();
		m_pD3DBuffMat=NULL;
	}
	if(m_pD3DXMesh!=NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh=NULL;
	}
	Release();
}

//�X�V����
void CSceneX::Update()
{
	if(CInputKeyboard::GetTrig(DIK_BACK))
	{
		this->Uninit();
	}
}
//�`�揈��
void CSceneX::Draw()
{
	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_MtxWorld);
	D3DXMatrixScaling(&m_MtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxScl);
	D3DXMatrixRotationYawPitchRoll(&m_MtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxRot);
	D3DXMatrixTranslation(&m_MtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxTranslate);
	
	m_pDevice->SetTransform(D3DTS_WORLD,&m_MtxWorld);
	//�}�e���A���ݒ�
	m_pDevice->GetMaterial(&m_MatDef);
	m_pD3DMat=(D3DXMATERIAL*)m_pD3DBuffMat->GetBufferPointer();

	SetVertexPolygon();

	m_pDevice->SetMaterial(&m_MatDef);


}

void CSceneX::SetVertexPolygon()
{
	for(int nCntMat=0;nCntMat<m_nNumMat;nCntMat++)
	{
		m_pDevice->SetMaterial(&m_pD3DMat[nCntMat].MatD3D);
		m_pDevice->SetTexture(0,NULL);
		m_pD3DXMesh->DrawSubset(nCntMat);
	}
}

CSceneX* CSceneX::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)
{
	CSceneX* pSceneX=NULL;
	pSceneX=new CSceneX(3,Type);
	pSceneX->Init(pRenderer,Pos,Rot,filename,Type);
	return pSceneX;
}

