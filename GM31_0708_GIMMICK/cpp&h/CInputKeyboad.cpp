//=============================================================================
//
// ���͏��� [CInputKeyboad.cpp]
// Author : yutaka nakanishi
//
//=============================================================================
#include "CInputKeyboad.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BYTE CInputKeyboard::m_aKeyState[256];
BYTE CInputKeyboard::m_aTrigKey[256];
BYTE CInputKeyboard::m_aReleaseKey[256];
BYTE CInputKeyboard::m_aRepeatKey[256];
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	CInput::Init(hInstance,hWnd);
	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr=m_pDInput->CreateDevice(GUID_SysKeyboard,
								&m_pDIDevKeyboard,NULL);
	if(FAILED(hr))
	{
		//���b�Z�[�W�{�b�N�X
		MessageBox(NULL,
					"�ǂ������ł�",
					"�m�F",
					MB_OK);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr=m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		//���b�Z�[�W�{�b�N�X
		MessageBox(NULL,
					"�������ł��B",
					"�m�F",
					MB_OK);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr=m_pDIDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND|DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		//���b�Z�[�W�{�b�N�X
		MessageBox(NULL,
					"�ǂ������ł��B",
					"�F",
					MB_OK);
		return hr;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	hr=m_pDIDevKeyboard->Acquire();
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
	if(m_pDIDevKeyboard!=NULL)
	{
		// DirectInput�I�u�W�F�N�g�̊J��
		m_pDIDevKeyboard->Unacquire();

		// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_pDIDevKeyboard->Release();
		m_pDIDevKeyboard=NULL;
	}

}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE	aKeyState[256];
	if(SUCCEEDED(m_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState),
													&aKeyState[0])))
	{
		for(int nKey=0;nKey<256;nKey++)
		{
			//�g���K�[���ȂǍ쐬
			m_aTrigKey[nKey]=((m_aKeyState[nKey]^aKeyState[nKey])&aKeyState[nKey]);
			m_aReleaseKey[nKey]=((m_aKeyState[nKey]^aKeyState[nKey])&m_aKeyState[nKey]);
			m_aRepeatKey[nKey]=0;
			if(aKeyState[nKey]!=0)
			{
				m_nRepeatCnt[nKey]++;
				if((m_nRepeatCnt[nKey]%2==0 && m_nRepeatCnt[nKey]>20)||m_aTrigKey[nKey]!=0)
				{
					m_aRepeatKey[nKey]=1;
				}
				
			}
			else
			{
				m_nRepeatCnt[nKey]=0;
			}


			//�Ƃ��яo�ĐV���������ɂȂ�
			m_aKeyState[nKey]=aKeyState[nKey];
		}
	}
	else
	{
		m_pDIDevKeyboard->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey]);
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetTrig(int nKey)
{
	return (m_aTrigKey[nKey]);
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_aRepeatKey[nKey]);
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aReleaseKey[nKey]);
}
