
#include "execute.h"
#include "dmformat.h"
#include "dmstrtk.hpp"
#include "dmutil.h"

int main( int argc, char* argv[] )
{
    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        auto strPath = getenv("path");
        std::string strCwd = DMGetWorkPath();

        typedef strtk::std_string::token_deque_type match_list_type;
        match_list_type match_list;
        strtk::ifind_all(strCwd, strPath, std::back_inserter(match_list));

        if (!match_list.empty())
        {
            execute->exec("echo OK!");
            return 0;
        }

        std::string strCmd = fmt::format("setx /m path \"{};{}\"", strPath, strCwd);
        execute->exec(strCmd);
    }

    return 0;
}
