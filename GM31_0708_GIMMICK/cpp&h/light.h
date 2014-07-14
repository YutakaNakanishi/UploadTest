//=============================================================================
//
// ���C�g���� [light.h]
// Author : yutaka nakanishi
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class CLight
{
	public:
		//�R���X�g���N�^
		CLight();
		//�f�X�g���N�^
		~CLight();
		//����������
		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);
		//�I������
		void	Uninit(void);
		//�X�V����
		void	Update(void);
	private:
		//���C�g
		D3DLIGHT9				m_aLight[3];
		D3DXVECTOR3				m_aVecDir[3];

};

#endif
