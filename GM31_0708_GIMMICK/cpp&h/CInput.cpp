//=============================================================================
//
// ���͏��� [CInput.cpp]
// Author : yutaka nakanishi
//
//=============================================================================
#include "CInput.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECTINPUT8 CInput::m_pDInput;

//�R���X�g���N�^
CInput::CInput()
{

}

//�f�X�g���N�^
CInput::~CInput()
{

}


HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if(m_pDInput==NULL)
	{
		hr=DirectInput8Create(hInstance,DIRECTINPUT_VERSION,
							IID_IDirectInput8,(void**)&m_pDInput,
							NULL);
		if(FAILED(hr))
		{
			//���b�Z�[�W�{�b�N�X
			MessageBox(NULL,
					"�ǂ������ł��B",
					"�m�F",
					MB_OK);
			return hr;
		}
	}
	return S_OK;
}

void CInput::Uninit()
{
	if(m_pDInput!=NULL)
	{
		m_pDInput->Release();
		m_pDInput=NULL;
	}
}


