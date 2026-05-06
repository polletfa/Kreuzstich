/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

// Note: we only check the bindings, not the functionality, which is tested directly in the core component.

import { describe, it, expect, beforeAll } from 'vitest';
import * as Core from './build/wrapper-wasm';

let core: Core.Module;

beforeAll(async () => {
    core = await Core.load();
});

describe('ColorSpace', () => {
    it('rgbaEquals', () => {
        expect(core.ColorSpace.rgbaEquals({red: 1, green: 2, blue: 3, alpha: 4}, {red: 1.1, green: 2, blue: 3, alpha: 4})).toBe(true);
    });

    it('compositeRGBAOntoBackground', () => {
        expect(core.ColorSpace.compositeRGBAOntoBackground({red: 59, green: 130, blue: 246, alpha: 204}, {red: 1, green: 2, blue: 3, alpha: 255}))
            .toEqual({red: 47, green: 104, blue: 197, alpha: 255});
    });

    it('toHSL', () => {
        const res = core.ColorSpace.toHSL({red: 123, green: 45, blue: 67, alpha: 255});
        expect(res.hue).toBeCloseTo(343.08);
        expect(res.saturation).toBeCloseTo(0.4643);
        expect(res.lightness).toBeCloseTo(0.3294);
    });

    it('toLAB', () => {
        const res = core.ColorSpace.toLAB({red: 123, green: 45, blue: 67, alpha: 255});
        expect(res.lightness).toBeCloseTo(30.6264);
        expect(res.a).toBeCloseTo(36.0117);
        expect(res.b).toBeCloseTo(4.1579);
    });

    it('distance', () => {
        expect(core.ColorSpace.distance({lightness: 64, a: 12, b: -48}, {lightness: 79, a: 95, b: 10}, "CIE1976")).toBeCloseTo(102.3621);
        expect(core.ColorSpace.distance({lightness: 64, a: 12, b: -48}, {lightness: 79, a: 95, b: 10}, "CIEDE2000")).toBeCloseTo(42.9367);
        // with wrong enum, default to CIE1976, which is fine
        // but it will cause a TypeScript error anyway
        expect(core.ColorSpace.distance({lightness: 64, a: 12, b: -48}, {lightness: 79, a: 95, b: 10}, "wrong" as Core.ColorSpace.DistanceAlgo)).toBeCloseTo(102.3621);
    });
});
