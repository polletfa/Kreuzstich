/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

interface Version {
    NAME: string,
    WEBSITE: string,
    MAJOR: number,
    MINOR: number,
    BUILD_TIME: number,
    GIT_COMMIT: string,
    RELEASE_BUILD: boolean,
    LICENSE: string,

    getVersionString: ()=>void
    replaceVersionVars: (string)=>string
}
