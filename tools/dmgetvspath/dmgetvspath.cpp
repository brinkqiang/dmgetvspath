
#include "execute.h"
#include "dmformat.h"
#include "dmstrtk.hpp"
#include "dmutil.h"

#include "dmflags.h"

DEFINE_string(VS_VERSION, "2019", "VS version");
DEFINE_string(VS_BIT, "amd64", "x86/amd64");

int main(int argc, char* argv[])
{
    DMFLAGS_INIT(argc, argv);

    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        std::string strCwd = DMGetWorkPath();

        std::string strCmd = fmt::format(R"(vswhere)");
        std::string strRet = execute->exec(strCmd);


		std::vector<std::string> vecList;

		auto startPos = strRet.find("installationPath: ");
		if (startPos != std::string::npos)
		{
			startPos += std::string("installationPath: ").length(); // 跳过 'installationPath:' 的长度
			auto endPos = strRet.find_first_of("\n", startPos); // 假设路径后有换行符

			if (endPos != std::string::npos)
			{
				std::string strPath = strRet.substr(startPos, endPos - startPos);
				strPath = strPath + R"(\VC\Auxiliary\Build\vcvarsall.bat)"; // 构造完整的路径

				vecList.push_back(strPath);
			}
		}

        for (auto str : vecList)
        {
            auto it = str.find(FLAGS_VS_VERSION);
            if (it != std::string::npos)
            {
                std::string strCmd2 = fmt::format(R"(call "{}" {})", str, FLAGS_VS_BIT);
                std::string strRet2 = execute->exec(strCmd2);

                fmt::print("{}\n", strCmd2);
                return 0;
            }
        }

    }

    return 0;
}
