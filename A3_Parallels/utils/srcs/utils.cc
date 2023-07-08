#include "../includes/utils.h"

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

std::ostream& operator<<(std::ostream& out, const s21::TsmResult& tsm_result){
    out
        << "distance: " << tsm_result.distance << std::endl
        << "vertices: " << std::endl;
    
    for (size_t i = 0; i < tsm_result.vertices.size(); i++){
        out << tsm_result.vertices[i];
        if (i + 1 != tsm_result.vertices.size()) out << "->";
    }

    return out;
}
