
#include "execute.h"
#include "dmformat.h"
#include "dmstrtk.hpp"
#include "dmutil.h"

#include "dmflags.h"
#include "dmfile.h"

DEFINE_string(GETIP_CMD, R"(wsl -- ifconfig eth0 | find "inet ")", "");
DEFINE_string(SET_WSL_HOST_NAME, "WSL2.HOST", "");

int main(int argc, char* argv[])
{
    DMFLAGS_INIT(argc, argv);

    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        std::string strCwd = DMGetWorkPath();

        std::string strCmd = fmt::format("{}", FLAGS_GETIP_CMD);
        std::string strRet = execute->exec(strCmd);

        std::vector<std::string> results;
        strtk::parse(strRet, " ", results);
        if (results.size() >= 7 && results[1] == "inet")
        {
            std::string ip = results[2];


            std::string strData = DMLoadFile(fmt::format(R"({}{})", getenv("windir"), R"(\System32\drivers\etc\hosts)"));

            std::vector<std::string> lines;
            strtk::parse(strData, "\n", lines);

            bool change = false;
            for (auto& line : lines)
            {
                auto it = strtk::ifind(FLAGS_SET_WSL_HOST_NAME, line);
                if (it != std::string::npos)
                {
                    line = fmt::format("{} {}", ip, FLAGS_SET_WSL_HOST_NAME);

                    strData = strtk::join("\n", lines);
                    change = true;
                    break;
                }
            }

            if (!change)
            {
                strData += fmt::format("{} {}\n", ip, FLAGS_SET_WSL_HOST_NAME);
            }

            bool bRet = DMWriteFile(fmt::format(R"({}{})", getenv("windir"), R"(\System32\drivers\etc\hosts)"), strData);
            if (!bRet)
            {
                fmt::print("DMWriteFile failed. please run with root.\n");
                return -1;
            }
            fmt::print("Done\n");
        }

    }

    return 0;
}
