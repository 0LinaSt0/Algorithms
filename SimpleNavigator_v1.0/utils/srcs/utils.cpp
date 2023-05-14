#include "../includes/utils.hpp"

namespace s21{

void PrintError(const std::string& filename, 
        const std::string& funcname, int line, const std::string& msg){
    std::cerr << filename << ": "
            << funcname << ": "
            << line << ": "
            << msg << std::endl;
}

void ReadOnlyPermissions(std::string& filepath){
    fs::path path = filepath;

    fs::permissions(
        path,
        fs::perms::none | 
            fs::perms::owner_read | 
            fs::perms::group_read | 
            fs::perms::others_read,
        fs::perm_options::replace 
    );
}

}
