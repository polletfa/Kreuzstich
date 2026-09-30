/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { describe, it, expect } from 'vitest';

import { Helpers } from '../src/Helpers';

describe('Helpers', () => {
    it('errorToString, error object', async () => {
        expect(Helpers.errorToString(new Error('test'))).toBe('test');
    });

    it('errorToString, other object', async () => {
        expect(Helpers.errorToString({error: 'test'})).toBe('unknown');
    });
});
