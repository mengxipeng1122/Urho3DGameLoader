
std::string demangle(char const* mangled);

// default implementation
template <typename T>
std::string TypeName<T>::Get()
{
    return demangle(typeid(T).name());
}

