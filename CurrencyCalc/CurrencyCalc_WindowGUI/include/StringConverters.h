


#include <string>
#include <locale>

std::wstring to_wstring ( const std::string & s, const std::locale & loc = std::locale() )
{
   std::wstring buf( s.size(), L' ' );
   std::use_facet< std::ctype<wchar_t> >(loc).widen( s.data(), s.data() + s.size(), buf.data() );
   return std::wstring( buf.data(), buf.size() );
}


std::string to_string (const std::wstring & s, const std::locale & loc = std::locale() )
{
   std::string buf( s.size(), ' ' );
   std::use_facet< std::ctype<wchar_t> >(loc).narrow( s.data(), s.data() + s.size(), '.', buf.data() );
   return std::string( buf.data(), buf.size() );
}




