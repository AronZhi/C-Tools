#ifndef PATH
#define PATH

#include <string>

#ifdef _WIN32
#include <Windows.h>

void dosPath2NtPath(const WCHAR* dos_path, WCHAR* nt_path)
{
    /*
    * convert DOS path to NT path
    */
   if (wcslen(dos_path) < 3)
		return;
	WCHAR device[3] = { 0 };
	device[0] = dos_path[0];
	device[1] = dos_path[1];
	WCHAR volume[MAX_PATH] = { 0 };
	if (!QueryDosDeviceW(device, volume, MAX_PATH))
		return;

	wsprintfW(nt_path, L"%ws%ws", volume, dos_path + 2);
}

void ntPath2DosPath(const WCHAR* nt_path, WCHAR* dos_path)
{
    /*
    * convert NT path to DOS path
    */
    WCHAR all_device[MAX_PATH] = { 0 };
	WCHAR volume[MAX_PATH] = { 0 };
	WCHAR tmp[MAX_PATH] = { 0 };
	WCHAR device[3] = { 0 };
	size_t volume_len = 0;

	GetLogicalDriveStringsW(MAX_PATH, all_device);
	for (int i = 0; all_device[i]; i += 4)
	{
		device[0] = all_device[i];
		device[1] = all_device[i + 1];
		device[2] = 0;
		memset(volume, 0, MAX_PATH * sizeof(WCHAR));
		if (!QueryDosDeviceW(device, volume, MAX_PATH))
		{
			continue;
		}
		else
		{
			volume_len = wcslen(volume);
			memset(tmp, 0, MAX_PATH * sizeof(WCHAR));
			memcpy(tmp, nt_path, volume_len * sizeof(WCHAR));
			if (lstrcmpW(tmp, volume) == 0)
			{
				volume_len = wcslen(volume);
				wsprintfW(dos_path, L"%ws%ws", device, nt_path + volume_len);
				break;
			}
		}
	}
	return;
}

#endif 

int comparePath(const std::string& path, const std::string& specific_path)
{
    /*
    * Compare path and specific_path,
    * return -1 if path and specific_path are not related
    * return 0 if path equal to specific_path
    * return 1 if path is subdirectory of specific_path
    * return 2 if specific_path is subdirectory of specific_path
    */
   if ( 0 == path.compare(specific_path))
   {
       return 0;
   }
   else
   {
       if (path.length() > specific_path.length())
       {
            std::string t(path.substr(0, specific_path.length()));
            return t.compare(specific_path) == 0 ? 1 : -1;
       }
       else if (path.length() < specific_path.length())
       {
            std::string t(specific_path.substr(0, path.length()));
            return t.compare(path) == 0? 2 : -1;
       }
   }
   return -1;
}

#endif // PATH