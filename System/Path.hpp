#include <string>

int compareFolder(const std::string& folder, const std::string& specific_folder)
{
    /*
    * return -1 if folder and specific_folder are not related
    * return 0 if folder equal to specific_folder
    * return 1 if folder is subdirectory of specific_folder
    * return 2 if specific_folder is subdirectory of specific_folder
    */
   if ( 0 == folder.compare(specific_folder))
   {
       return 0;
   }
   else
   {
       if (folder.length() > specific_folder.length())
       {
            std::string t(folder, specific_folder.length());
            return t.compare(specific_folder) == 0 ? 1 : -1;
       }
       else if (folder.length() < specific_folder.length())
       {
            std::string t(specific_folder, folder.length());
            return t.compare(folder) == 0? -1 : 1;
       }
   }
   return -1;
}