

#include <stdio.h>
int main4()
{
	printf("hello world\n");
	return 0;
}

#include "../src/Global.h"
#include "../src/utils/log.hpp"

int main13()
{
    Vector<int> v;
    LOG_INFOS_CPP( v.Size());
    return 0;
}

int main()
{
    //SharedPtr<String> spi( new String("hello"));
    SharedPtr<FontFace> newFace(new FontFaceBitmap(nullptr));
    LOG_INFOS_CPP(newFace.Get());
    return 0;
}


