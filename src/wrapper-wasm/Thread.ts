/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { ColorSpace } from './ColorSpace';
import type * as wasm from './wrapper-wasm';

export class Thread {
    constructor(private obj: wasm.Thread) {}

    delete() { this.obj.delete(); }
    isDeleted(): boolean { return this.obj.isDeleted(); }

    isValid(): boolean {  return this.obj.isValid(); }

    equals(other: Thread | ColorSpace.ColorRGBA): boolean {
        if(other instanceof Thread) {
            return this.obj.equalsToThread(other.obj);
        } else {
            return this.obj.equalsToColorRGBA(other);
        }
    }

    name(): string { return this.obj.name(); }
    color(): ColorSpace.ColorRGBA { return this.obj.color(); }
    hsl(): ColorSpace.ColorHSL { return this.obj.hsl(); }

    distance(other: Thread | ColorSpace.ColorLAB, algo: ColorSpace.DistanceAlgo): number {
        if(other instanceof Thread) {
            return this.obj.distanceFromThread(other.obj, algo);
        } else {
            return this.obj.distanceFromColorLAB(other, algo);
        }
    }
}

export interface ThreadConstructor {
    new(name: wasm.EmbindString, colorString: wasm.EmbindString): Thread
};

export function ThreadConstructor(core: wasm.MainModule): ThreadConstructor {
    return class extends Thread {
        constructor(name: wasm.EmbindString, colorString: wasm.EmbindString) {
            super(new core.Thread(name, colorString));
        }
    };
}
