
#include "execute.h"
#include "dmformat.h"
#include "dmstrtk.hpp"
#include "dmutil.h"

#include "dmflags.h"

DEFINE_string(VS_BIT, "x64", "x86 | amd64 | x86_amd64 | x86_arm | x86_arm64 | amd64_x86 | amd64_arm | amd64_arm64");
// for /f "delims=" %%i in ('vswhere -latest -property installationPath') do call "%%i\VC\Auxiliary\Build\vcvarsall.bat" x64

int main(int argc, char* argv[])
{
    DMFLAGS_INIT(argc, argv);

    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        std::string strCwd = DMGetWorkPath();

        std::string strCmd = fmt::format(R"(vswhere -latest -property installationPath)");
        std::string strRet = execute->exec(strCmd);

        strRet = strtk::replace("\n", "", strRet);

		std::string strPath = strRet + R"(\VC\Auxiliary\Build\vcvarsall.bat)"; // 构造完整的路径

        std::string strCmd2 = fmt::format(R"(call "{}" {})", strPath, FLAGS_VS_BIT.c_str());
        std::string strRet2 = execute->exec(strCmd2);

        return 0;
    }

    return 0;
}
