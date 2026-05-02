/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

namespace ColorSpace {
    interface ColorRGBA {
        red: number;
        green: number;
        blue: number;
        alpha: number;
    }

    interface ColorHSL {
        hue: number;
        saturation: number;
        lightness: number;
    }

    interface ColorLAB {
        lightness: number;
        a: number;
        b: number;
    }

    type DistanceAlgo = "CIE1976"|"CIEDE2000";
}

interface ColorSpace {
    rgbaEquals: (lhs: ColorSpace.ColorRGBA, rhs: ColorSpace.ColorRGBA) => bool;
    compositeRGBAOntoBackground: (rgba: ColorSpace.ColorRGBA, bg: ColorSpace.ColorRGBA) => ColorSpace.ColorRGBA;
    toHSL: (rgba: ColorSpace.ColorRGBA) => ColorSpace.ColorHSL;
    toLAB: (rgba: ColorSpace.ColorRGBA) => ColorSpace.ColorLAB;
    distance: (color1: ColorSpace.ColorLAB, color2: ColorSpace.ColorLAB, algo: ColorSpace.DistanceAlgo) => number;
}
