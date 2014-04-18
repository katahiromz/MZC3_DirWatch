////////////////////////////////////////////////////////////////////////////
// DirWatch.h -- Win32 directory watcher
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef __MZC3_DIRWATCH__
#define __MZC3_DIRWATCH__

///////////////////////////////////////////////////////////////////////////////

class MDirWatch EXTENDS_MOBJECT
{
public:
    enum
    {
        check_file_name = FILE_NOTIFY_CHANGE_FILE_NAME,
        check_dir_name = FILE_NOTIFY_CHANGE_DIR_NAME,
        check_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES,
        check_size = FILE_NOTIFY_CHANGE_SIZE,
        check_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE,
        check_last_access = FILE_NOTIFY_CHANGE_LAST_ACCESS,
        check_creation = FILE_NOTIFY_CHANGE_CREATION,
        check_security =  FILE_NOTIFY_CHANGE_SECURITY,
        check_all = 0x17F
    }; // for dwNotifyChangeFlags

public:
    MDirWatch();
    MDirWatch(HANDLE hFindChange);
    MDirWatch(LPCTSTR pszPath, BOOL bWatchSubTree = TRUE,
              DWORD dwNotifyChangeFlags = MDirWatch::check_all);
    virtual ~MDirWatch();

    operator bool() const;
    bool operator!() const;
    operator HANDLE() const;
    void operator=(HANDLE hFindChange);
    PHANDLE operator&();

    VOID Attach(HANDLE hFindChange);
    HANDLE Detach();

    BOOL FindFirstChangeNotification(
        LPCTSTR pszPath, BOOL bWatchSubTree = TRUE,
        DWORD dwNotifyChangeFlags = MDirWatch::check_all);
    BOOL FindNextChangeNotification();  
    BOOL FindCloseChangeNotification();

    DWORD WaitForSingleObject(DWORD dwMilliseconds = INFINITE);
    DWORD WaitForSingleObjectEx(DWORD dwMilliseconds = INFINITE,
                                BOOL bAlertable = TRUE);

public:
    HANDLE m_hFindChange;
};

////////////////////////////////////////////////////////////////////////////

#ifndef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE inline
    #include "DirWatch_inl.h"
#endif

#endif  // ndef __MZC3_DIRWATCH__
