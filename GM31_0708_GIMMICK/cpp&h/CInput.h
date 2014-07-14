//=============================================================================
//
// ���͏��� [CInput.h]
// Author : yutaka nakanishi
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
//=============================================================================
//�N���X
//=============================================================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void	Uninit(void);
	virtual void	Update(void)=0;
	static  LPDIRECTINPUT8	m_pDInput;
	LPDIRECTINPUTDEVICE8	m_pDIDevice;	
};
#endif