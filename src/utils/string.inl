
#include <any>
#include <sstream>

template<typename ... Args>
std::string ConstructStringWithFormat( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

template <typename Arg, typename... Args>
void ConstructStringToOStream_(std::ostream& out, Arg&& arg, Args&&... args)
{
    out << std::forward<Arg>(arg);
    ((out << ',' << std::forward<Args>(args)), ...);
}

template <typename Arg, typename... Args>
std::string ConstructString( Arg&& arg, Args ... args )
{
    std::ostringstream os;
    ConstructStringToOStream_(os, arg, args...);
    return os.str();
}
