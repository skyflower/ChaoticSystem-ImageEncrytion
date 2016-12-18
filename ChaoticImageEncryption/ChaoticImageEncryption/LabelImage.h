
#pragma once
#include "atlimage.h"
#include <cstring>
#include <iostream>

class LabelImage :
	public CImage
{
public:
	LabelImage(CImage _pImage);
	virtual ~LabelImage();

public:
	void SetLabel(double MinX, double MaxX, double MinY, double MaxY);

public:
	void SetTitle(std::string strTitle, std::string strLabelY, std::string strLabelX);

public:
	void Draw(HDC hDC, size_t PosX, size_t PosY);

private:
	CImage m_Image;
	double m_dMinX;
	double m_dMaxX;
	double m_dMinY;
	double m_dMaxY;
	std::string m_strTitleName;
	std::string m_strLabelX;
	std::string m_strLabelY;
};

