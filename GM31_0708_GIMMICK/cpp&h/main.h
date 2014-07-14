//=============================================================================
//
// メイン処理 [main.h]
// Author : yutaka nakanishi
//
// 最終更新日 4/14
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)    // 警告対策用
#include "dinput.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280.0f)				// ウインドウの幅
#define SCREEN_HEIGHT	(720.0f)				// ウインドウの高さ

#define SCENE_MAX		(10)


typedef enum
{
	MODE_TITLE=0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
//*****************************************************************************
//構造体
//*****************************************************************************
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;

typedef struct
{
	float vx;
	float vy;
	float vz;
}VECTOR;

typedef struct
{
	LPDIRECT3DTEXTURE9		g_pD3DTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;	// 頂点バッファインターフェースへのポインタ
	D3DXVECTOR3				g_pos;			// 座標
	D3DXVECTOR3				g_rot;			// 角度
	D3DXVECTOR3				g_scl;			// 拡縮
	VERTEX_3D*				pVtx;			// 頂点データポインター
	//マトリックス
	D3DXMATRIX				g_mtx;			//ワールドマトリックス
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//マトリックス情報
	VECTOR					Speed;
}DEFAULT;

typedef struct
{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
}COLORRGBA;



#endif