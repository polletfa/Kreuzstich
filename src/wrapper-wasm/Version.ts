/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type * as wasm from './wrapper-wasm';

export interface Version {
    readonly NAME: wasm.EmbindString;
    readonly WEBSITE: wasm.EmbindString;
    readonly MAJOR: number;
    readonly MINOR: number;
    readonly BUILD_TIME: wasm.EmbindString;
    readonly GIT_COMMIT: wasm.EmbindString;
    readonly RELEASE_BUILD: boolean;
    readonly LICENSE: wasm.EmbindString;

    getVersionString(): string;
    replaceVersionVars(str: wasm.EmbindString): string;
}

export function Version(core: wasm.MainModule): Version {
    return {
        NAME: core.Version_NAME,
        WEBSITE: core.Version_WEBSITE,
        MAJOR: core.Version_MAJOR,
        MINOR: core.Version_MINOR,
        BUILD_TIME: core.Version_BUILD_TIME,
        GIT_COMMIT: core.Version_GIT_COMMIT,
        RELEASE_BUILD: core.Version_RELEASE_BUILD,
        LICENSE: core.Version_LICENSE,
        getVersionString: core.Version_getVersionString,
        replaceVersionVars: core.Version_replaceVersionVars
    };
}
