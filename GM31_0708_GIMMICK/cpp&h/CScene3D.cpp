//=============================================================================
//
// Scene3D�N���X [Scene3D.cpp]
// Author : ���� �T
//
// �ŏI�X�V�� 4/16
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CScene3D.h"
#include "CRenderer.h"
#include "camera.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define POLYGON_WIDTH	(10)
#define POLYGON_HEIGHT	(10)
#define ROTATION_SPEED	(0.01f)
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
D3DXVECTOR3 Vec[2][2];
D3DXVECTOR3 AnsVec[2];
D3DXVECTOR3 NorVec;
//=============================================================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CScene3D::Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	//�܂��͎O�p�`�̂ǂ����𒆐S�ɂ����x�N�g�������
	Vec[0][0]=D3DXVECTOR3(-POLYGON_WIDTH,2,-POLYGON_HEIGHT)-D3DXVECTOR3(-POLYGON_WIDTH,0,POLYGON_HEIGHT);
	Vec[0][1]=D3DXVECTOR3(POLYGON_WIDTH,2,POLYGON_HEIGHT)-D3DXVECTOR3(-POLYGON_WIDTH,0,POLYGON_HEIGHT);
	Vec[1][0]=D3DXVECTOR3(-POLYGON_WIDTH,2,-POLYGON_HEIGHT)-D3DXVECTOR3(POLYGON_WIDTH,0,-POLYGON_HEIGHT);
	Vec[1][1]=D3DXVECTOR3(POLYGON_WIDTH,2,POLYGON_HEIGHT)-D3DXVECTOR3(POLYGON_WIDTH,0,-POLYGON_HEIGHT);


	//���ɊO�ςŖ@���x�N�g�������
	D3DXVec3Cross(&AnsVec[0],&Vec[0][0],&Vec[0][1]);
	D3DXVec3Cross(&AnsVec[1],&Vec[1][0],&Vec[1][1]);
	//�������K���Ȃ̂Ńm�[�}���C�Y����
	D3DXVec3Normalize(&AnsVec[0],&AnsVec[0]);
	D3DXVec3Normalize(&AnsVec[1],&AnsVec[1]);
	NorVec=(AnsVec[0]+AnsVec[1])/2;
	//�I���
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
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pDevice,filename,&m_pD3DTex);
	return S_OK;
}
//=============================================================================
//�I������
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
//�X�V����
//=============================================================================
void CScene3D::Update()
{
	//m_Rot.y+=D3DX_PI*ROTATION_SPEED;
	
}
//=============================================================================
//�`�揈��
//=============================================================================
void CScene3D::Draw()
{
	//m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//���[���h�g�����X�t�H�[��
	D3DXMatrixIdentity(&m_MtxWorld);


	D3DXMatrixScaling(&m_MtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxScl);
	//��]
	D3DXMatrixRotationYawPitchRoll(&m_MtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxRot);
	D3DXMatrixTranslation(&m_MtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld,&m_MtxWorld,&m_MtxTranslate);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);			// ���C���[�t���[��
	

	m_pDevice->SetTransform(D3DTS_WORLD,&m_MtxWorld);

	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pDevice->SetFVF(FVF_VERTEX_3D);
	m_pDevice->SetTexture(0,m_pD3DTex);
	
	//�|���S���`��					�`����@		//�|���S����
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);


	//m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_FORCE_DWORD);			// ���C���[�t���[��

}


//=============================================================================
//���_���̃Z�b�g
//=============================================================================
void	CScene3D::SetVertexPolygon(void)
{
	VERTEX_3D *pVtx;

	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//�|���S��
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
//���W�̐ݒ�
//=============================================================================
void	CScene3D::SetPos(D3DXVECTOR3 Pos)
{
	m_Pos=Pos;
}
//=============================================================================
//���W�̎擾
//=============================================================================
D3DXVECTOR3	CScene3D::GetPos(void)
{
	return m_Pos;
}
//=============================================================================
//��]�̐ݒ�
//=============================================================================
void	CScene3D::SetRot(D3DXVECTOR3 Rot)
{
	m_Rot=Rot;
}
//=============================================================================
//��]�̎擾
//=============================================================================
D3DXVECTOR3	CScene3D::GetRot(void)
{
	return m_Rot;
}


//=============================================================================
//�I�u�W�F�N�g����
//=============================================================================
CScene3D* CScene3D::Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type)
{
	CScene3D* pScene3D=NULL;
	pScene3D=new CScene3D(3,Type);
	pScene3D->Init(pRenderer,Pos,Rot,filename,Type);
	return pScene3D;
}