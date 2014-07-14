//=============================================================================
//
// �r���{�[�h [CSceneBillboard.h]
// Author : yutaka nakanishi
//
// 2014/5/21
//=============================================================================
#ifndef _CSCENEBILLBOARD_H_
#define _CSCENEBILLBOARD_H_

#include "main.h"
#include "CScene.h"

//*****************************************************************************
// �N���X
//*****************************************************************************
class CRenderer;			//�O���錾
class CSceneBillboard:public CScene
{
	public:
		//�R���X�g���N�^
		CSceneBillboard(int nPriority,OBJTYPE Type);
		//�f�X�g���N�^
		~CSceneBillboard();
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
		static CSceneBillboard*				Create(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type);
	protected:
		LPDIRECT3DTEXTURE9		m_pD3DTex;
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;
		LPDIRECT3DDEVICE9		m_pDevice;
		D3DXVECTOR3				m_Pos;
		D3DXVECTOR3				m_Rot;
		D3DXVECTOR3				m_Scl;
		D3DXMATRIX				m_MtxWorld;
		D3DXMATRIX				m_MtxScl,m_MtxRot,m_MtxTranslate;
		D3DXMATRIX				m_MtxView;
		float					m_fLength;		//���S���璸�_�܂ł̋���
		float					m_fAngle;		//���S���璸�_�ւ̊p�x
};
#endif _CSCENEBILLBOARD_H_