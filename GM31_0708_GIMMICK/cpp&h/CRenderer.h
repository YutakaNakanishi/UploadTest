//=============================================================================
//
// CRender�N���X [CRenderer.h]
// Author : ���� �T
//
// �ŏI�X�V�� 4/15
//=============================================================================
#ifndef _CRENDERER_H_
#define _CRENDERER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
//=============================================================================
// �}�N����`
//=============================================================================
//=============================================================================
// �N���X
//=============================================================================
class CScene;
class CCamera;
class CRenderer
{
	public:
		//�R���X�g���N�^
		CRenderer();
		//�f�X�g���N�^
		~CRenderer();
		//����������
		HRESULT						Init(HWND hWnd,BOOL bWindow);
		//�I������
		void						Uninit(void);
		//�X�V����
		void						Update(void);
		//�`�揈��
		void						Draw(void);
		//�o�^�p�֐�
		void						AddScene(CScene *pScene);
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9			GetDevice(void);
	private:
		//�f�o�b�N�̂��߂�
		void DrawFPS(void);

		//�ȉ������o�[�ϐ�
		LPDIRECT3D9					m_pD3D;			// Direct3D �I�u�W�F�N�g�|�C���^�[
		LPDIRECT3DDEVICE9			m_pD3DDevice;	// Direct3D �f�o�C�X�|�C���^�[
		CScene						*m_apScenes[SCENE_MAX];
		int							m_nCountScene;
};

#endif

