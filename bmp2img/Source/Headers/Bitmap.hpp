#ifndef __WIZARDTOOL_BMP2IMG_BITMAP_HPP__
#define __WIZARDTOOL_BMP2IMG_BITMAP_HPP__

#include <string>

namespace WizardTool
{
#pragma pack( 1 )
	typedef struct _tagBITMAP_HEADER
	{
		char	Type[ 2 ];
		int		Size;
		int		Reserved;
		int		Offset;
		int		HeaderSize;
		int		Width;
		int		Height;
		short	Planes;
		short	BitsPerPixel;
		int		Compression;
		int		SizeImage;
		int		XPixelsPerMetre;
		int		YPixelsPerMetre;
		int		ColoursUsed;
		int		ColoursImportant;
	}BITMAP_HEADER,*PBITMAP_HEADER;
#pragma pack( )

	class Bitmap
	{
	public:
		Bitmap( );
		~Bitmap( );

		int Load( const std::string &p_FileName );

		int ExportIMAGE( );

	private:
		std::string		m_Name;
		unsigned short	m_Width;
		unsigned short	m_Height;
		unsigned char	*m_pData;
	};
}

#endif // __WIZARDTOOL_BMP2PAL_BITMAP_HPP__
