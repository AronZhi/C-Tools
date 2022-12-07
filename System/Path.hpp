#include <string>

int comparePath(const std::string& path, const std::string& specific_path)
{
    /*
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