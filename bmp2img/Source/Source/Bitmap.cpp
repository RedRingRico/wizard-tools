#include <Bitmap.hpp>
#include <iostream>
#include <cstdio>
#include <cstring>

namespace WizardTool
{
	Bitmap::Bitmap( ) :
		m_pData( nullptr )
	{
	}

	Bitmap::~Bitmap( )
	{
		if( m_pData )
		{
			delete [ ] m_pData;
			m_pData = nullptr;
		}
	}

	int Bitmap::Load( const std::string &p_FileName )
	{
		FILE *pFile = fopen( p_FileName.c_str( ), "rb" );

		if( pFile == NULL )
		{
			return 1;
		}

		BITMAP_HEADER Header;

		fread( &Header, sizeof( Header ), 1, pFile );

		for( int i = 0; i < Header.ColoursUsed * 4; ++i )
		{
			fgetc( pFile );
		}


		m_Name = p_FileName;

		m_Name += ".img";

		m_Width = Header.Width;
		m_Height = Header.Height;
		m_pData = new unsigned char[ m_Width * m_Height ];

		int WidthPadding = m_Width % 4;
		if( WidthPadding )
		{
			WidthPadding = 4 - WidthPadding;
		}

		for( int BitmapRow = m_Height - 1; BitmapRow >= 0;
			--BitmapRow )
		{
			fread( &m_pData[ ( Header.Width ) * BitmapRow ], 1, Header.Width,
				pFile );

			fseek( pFile, WidthPadding, SEEK_CUR );
		}

		fclose( pFile );

		return 0;
	}

	int Bitmap::ExportIMAGE( )
	{
		FILE *pFile = fopen( m_Name.c_str( ), "wb" );

		std::cout << "Exporting to IMAGE" << std::endl;

		fwrite( &m_Width, sizeof( unsigned short ), 1, pFile );
		fwrite( &m_Height, sizeof( unsigned short ), 1, pFile );
		fwrite( m_pData, m_Width * m_Height, 1, pFile );

		fclose( pFile );

		return 0;
	}
}

