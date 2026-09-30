/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { describe, it, expect } from 'vitest';

import { TestBase } from './TestBase';
import { Application } from '../src/Application';
import * as api from '@datatypes/api/Version';

let testbase = new TestBase();

describe('Version', () => {
    it('GET /version', async () => {
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/version'
        });

        expect(response.statusCode).toBe(200);
        expect(api.GetVersionResponseSchema.safeParse(response.body)).toBeTruthy();
        expect(response.body.VERSION_STRING).not.toBe('');
    });
});
