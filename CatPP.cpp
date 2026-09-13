#include <iostream>
#include <system_error>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string_view>

bool compare_string_literals(std::string_view s1, std::string_view s2)
{
    return s1 == s2;
}


int main(int argc, char** argv)
{
    int arguements_inline = argc - 1;
    
    if(arguements_inline > 2)
    {
        std::cerr << "Too many arguements." << "\n for help try -h as a single arguement!";
        return 1;
    }
    
    if(compare_string_literals("-h", argv[1]))
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


    }

    return 0;   
}
