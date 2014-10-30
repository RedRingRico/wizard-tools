#include <Bitmap.hpp>
#include <iostream>
#include <cstdio>
#include <cstring>

namespace WizardTool
{
	Bitmap::Bitmap( ) :
		m_PaletteCount( 0 )
	{
		memset( m_Palette, 0, sizeof( m_Palette ) );
	}

	Bitmap::~Bitmap( )
	{
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

		m_PaletteCount = Header.ColoursUsed;

		for( int i = 0; i < Header.ColoursUsed; ++i )
		{
			unsigned char PaletteSwizzle[ 3 ];

			fread( PaletteSwizzle, 3, 1, pFile );
			fgetc( pFile );
			
			m_Palette[ i * 3 ] = ( PaletteSwizzle[ 2 ] >> 2 );
			m_Palette[ ( i * 3 ) + 1 ] = ( PaletteSwizzle[ 1 ] >> 2 );
			m_Palette[ ( i * 3 ) + 2 ] = ( PaletteSwizzle[ 0 ] >> 2 );
		}

		fclose( pFile );

		m_Name = p_FileName;

		m_Name += ".pal";

		return 0;
	}

	int Bitmap::ExportPalette( )
	{
		FILE *pExportFile = fopen( m_Name.c_str( ), "wb" );

		std::cout << "Exporting " << m_PaletteCount << " colours" << std::endl;

		fwrite( &m_PaletteCount, sizeof( m_PaletteCount ), 1, pExportFile );
		fwrite( m_Palette, m_PaletteCount * 3, 1, pExportFile );

		fclose( pExportFile );

		return 0;
	}
}

