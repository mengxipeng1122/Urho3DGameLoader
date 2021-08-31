
template <typename T>
static const char* TypeName::Get();
{
    return typeid(T).name();
}

// a specialization for each type of those you want to support
// and don't like the string returned by typeid
template <>
struct TypeName<int>
{
    static const char* Get()
    {
        return "int";
    }
};

