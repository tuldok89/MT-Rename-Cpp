/** A small util to automatically remove file numbers from files
 *  downloaded from Mangatraders.com
 *
 *  Execute this in a directory to rename all files in that dir.
 */

#include <stdio.h>
#include <tchar.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int _tmain()
{
    _TDIR *dir;
    struct _tdirent *entry;
    struct stat64 st;

    // open directory
    dir = _topendir(_T("./"));
    if (dir != NULL)
    {
        // get directory entries
        while ((entry = _treaddir(dir)) != NULL)
        {
            // determine if entry is a directory or a file
            _tstat64(entry->d_name, &st);

            if (!S_ISDIR(st.st_mode)) // not a directory
            {
                _TCHAR* pos = _tcschr(entry->d_name, _T('-')) + 1; // filename without the file number
                _tprintf(_T("%s -> %s\n"), entry->d_name, pos); // print name

                // rename file
                _trename(entry->d_name, pos);
            }
        }
        _tclosedir(dir);
    }
    else
    {
        _tperror(_T("Can't read directory"));
        return EXIT_FAILURE;
    }

#ifndef NDEBUG
    system("PAUSE");
#endif // DEBUG

    return EXIT_SUCCESS;
}

