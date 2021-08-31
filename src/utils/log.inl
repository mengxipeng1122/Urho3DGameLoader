
template<typename T, typename... Args>
void _log(T t, Args... args) // recursive variadic function
{
    std::cout << t << " ";
    _log(args...) ;
}
