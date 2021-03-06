
/*
  ==============================================================================

	ThumbParser.cpp
	Created: 10 Oct 2018 11:27:40am
	Author:  Joris

  ==============================================================================
*/

#include "ThumbParser.h"

ThumbParser::ThumbParser()
{
	buildCollection();
}

ThumbParser::~ThumbParser()
{
}

Array<Thumb> ThumbParser::getThumbs()
{
	return thumbs;
}

void ThumbParser::buildCollection()
{
	thumbs.clear();
	for ( auto clip : getClips() )
	{
		Thumb thumb;
		thumb.uniqueId = clip.uniqueId;
		thumb.thumbData = getBase64ForFile( clip.thumbFileData );
		thumbs.add( thumb );
	}
}

String ThumbParser::getBase64ForFile( String thumbFileData )
{
	String base64 = String();
	if ( thumbFileData.isNotEmpty() )
	{
		String thumbname;
		File file = File( thumbFileData );
		if ( file.existsAsFile() )
		{
			thumbname = file.getFileNameWithoutExtension();
			Time time = file.getLastModificationTime();
			thumbname += String( time.getYear() )
				+ String( time.getMonth() )
				+ String( time.getDayOfMonth() )
				+ String( time.getHours() )
				+ String( time.getMinutes() )
				+ String( time.getSeconds() )
				+ String( time.getMilliseconds() )
				+ String( file.getSize() )
				+ file.getFileExtension().substring( 1 )
				+ "_video.png";
		}

		File thumbFile = File::getSpecialLocation( File::SpecialLocationType::userApplicationDataDirectory ).getParentDirectory().getChildFile( "Local/Resolume Arena 6/previews/" + thumbname );
		if ( thumbFile.existsAsFile() )
		{
			Image img = ImageFileFormat::loadFrom( thumbFile );
			PNGImageFormat format;
			MemoryOutputStream imgStream;
			format.writeImageToStream( img, imgStream );
			base64 = Base64::toBase64( imgStream.getData(), imgStream.getDataSize() );
		}
	}
	
	return base64;
}


