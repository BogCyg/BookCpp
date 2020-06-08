///////////////////////////////////////////////////////
// BC++ book
///////////////////////////////////////////////////////
// by Boguslaw Cyganek, Wiley, 2019
///////////////////////////////////////////////////////



#pragma once

#include <cassert>
#include <string>
#include <memory>


namespace CppBook
{


class HTTP_File_Body
{

	public:

		virtual bool	Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName ) = 0;
		
		virtual ~HTTP_File_Body() = default;	// a virtual desctructor to allow inheritance

};


class HTTP_File_Body_Windows : public HTTP_File_Body
{

	public:

		bool	Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName ) override;

};

class HTTP_File_Body_Linux : public HTTP_File_Body
{

	public:

		bool	Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName ) override;

};

class HTTP_File_Body_MacOS : public HTTP_File_Body
{

	public:

		bool	Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName ) override;

};



class HTTP_File_Handle
{
	private:

		using BodyPtr = std::unique_ptr< HTTP_File_Body >;

		BodyPtr		fBodyObj;

	public:

		enum class EHandledSystems { kWindows, kLinux, kMac };

		HTTP_File_Handle( EHandledSystems system )
		{
			switch( system )
			{
				case EHandledSystems::kWindows:
				fBodyObj = std::make_unique< HTTP_File_Body_Windows >();
				break;

				case EHandledSystems::kLinux:
				fBodyObj = std::make_unique< HTTP_File_Body_Linux >();
				break;		

				case EHandledSystems::kMac:
				fBodyObj = std::make_unique< HTTP_File_Body_MacOS >();
				break;		

				default:
				assert( false );	// not supported
				break;		
			}
	
	
		}

	public:	
	
		virtual bool	Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
		{
			assert( fBodyObj );
			return fBodyObj->Load_HTTP_File( internet_addr, localName );	// delegate an action to the body
		}


	public:	

		virtual ~HTTP_File_Handle() = default;	// a virtual desctuctor to allow inheritance

};



}	// CppBook


