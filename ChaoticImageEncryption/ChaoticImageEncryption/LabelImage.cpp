#include "stdafx.h"
#include "LabelImage.h"


LabelImage::LabelImage(CImage _pImage) : m_Image(_pImage)
{

}


LabelImage::~LabelImage()
{
}


void LabelImage::SetLabel(double MinX, double MaxX, double MinY, double MaxY)
{
	m_dMaxX = MaxX;
	m_dMaxY = MaxY;
	m_dMinX = MinX;
	m_dMinY = MinY;
}

void LabelImage::SetTitle(std::string strTitle, std::string strLabelY, std::string strLabelX)
{
	m_strTitleName = strTitle;
	m_strLabelX = strLabelX;
	m_strLabelY = strLabelY;
}

void LabelImage::Draw(HDC hDC, size_t PosX, size_t PosY)
{
	size_t rowImage = m_Image.GetWidth();
	size_t colImage = m_Image.GetHeight();
	m_Image.Draw(hDC, PosX, PosY, rowImage, colImage);

}