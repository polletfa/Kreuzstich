/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import * as wasm from './wrapper-wasm';
import { Version } from './Version';
import { ColorSpace } from './ColorSpace'
import { Thread, ThreadConstructor } from './Thread';
import { ThreadList, ThreadListConstructor } from './ThreadList';

// Polyfill for Symbol.dispose
if (typeof Symbol !== "undefined" && !Symbol.dispose) {
  Object.defineProperty(Symbol, "dispose", {
    value: Symbol("Symbol.dispose"),
    configurable: false,
    enumerable: false,
    writable: false
  });
}

export {
    Version,
    ColorSpace,
    Thread,
    ThreadList
};

export class Module {
    constructor(core: wasm.MainModule) {
        this.Version = Version(core);
        this.ColorSpace = ColorSpace(core);
        this.Thread = ThreadConstructor(core);
        this.ThreadList = ThreadListConstructor(core);
    }

    Version: Version;
    ColorSpace: ColorSpace;
    Thread: ThreadConstructor;
    ThreadList: ThreadListConstructor;
}

export async function load(locateFile?: (file:string, prefix: string)=>string): Promise<Module> {
    const wasmModule = await wasm.default({locateFile});
    return new Module(wasmModule);
}
