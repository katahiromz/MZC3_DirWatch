////////////////////////////////////////////////////////////////////////////
// DirWatch_inl.h -- Win32 directory watcher
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

MZC_INLINE MDirWatch::MDirWatch() : m_hFindChange(INVALID_HANDLE_VALUE)
{
}

MZC_INLINE MDirWatch::MDirWatch(HANDLE hFindChange) :
    m_hFindChange(hFindChange)
{
}

MZC_INLINE MDirWatch::MDirWatch(
    LPCTSTR pszPath, BOOL bWatchSubTree/* = TRUE*/,
    DWORD dwNotifyChangeFlags/* = MDirWatch::check_all*/
) : m_hFindChange(INVALID_HANDLE_VALUE)
{
    FindFirstChangeNotification(pszPath, bWatchSubTree, dwNotifyChangeFlags);
}

MZC_INLINE /*virtual*/ MDirWatch::~MDirWatch()
{
    if (m_hFindChange != INVALID_HANDLE_VALUE)
        FindCloseChangeNotification();
}

MZC_INLINE MDirWatch::operator bool() const
{
    return m_hFindChange != INVALID_HANDLE_VALUE;
}

MZC_INLINE bool MDirWatch::operator!() const
{
    return m_hFindChange == INVALID_HANDLE_VALUE;
}

MZC_INLINE void MDirWatch::operator=(HANDLE hFindChange)
{
    assert(hFindChange != NULL && hFindChange != INVALID_HANDLE_VALUE);
    if (m_hFindChange != hFindChange)
    {
        if (m_hFindChange != INVALID_HANDLE_VALUE)
            FindCloseChangeNotification();
        m_hFindChange = hFindChange;
    }
}

MZC_INLINE VOID MDirWatch::Attach(HANDLE hFindChange)
{
    assert(hFindChange != NULL && hFindChange != INVALID_HANDLE_VALUE);
    assert(m_hFindChange == INVALID_HANDLE_VALUE);
    m_hFindChange = hFindChange;
}

MZC_INLINE HANDLE MDirWatch::Detach()
{
    HANDLE hFindChange = m_hFindChange;
    m_hFindChange = INVALID_HANDLE_VALUE;
    return hFindChange;
}

MZC_INLINE MDirWatch::operator HANDLE() const
{
    return m_hFindChange;
}

MZC_INLINE PHANDLE MDirWatch::operator&()
{
    return &m_hFindChange;
}

MZC_INLINE BOOL MDirWatch::FindNextChangeNotification() 
{
    assert(m_hFindChange != INVALID_HANDLE_VALUE);
    BOOL bFound = ::FindNextChangeNotification(m_hFindChange);
    return bFound;
}

MZC_INLINE BOOL MDirWatch::FindCloseChangeNotification()
{
    BOOL bOK = ::FindCloseChangeNotification(m_hFindChange);
    m_hFindChange = INVALID_HANDLE_VALUE;
    return bOK;
}

MZC_INLINE DWORD
MDirWatch::WaitForSingleObject(DWORD dwMilliseconds/* = INFINITE*/)
{
    return ::WaitForSingleObject(m_hFindChange, dwMilliseconds);
}

MZC_INLINE DWORD MDirWatch::WaitForSingleObjectEx(
    DWORD dwMilliseconds/* = INFINITE*/, BOOL bAlertable/* = TRUE*/)
{
    return ::WaitForSingleObjectEx(m_hFindChange,
                                   dwMilliseconds, bAlertable);
}

MZC_INLINE BOOL MDirWatch::FindFirstChangeNotification(
    LPCTSTR pszPath, BOOL bWatchSubTree/* = TRUE*/,
    DWORD dwNotifyChangeFlags/* = MDirWatch::check_all*/)
{
    assert(pszPath);
    assert(m_hFindChange == INVALID_HANDLE_VALUE);
    m_hFindChange = ::FindFirstChangeNotification(
        pszPath, bWatchSubTree, dwNotifyChangeFlags);
    return m_hFindChange != INVALID_HANDLE_VALUE;
}
