
#include "execute.h"
#include "dmformat.h"
#include "dmstrtk.hpp"
#include "dmutil.h"

#include "dmflags.h"
#include "dmfile.h"
#include "dmcmake_package_bin.h"

DEFINE_string(VS_VERSION, "2019", "VS version");
DEFINE_string(VS_NAME, "Enterprise", "VS name");
DEFINE_string(VS_BIT, "amd64", "x86/amd64");

int main(int argc, char* argv[])
{
    DMFLAGS_INIT(argc, argv);

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
                std::string strPath = strRet.substr(it + 1, it2 - it - 1);
                auto it3 = strPath.find(FLAGS_VS_NAME);
                if (it3 != std::string::npos)
                {
                    strPath = strPath.substr(0, it3);
                    strPath = strPath + FLAGS_VS_NAME + R"(\MSBuild\Current\Bin\Microsoft.Common.CurrentVersion.targets)";
                    vecList.push_back(strPath);
                }
            }

            it = it2;
        }

        for (auto str : vecList)
        {
            auto it = str.find(FLAGS_VS_VERSION);
            if (it != std::string::npos)
            {
                bool bRet = DMWriteFile(str, std::string(DMTPL_DMCMAKE_GetData(ETPLTYPE_MICROSOFT_COMMON_CURRENTVERSION_TARGETS), DMTPL_DMCMAKE_GetDataSize(ETPLTYPE_MICROSOFT_COMMON_CURRENTVERSION_TARGETS)));
                if (bRet)
                {
                    fmt::print("patch done path: {}\n", str);
                }
                else
                {
                    fmt::print("patch failed. please use administrator run.\n");
                }

                return 0;
            }
        }

    }

    return 0;
}
