//=============================================================================
//
// 入力処理 [CInput.h]
// Author : yutaka nakanishi
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
//=============================================================================
//クラス
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