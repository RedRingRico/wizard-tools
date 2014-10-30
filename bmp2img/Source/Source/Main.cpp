#include <iostream>
#include <Bitmap.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Bitmap (.BMP) to Wizard IMAGE converter" << std::endl;

	if( p_Argc != 2 )
	{
		std::cout << "Usage" << std::endl;
		std::cout << p_ppArgv[ 0 ] << " file.bmp" << std::endl;
		return 1;
	}

	WizardTool::Bitmap TheBitmap;

	TheBitmap.Load( p_ppArgv[ 1 ] );

	TheBitmap.ExportIMAGE( );

	return 0;
}

