////////////////////////////////////////////////////////////////////////////
// DirWatch.cpp -- Win32 directory watcher
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE  /*empty*/
    #include "DirWatch_inl.h"
#endif

////////////////////////////////////////////////////////////////////////////

#ifdef UNITTEST
    #include <cstdio>
    using namespace std;
    int main(void)
    {
        MDirWatch watch(TEXT("."));
        printf("I'm waiting for change of this directory...\n");
        fflush(stdout);
        watch.WaitForSingleObject();
        printf("Notified.\n");
        return 0;
    }
#endif
