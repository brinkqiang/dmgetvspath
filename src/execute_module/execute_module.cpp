
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "execute_module.h"
#define BUFFER_SIZE 256

#ifdef WIN32
#define popen _popen
#define pclose _pclose

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

#endif
#include <memory>

std::string DMExecute(const char* cmd)
{
    std::string result;

    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

    if (!pipe)
    {
        return result;
    }

    while (!feof(pipe.get()))
    {
        char szBuf[BUFFER_SIZE + 1] = { 0 };

        if (fgets(szBuf, BUFFER_SIZE, pipe.get()) != nullptr)
        {
            result += szBuf;
        }
    }

    return result;
}

static inline uint32_t GetTickCount32()
{
#ifdef _MSC_VER
    return ::GetTickCount();
#else
    struct timespec ts = { 0 };
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
}

Cexecute_module::Cexecute_module()
{

}

Cexecute_module::~Cexecute_module()
{

}

void DMAPI Cexecute_module::Release(void)
{
    delete this;
}

std::string DMAPI Cexecute_module::exec(const std::string& strCmd)
{
    uint32_t start = GetTickCount32();
    std::string strRet = DMExecute(strCmd.c_str());
    uint32_t end = GetTickCount32();
    std::cout << strRet << std::endl;
    std::cout << end - start << " ms" << std::endl;

    return strRet;
}

Iexecute* DMAPI executeGetModule()
{
    return new Cexecute_module();
}
