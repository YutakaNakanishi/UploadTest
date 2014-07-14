//=============================================================================
//
// CRender�N���X [CSceneX.h]
// Author : ���� �T
//
// �ŏI�X�V�� 4/23
//=============================================================================
#ifndef _CSCENEX_H_
#define _CSCENEX_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "CScene.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �N���X
//=============================================================================
class CRenderer;
class CSceneX:public CScene
{
	public:
		//�R���X�g���N�^
		CSceneX(int nPriority,OBJTYPE nType);
		//�f�X�g���N�^
		~CSceneX();
		//����������
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
		//�I������
		void Uninit();
		//�X�V����
		void Update();
		//�`�揈��
		void Draw();
		//���_���̃Z�b�g
		void						SetVertexPolygon();
		//���W�̐ݒ�
		void						SetPos(D3DXVECTOR3 Pos){m_Pos=Pos;};
		//���W�̎擾
		D3DXVECTOR3					GetPos(void){return m_Pos;};
		//��]�̐ݒ�
		void						SetRot(D3DXVECTOR3 Rot){m_Rot=Rot;};
		//��]�̎擾
		D3DXVECTOR3					GetRot(void){return m_Rot;};
		//�I�u�W�F�N�g����
		static CSceneX*				Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
	private:
		LPDIRECT3DTEXTURE9			m_pD3DTex;		// Direct3D �e�N�X�`���|�C���^�[
		LPD3DXBUFFER				m_pD3DBuffMat;	// Direct3D ���_�o�b�t�@�|�C���^�[
		LPD3DXMESH					m_pD3DXMesh;
		D3DXMATERIAL				*m_pD3DMat;
		LPDIRECT3DDEVICE9			m_pDevice;
		DWORD						m_nNumMat;
		D3DMATERIAL9				m_MatDef;
		D3DXVECTOR3					m_Pos;			//�|���S�����W
		D3DXVECTOR3					m_Rot;			//�|���S���p�x
		D3DXVECTOR3					m_Scl;
		D3DXMATRIX					m_MtxWorld;
		D3DXMATRIX					m_MtxScl,m_MtxRot,m_MtxTranslate;
		D3DXMATRIX					m_MtxView;
		float						m_fLength;		//���S���璸�_�܂ł̋���
		float						m_fAngle;		//���S���璸�_�ւ̊p�x

};

#endif _SCENEX_H_

