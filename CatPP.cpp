#include <iostream>
#include <system_error>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string_view>

#define DEV
namespace fs = std::filesystem;

bool compare_string_literals(std::string_view s1, std::string_view s2)
{
    return s1 == s2;
}

void print_contents(const std::string& target)
{
    std::string content;
    std::string line;
    std::ifstream ifs(target);

    while(std::getline(ifs, line))
    {
        content.append(line);
        content.append("\n");
    }
    std::cout << content; 
}

bool search_directory(const std::string& target, const fs::path& start_dir = fs::current_path())
{
    std::error_code ec;
    if (!fs::exists(start_dir, ec) || !fs::is_directory(start_dir, ec))
    {
        std::cerr << "Directory does not exist: " << start_dir << "\n";
        return false;
    }

    for (auto it = fs::recursive_directory_iterator(start_dir, fs::directory_options::skip_permission_denied, ec);
         it != fs::recursive_directory_iterator(); it.increment(ec))
    {
        if (ec) continue; // skip entries that error out mid-iteration
        if (it->is_regular_file() && it->path().filename() == target)
        {
            print_contents(it->path().string());
            return true;
        }
    }
    return false;
}

fs::path parse_directory(std::string apd)
{
    return fs::current_path() / fs::path(apd).relative_path();
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
    
    if (arguements_inline == 3 && compare_string_literals(argv[1], "-d"))
    {
        fs::path search_dir = parse_directory(std::string(argv[2]));

#ifdef DEV
    std::cout << "Searching in: " << search_dir << "\n";
#endif

    if (search_directory(argv[3], search_dir))
    {
        return 0;
    }

    std::cerr << "Failed to open file or directory, maybe nonexistent?" << "\nFor help try -h\n";
    return 1;
    } 

    return 0;   
}
