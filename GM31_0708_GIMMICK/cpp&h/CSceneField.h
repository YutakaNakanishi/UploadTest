//=============================================================================
//
// ���b�V���n�ʂ̏��� [CSceneField.h]
// Author : yutaka nakanishi
//
// 2014/5/21
//=============================================================================
#ifndef _CSENEFIELD_H_
#define _CSCNEFIELD_H_
//=============================================================================
//�C���N���[�h
//=============================================================================
#include "CScene.h"
#include "main.h"

//=============================================================================
//�N���X
//=============================================================================
class CRenderer;		//�O���錾
class CSceneField:public CScene
{
	public:
		//�����R���X�g���N�^
		CSceneField(int nPriority,OBJTYPE Type);
		//�f�X�g���N�^
		~CSceneField();
		//�������z�֐��p
		HRESULT Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
		//���b�V��������
		HRESULT Init(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);

		//�I������
		void Uninit();
		//�X�V����
		void Update();
		//�`�揈��
		void Draw();
		//���_���̃Z�b�g
		void SetVertexPolygon();//�������z�֐��p

		void SetVertexPolygon(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
		//���W�̐ݒ�
		void						SetPos(D3DXVECTOR3 Pos){m_Pos=Pos;};
		//���W�̎擾
		D3DXVECTOR3					GetPos(void){return m_Pos;};
		//��]�̐ݒ�
		void						SetRot(D3DXVECTOR3 Rot){m_Rot=Rot;};
		//��]�̎擾
		D3DXVECTOR3					GetRot(void){return m_Rot;};
		//�I�u�W�F�N�g����
		static CSceneField*			Create(CRenderer *pRenderer,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
		//�����擾����
		static float				GetHeight(D3DXVECTOR3 Pos);

private:
		LPDIRECT3DTEXTURE9			m_pD3DTex;		// Direct3D �e�N�X�`���|�C���^�[
		static LPDIRECT3DVERTEXBUFFER9		m_pD3DVtxBuff;	// Direct3D ���_�o�b�t�@�|�C���^�[
		LPDIRECT3DDEVICE9			m_pDevice;
		D3DXVECTOR3					m_Pos;			//�|���S�����W
		D3DXVECTOR3					m_Rot;			//�|���S���p�x
		D3DXVECTOR3					m_Scl;
		D3DXMATRIX					m_MtxWorld;
		D3DXMATRIX					m_MtxScl,m_MtxRot,m_MtxTranslate;
		D3DXMATRIX					m_MtxView;
		float						m_fLength;		//���S���璸�_�܂ł̋���
		float						m_fAngle;		//���S���璸�_�ւ̊p�x
		//�C���f�b�N�X�o�b�t�A
		LPDIRECT3DINDEXBUFFER9		m_pD3DIndexBuff;
		int							m_nNumVertexIndex;				// ���_�̑��C���f�b�N�X��
		static int					m_nNumBlockX, m_nNumBlockZ;		// �u���b�N��
		int							m_nNumVertex;					// �����_��
		int							m_nNumPolygon;					// ���|���S����
		static float				m_fSizeBlockX, m_fSizeBlockZ;	// �u���b�N�T�C�Y
		
};


#endif _CSCENEFIELD_H_