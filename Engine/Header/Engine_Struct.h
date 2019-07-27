#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine 
{
	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3			vPosition;
		D3DXVECTOR2			vTexUV;
	}VTXTEX;

	typedef struct tagPolygon16
	{
		unsigned short		_1, _2, _3;
	}POLYGON16;

	typedef struct tagView_Matrix
	{
		D3DXVECTOR3 m_vAt, m_vEye;
		D3DXVECTOR3 m_vAxisY = { 0.f,1.f,0.f };
	}DESC_VIEW;
	typedef struct tagProj_Matrix
	{
		int		m_iBackCX, m_iBackCY;		// 창의 크기 -> 창의 크기의 비율 800:800 => 1:1 800:600 -> ㅁㄴㅇ리ㅏㅓㅁ니ㅏ
		float	m_fNear, m_fFar;			// 출력해야할 영역의 최대거리 : Far, 눈 바로 앞까지의 거리 : Near
	}DESC_PROJ;


}

#endif   