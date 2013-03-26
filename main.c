/** A small util to automatically remove file numbers from files
 *  downloaded from Mangatraders.com
 *
 *  Execute this in a directory to rename all files in that dir.
 */

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int _tmain(int argc, _TCHAR* argv)
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
                _TCHAR* fName = entry->d_name;
                _TCHAR* pos = _tcschr(fName, _T('-')); // filename without the file number

                if (pos == NULL) // filename contains no dash
                    continue;

                // print name
                _tprintf(_T("%s -> %s\n"), fName, pos + 1);

                // rename file
                _trename(entry->d_name, pos + 1);
            }
        }
        _tclosedir(dir);
    }
    else
    {
        _tperror(_T("Can't read directory"));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

