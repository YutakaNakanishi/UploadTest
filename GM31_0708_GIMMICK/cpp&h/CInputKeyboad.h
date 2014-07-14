//=============================================================================
//
// ì¸óÕèàóù [CInputKeyboad.h]
// Author : yutaka nakanishi
//
//=============================================================================
#ifndef _CINPUTKEYBOAD_H_
#define _CINPUTKEYBOAD_H_

#include "main.h"
#include "CInput.h"

//*****************************************************************************
// ÉNÉâÉX
//*****************************************************************************
class CInputKeyboard:public CInput
{
	public:
		CInputKeyboard();
		~CInputKeyboard();
		HRESULT Init(HINSTANCE hInstance, HWND hWnd);
		void	Uninit(void);
		void	Update(void);
		static bool	GetPress(int nKey);
		static bool	GetTrig(int nKey);
		static bool	GetRepeat(int nKey);
		static bool	GetRelease(int nKey);
	private:
		LPDIRECTINPUTDEVICE8	m_pDIDevKeyboard;
		static BYTE				m_aKeyState[256];
		static BYTE				m_aTrigKey[256];
		static BYTE				m_aReleaseKey[256];
		static BYTE				m_aRepeatKey[256];
		int						m_nRepeatCnt[256];

};

#endif