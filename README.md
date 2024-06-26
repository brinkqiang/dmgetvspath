# dmgetvspath

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmgetvspath](https://img.shields.io/badge/brinkqiang-dmgetvspath-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmgetvspath)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmgetvspath/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmgetvspath.svg?label=Stars)](https://github.com/brinkqiang/dmgetvspath) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmgetvspath.svg?label=Fork)](https://github.com/brinkqiang/dmgetvspath)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmgetvspath/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmgetvspath/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmgetvspath/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmgetvspath/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmgetvspath/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmgetvspath/actions/workflows/win.yml "win build status"

## Intro
dmgetvspath
```
dmgetvspath -VS_BIT=amd64 -VS_NAME=Enterprise -VS_VERSION=2019
```

output
```
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64
```

use in bat
```
for /F "tokens=*" %%i in ('dmgetvspath -VS_BIT=amd64 -VS_NAME=Enterprise -VS_VERSION=2019') do ( 
    set vscmd=%%i
)

%vscmd%

```

dmgetvspath_fastbuild_patch  
- fix vs2019 fastbuild build bug
```
dmgetvspath_fastbuild_patch -VS_NAME=Enterprise -VS_VERSION=2019
```
output
```
patch done path: C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\Microsoft.Common.CurrentVersion.targets
```

## Contacts

## Thanks
