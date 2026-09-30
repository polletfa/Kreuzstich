/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type * as wasm from './wrapper-wasm';

export namespace ColorSpace {
    export type ColorRGBA = wasm.ColorSpace_ColorRGBA;
    export type ColorHSL = wasm.ColorSpace_ColorHSL;
    export type ColorLAB = wasm.ColorSpace_ColorLAB;
    export type DistanceAlgo = wasm.ColorSpace_DistanceAlgo;
}

export interface ColorSpace {
    rgbaEquals: (lhs: ColorSpace.ColorRGBA, rhs: ColorSpace.ColorRGBA) => boolean;
    compositeRGBAOntoBackground: (col: ColorSpace.ColorRGBA, bg: ColorSpace.ColorRGBA) => ColorSpace.ColorRGBA;
    toHSL: (rgba: ColorSpace.ColorRGBA) => ColorSpace.ColorHSL;
    toLAB: (rgba: ColorSpace.ColorRGBA) => ColorSpace.ColorLAB;
    distance: (col1: ColorSpace.ColorLAB, col2: ColorSpace.ColorLAB, algo: ColorSpace.DistanceAlgo) => number;
}

export function ColorSpace(core: wasm.MainModule): ColorSpace {
    return {
        rgbaEquals: core.ColorSpace_rgbaEquals,
        compositeRGBAOntoBackground: core.ColorSpace_compositeRGBAOntoBackground,
        toHSL: core.ColorSpace_toHSL,
        toLAB: core.ColorSpace_toLAB,
        distance: core.ColorSpace_distance
    };
}
