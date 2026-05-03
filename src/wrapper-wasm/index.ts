/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import * as wasm from './wrapper-wasm';
import { Version } from './Version';
import { ColorSpace } from './ColorSpace'
import { Thread, ThreadConstructor } from './Thread';

export {
    Version,
    ColorSpace,
    Thread
};

export class Module {
    constructor(private core: wasm.MainModule) {
        this.Version = Version(core);
        this.ColorSpace = ColorSpace(core);
        this.Thread = ThreadConstructor(core);
    }

    Version: Version;
    ColorSpace: ColorSpace;
    Thread: ThreadConstructor;
}

export async function load(locateFile?: (file:string)=>string): Promise<Module> {
    const wasmModule = await wasm.default({locateFile});
    return new Module(wasmModule);
}
