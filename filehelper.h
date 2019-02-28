#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <fstream>
#include <experimental/filesystem>
#include <system_error>
#include <algorithm>

namespace filehelper {

std::vector<std::string> getAllFilesInDir(const std::string &dirPath, const std::vector<std::string> dirSkipList)
{
    namespace filesys = std::experimental::filesystem;
    // Create a vector of string
    std::vector<std::string> listOfFiles;
    try {
        // Check if given path exists and points to a directory
        if (filesys::exists(dirPath) && filesys::is_directory(dirPath))
        {
            // Create a Recursive Directory Iterator object and points to the starting of directory
            filesys::recursive_directory_iterator iter(dirPath);

            // Create a Recursive Directory Iterator object pointing to end.
            filesys::recursive_directory_iterator end;

            // Iterate till end
            while (iter != end)
            {
                // Check if current entry is a directory and if exists in skip list
                if (filesys::is_directory(iter->path()) &&
                        (std::find(dirSkipList.begin(), dirSkipList.end(), iter->path().filename()) != dirSkipList.end()))
                {
                    // Skip the iteration of current directory pointed by iterator
#ifdef USING_BOOST
                    // Boost Fileystsem  API to skip current directory iteration
                    iter.no_push();
#else
                    // c++17 Filesystem API to skip current directory iteration
                    iter.disable_recursion_pending();
#endif
                }
                else
                {
                    // Add the name in vector
                    listOfFiles.push_back(iter->path().string());
                }

                std::error_code ec;
                // Increment the iterator to point to next entry in recursive iteration
                iter.increment(ec);
                if (ec) {
                    std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
                }
            }
        }
    }
    catch (std::system_error & e)
    {
        std::cerr << "Exception :: " << e.what();
    }
    return listOfFiles;
}

double toDouble(std::string& s)
{
    // do not use a reference, since we're going to modify this string
    // If you do not care about ',' or '.' in your string use a
    // reference instead.
    size_t found = s.find(",");
    if(found != std::string::npos)
        s[found]='.'; // Change ',' to '.'
    return std::atof(s.c_str());
}

}



#endif // FILEHELPER_H
