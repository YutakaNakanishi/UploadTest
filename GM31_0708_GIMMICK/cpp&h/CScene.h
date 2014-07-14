//=============================================================================
//
// CRender�N���X [CScene.h]
// Author : ���� �T
//
// �ŏI�X�V�� 4/21
//=============================================================================
#ifndef _CSCENE_H_
#define _CSCENE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_PRIORITY	(8)
typedef enum
		{
			OBJTYPE_NONE=0,
			OBJTYPE_2D,
			OBJTYPE_3D,
			OBJTYPE_X,
			OBJTYPE_BILLBOARD,
			OBJTYPE_SQHERE,
			OBJTYPE_DOME,
			OBJTYPE_CYLINDER,
			OBJTYPE_FIELD,
			OBJTYPE_WALL,
			OBJTYPE_ENEMY,
			OBJTYPE_PLAYER,
			OBJTYPE_EXPLOTION,
			OBJTYPE_BULLET,
			OBJTYPE_GIMICK,
			OBJTYPE_MAX
		}OBJTYPE;
//=============================================================================
// �N���X
//=============================================================================
class CRenderer;
class CScene
{
	public:
		
		//�����R���X�g���N�^
		CScene(int nPriority=3,OBJTYPE Type=OBJTYPE_NONE);
		//�f�X�g���N�^
		virtual ~CScene();
		//����������
		virtual HRESULT			Init(CRenderer *pRenderer,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,char* filename,OBJTYPE Type)=0;
		//�I������
		virtual void			Uninit()=0;
		//�X�V����
		virtual void			Update()=0;
		//�`�揈��
		virtual void			Draw()=0;
		//���_���̃Z�b�g
		virtual void			SetVertexPolygon()=0;
		//�����N�ǉ�����
		void LinkList(void);						//���g�������N�ɂȂ���
		//�����N����O������
		void UnlinkList(void);						//���X�g����폜�i�O���Ƃ����C���[�W�Ńf�[�^�͍폜���Ȃ��j
		//���W�̐ݒ�
		virtual void			SetPos(D3DXVECTOR3 Pos)=0;
		//���W�̎擾
		virtual D3DXVECTOR3		GetPos(void)=0;
		//��]�̐ݒ�
		virtual void			SetRot(D3DXVECTOR3 Rot)=0;
		//��]�̎擾
		virtual D3DXVECTOR3		GetRot(void)=0;
		OBJTYPE GetObjType(){return m_ObjType;};
		virtual void SetPositionOld(D3DXVECTOR3 PosOld){};
		virtual D3DXVECTOR3 GetPositionOld(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual void SetRotationOld(D3DXVECTOR3 RotOld){};
		virtual D3DXVECTOR3 GetRotationOld(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual D3DXVECTOR3 GetVertexMin(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual D3DXVECTOR3 GetVertexMax(){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		//�S���X�V
		static void UpdateAll(void);
		//�S���`��
		static void DrawAll(void);
		//�S�����
		static void ReleaseAll(void);
		//���
		void Release(void);


	private:
		//���X�g�\���p
		static CScene*	m_pTop[NUM_PRIORITY];		//���X�g�̐擪�A�h���X
		static CScene*	m_pCur[NUM_PRIORITY];		//���X�g�̏I�[�A�h���X
		CScene*			m_pPrev;					//�O�̃I�u�W�F�N�g�ւ̃|�C���^(�A�h���X)
		CScene*			m_pNext;					//���̃I�u�W�F�N�g�ւ̃|�C���^(�A�h���X)
		int				m_nPriority;				//�`��D�揇��
		bool			m_bDelete;					//�I�u�W�F�N�g�폜�t���O
		OBJTYPE			m_ObjType;
};

#endif _CSCENE_H_