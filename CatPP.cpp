#include <iostream>
#include <system_error>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string_view>

namespace fs = std::filesystem;

bool compare_string_literals(std::string_view s1, std::string_view s2)
{
    return s1 == s2;
}

void print_contents(const std::string& target)
{
    std::string content;
    std::ifstream ifs(target);

    while(std::getline(ifs, content))
    {
        std::cout << content;
    }
}

bool search_directory(const std::string& target, const fs::path& start_dir = fs::current_path())
{
    for (const auto& entry : fs::recursive_directory_iterator(start_dir))
    {
        if(entry.is_regular_file() && entry.path().filename() == target)
        {
            print_contents(entry.path().string());
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        return 1;
    }
    int arguements_inline = argc - 1;
    
    if(arguements_inline > 3)
    {
        std::cerr << "Too many arguements." << "\nFor help try -h as a single arguement!";
        return 1;
    }
    
    if(arguements_inline == 1 && compare_string_literals("-h", argv[1]))
    {
        std::cout << 
        R"(
            CatPP version 0.1.0 by Saso
            CatPP is meant to be a cat clone for windows, allowing users to print contents of files into the command line
            For more information run -h

            Facilities:
            -h      help
            -v      version
            -d      enter search directory

            Example:
            CatPP out.txt           #this outputs out.txt into the command line from the current directory

            CatPP -d /files text.txt            #this outputs text.txt from the files directory        
        )" << "\n";

        return 0;
    }
    
    if(arguements_inline == 1)
    {
        if(search_directory(argv[1]))
        {
            return 0;
        }
        std::cerr << "Failed to open file, maybe nonexistent?" << "\n\n" << "For help try -h\n";
        return 1;
    }  
    
    if(arguements_inline == 3 && compare_string_literals(argv[1], "-d"))
    {
        if(search_directory(argv[2], argv[3]))
        {
            return 0;
        }

        std::cerr << "Failed to open file or directory, maybe nonexistent?" << "For help try -h\n";
        return 1;
    }

    return 0;   
}
