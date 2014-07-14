//=============================================================================
//
// モデル処理 [camera.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class CCamera
{
public:
	//コンストラクタ
	CCamera();
	//デストラクタ
	~CCamera();
	//初期化
	HRESULT Init(void);
	//終了
	void Uninit(void);
	//更新
	void Update(void);
	//カメラセット
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);
	//回転角取得
	static D3DXVECTOR3 GetRot(void);
	//行列ゲット
	static D3DXMATRIX GetMtxView(void);
private:
	D3DXVECTOR3				m_posCameraP;		//視点
	D3DXVECTOR3				m_posCameraR;		//注視点
	D3DXVECTOR3				m_vecCameraU;		//上方向ベクトル
	static D3DXVECTOR3		m_rotCamera;		//カメラの向き(回転角)
	D3DXVECTOR3				m_posCameraPDest;
	D3DXVECTOR3				m_posCameraRDest;
	D3DXVECTOR3				m_rotDestCamera;
	//マトリックス	
	static D3DXMATRIX		m_mtxView;			//ビューマトリックス
	D3DXMATRIX				m_mtxProjection;	//プロジェクションマトリックス
	D3DXVECTOR3				m_vecDir;
	float					m_fAngle;			//角度
	float					m_fLength;			//距離
	float					m_fradian;			//半径
};
	#endif
	