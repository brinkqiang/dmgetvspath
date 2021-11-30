
#include "execute.h"
#include "dmformat.h"
#include "dmstrtk.hpp"
#include "dmutil.h"

int main(int argc, char* argv[])
{
    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        std::string strCwd = DMGetWorkPath();

        std::string strCmd = fmt::format(R"(REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\devenv.exe)");
        std::string strRet = execute->exec(strCmd);

        std::vector<std::string> vecList;
        auto it = strRet.find_first_of(R"(")");
        while (it != std::string::npos)
        {
            auto it2 = strRet.find_first_of(R"(")", it + 1);

            if (it2 != std::string::npos)
            {
                std::string strPath = strRet.substr(it, it2 - it + 1);
                auto it3 = strPath.find("Enterprise");
                if (it3 != std::string::npos)
                {
                    strPath = strPath.substr(0, it3);
                    strPath = strPath + R"(VC\Auxiliary\Build\vcvarsall.bat")";
                    vecList.push_back(strPath);
                }
            }

            it = it2;
        }

        for (auto str : vecList)
        {
            std::string strRet = execute->exec(fmt::format("call {} {}", str, "amd64"));

        }

    }

    return 0;
}
