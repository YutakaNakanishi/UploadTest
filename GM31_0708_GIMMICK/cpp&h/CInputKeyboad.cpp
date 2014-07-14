//=============================================================================
//
// 入力処理 [CInputKeyboad.cpp]
// Author : yutaka nakanishi
//
//=============================================================================
#include "CInputKeyboad.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
BYTE CInputKeyboard::m_aKeyState[256];
BYTE CInputKeyboard::m_aTrigKey[256];
BYTE CInputKeyboard::m_aReleaseKey[256];
BYTE CInputKeyboard::m_aRepeatKey[256];
//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	CInput::Init(hInstance,hWnd);
	// デバイスオブジェクトを作成
	hr=m_pDInput->CreateDevice(GUID_SysKeyboard,
								&m_pDIDevKeyboard,NULL);
	if(FAILED(hr))
	{
		//メッセージボックス
		MessageBox(NULL,
					"良かったです",
					"確認",
					MB_OK);
		return hr;
	}

	// データフォーマットを設定
	hr=m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		//メッセージボックス
		MessageBox(NULL,
					"かったです。",
					"確認",
					MB_OK);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr=m_pDIDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND|DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		//メッセージボックス
		MessageBox(NULL,
					"良かったです。",
					"認",
					MB_OK);
		return hr;
	}
	// キーボードへのアクセス権を獲得(入力制御開始)
	hr=m_pDIDevKeyboard->Acquire();
	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
	if(m_pDIDevKeyboard!=NULL)
	{
		// DirectInputオブジェクトの開放
		m_pDIDevKeyboard->Unacquire();

		// デバイスオブジェクトの開放
		m_pDIDevKeyboard->Release();
		m_pDIDevKeyboard=NULL;
	}

}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE	aKeyState[256];
	if(SUCCEEDED(m_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState),
													&aKeyState[0])))
	{
		for(int nKey=0;nKey<256;nKey++)
		{
			//トリガー情報など作成
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


			//家を飛び出て新しい自分になる
			m_aKeyState[nKey]=aKeyState[nKey];
		}
	}
	else
	{
		m_pDIDevKeyboard->Acquire();
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey]);
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool CInputKeyboard::GetTrig(int nKey)
{
	return (m_aTrigKey[nKey]);
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_aRepeatKey[nKey]);
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aReleaseKey[nKey]);
}
