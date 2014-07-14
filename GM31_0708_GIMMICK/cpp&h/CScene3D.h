//=============================================================================
//
// CRender�N���X [CScene3D.h]
// Author : ���� �T
//
// �ŏI�X�V�� 4/23
//=============================================================================
#ifndef _CSCENE3D_H_
#define _CSCENE3D_H_

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
class CScene3D:public CScene
{
	public:
		//�����R���X�g���N�^
		CScene3D(int nPriority,OBJTYPE Type);
		//�f�X�g���N�^
		~CScene3D();
		//����������
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
		//�I������
		void Uninit();
		//�X�V����
		void Update();
		//�`�揈��
		void Draw();
		//���_���̃Z�b�g
		void SetVertexPolygon();
		//���W�̐ݒ�
		void						SetPos(D3DXVECTOR3 Pos);
		//���W�̎擾
		D3DXVECTOR3					GetPos(void);
		//��]�̐ݒ�
		void						SetRot(D3DXVECTOR3 Rot);
		//��]�̎擾
		D3DXVECTOR3					GetRot(void);
		//�I�u�W�F�N�g����
		static CScene3D*			Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char * filename,OBJTYPE Type);
	private:
		LPDIRECT3DTEXTURE9			m_pD3DTex;		// Direct3D �e�N�X�`���|�C���^�[
		LPDIRECT3DVERTEXBUFFER9		m_pD3DVtxBuff;	// Direct3D ���_�o�b�t�@�|�C���^�[
		LPDIRECT3DDEVICE9			m_pDevice;
		D3DXVECTOR3					m_Pos;			//�|���S�����W
		D3DXVECTOR3					m_Rot;			//�|���S���p�x
		D3DXVECTOR3					m_Scl;
		D3DXMATRIX					m_MtxWorld;
		D3DXMATRIX					m_MtxScl,m_MtxRot,m_MtxTranslate;
		D3DXMATRIX					m_MtxView;
		float						m_fLength;		//���S���璸�_�܂ł̋���
		float						m_fAngle;		//���S���璸�_�ւ̊p�x

};

#endif _SCENE2D_H_
