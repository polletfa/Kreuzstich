/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/


// todo just a test for now!
import { describe, it, expect, beforeAll, beforeEach } from 'vitest';

import { Application } from '../src/Application';

let app: Application;

beforeAll(() => {
    //todo maybe create a testbase file or something. We will probably need this for lots of tests
    process.env.KREUZSTICH_DATA_WEB_PORT=80
    process.env.KREUZSTICH_DATA_WEB_DB_HOST="localhost";
    process.env.KREUZSTICH_DATA_WEB_DB_PORT="5555";
    process.env.KREUZSTICH_DATA_WEB_DB_DB="test";
    process.env.KREUZSTICH_DATA_WEB_DB_USER="test";
    process.env.KREUZSTICH_DATA_WEB_DB_PASSWORD="test";
    process.env.KREUZSTICH_DATA_WEB_JWT_SECRET="test";
});

beforeEach(async () => {
    app = new Application(/* disableLogs: */ true);
});

describe('Routing /version', () => {
    it('/version', async () => {
        const response = await app.get().inject({
            method: 'GET',
            url: '/version'
        });

        expect(response.statusCode).toBe(200);
    });
});
