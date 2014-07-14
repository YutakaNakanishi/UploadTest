//=============================================================================
//
// 入力処理 [CInput.cpp]
// Author : yutaka nakanishi
//
//=============================================================================
#include "CInput.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECTINPUT8 CInput::m_pDInput;

//コンストラクタ
CInput::CInput()
{

}

//デストラクタ
CInput::~CInput()
{

}


HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// DirectInputオブジェクトの作成
	if(m_pDInput==NULL)
	{
		hr=DirectInput8Create(hInstance,DIRECTINPUT_VERSION,
							IID_IDirectInput8,(void**)&m_pDInput,
							NULL);
		if(FAILED(hr))
		{
			//メッセージボックス
			MessageBox(NULL,
					"良かったです。",
					"確認",
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


