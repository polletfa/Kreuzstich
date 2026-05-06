/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

// Note: we only check the bindings, not the functionality, which is tested directly in the core component.

import { describe, it, expect, beforeAll, beforeEach, afterEach } from 'vitest';
import * as Core from './build/wrapper-wasm';

let core: Core.Module;

beforeAll(async () => {
    core = await Core.load();
});

describe('Thread', () => {
    let thread: Core.Thread;

    beforeEach(() => {
        thread = new core.Thread("Test", "7b2d43");
    });

    afterEach(() => {
        if(!thread.isDeleted()) {
            thread.delete();
        }
    });

    it('delete/isDeleted', () => {
        expect(thread.isDeleted()).toBe(false);
        thread.delete();
        expect(thread.isDeleted()).toBe(true);
    });

    it('isValid', () => {
        expect(thread.isValid()).toBe(true);
    });

    it('equals:Thread', () => {
        const thr2 = new core.Thread("Test2", "7b2d43");
        expect(thread.equals(thr2)).toBe(true);
        thr2.delete();
    });

    it('equals:ColorRGBA', () => {
        expect(thread.equals({red: 123, green: 45, blue: 67, alpha: 255})).toBe(true);
    });

    it('name', () => {
        expect(thread.name()).toBe('Test');
    });

    it('color', () => {
        expect(thread.color()).toEqual({red: 0x7b, green: 0x2d, blue: 0x43, alpha: 255});
    });

    it('hsl', () => {
        const res = thread.hsl();
        expect(res.hue).toBeCloseTo(343.08);
        expect(res.saturation).toBeCloseTo(0.4643);
        expect(res.lightness).toBeCloseTo(0.3294);
    });

    it('distance:Thread', () => {
        const thr2 = new core.Thread("Test2", "0c4e29");
        expect(thread.distance(thr2, "CIE1976")).toBeCloseTo(66.7232);
        thr2.delete();
    });

    it('distance:ColorRGBA', () => {
        expect(thread.distance({lightness: 28.6077, a: -29.5564, b: 16.3536}, "CIE1976")).toBeCloseTo(66.7232);
    });
});
