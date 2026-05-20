/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { describe, it, expect, beforeAll } from 'vitest';

import { TestBase } from './TestBase';
import { Application } from '../src/Application';
import * as api from '@datatypes/api/User';

const testbase = new TestBase();

beforeAll(async () => {
    await testbase.setupDatabase('UserService');

    // Insert test data into database
    await Application.instance.database.query(`INSERT INTO users(email, name, password) VALUES('test@kreuzstich.art', 'test user', '$2b$10$ZRGfENwLyrvD9/50ozR/Bu572DM53/cyJKgUx08XjC/e9SUcmIRzK');`);
});

describe('UserService', () => {
    it('POST /login, wrong password', async () => {
        const response = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'wrong password',
                persist: false
            }
        });

        expect(response.statusCode).toBe(401);
        expect(response.json()).toEqual({ error: 'Unauthorized' });
        expect(response.cookies.length).toBe(0); // no cookies
    });

    it('POST /login, correct password', async () => {
        const response = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'test',
                persist: false
            }
        });

        expect(response.statusCode).toBe(200);
        expect(response.json().email).toEqual('test@kreuzstich.art');
        expect(response.json().name).toEqual('test user');
        expect(response.json().password).toBe(undefined);
        expect(response.cookies[0].name).toEqual('access-token'); // cookie set
        expect(response.cookies[0].maxAge).toEqual(undefined); // expire on close
    });

    it('POST /login, correct password, keep me logged in', async () => {
        const response = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'test',
                persist: true
            }
        });

        expect(response.statusCode).toBe(200);
        expect(response.json().email).toEqual('test@kreuzstich.art');
        expect(response.json().name).toEqual('test user');
        expect(response.json().password).toBe(undefined);
        expect(response.cookies[0].name).toEqual('access-token'); // cookie set
        expect(response.cookies[0].maxAge).toEqual(60*60*24*30); // expire after 30d
    });

    it('GET /status, not logged in', async () => {
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/user/status'
        });

        expect(response.statusCode).toBe(401);
        expect(response.json()).toEqual({ error: 'Unauthorized' });
        expect(response.cookies.length).toBe(0); // no cookie set/changed
    });

    it('GET /status, logged in', async () => {
        const loginResp = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'test',
                persist: false
            }
        });
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/user/status',
            cookies: { 'access-token': loginResp.cookies[0].value }
        });

        expect(response.statusCode).toBe(200);
        expect(response.json().email).toEqual('test@kreuzstich.art');
        expect(response.json().name).toEqual('test user');
        expect(response.json().password).toBe(undefined);
        expect(response.cookies.length).toBe(0); // no cookie set/changed
    });

    it('GET /logout', async () => {
        const loginResp = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'test',
                persist: false
            }
        });
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/user/logout',
            cookies: { 'access-token': loginResp.cookies[0].value }
        });

        expect(response.statusCode).toBe(200);
        expect(response.json()).toEqual({success: true});
        expect(response.cookies[0].name).toBe('access-token');
        expect(response.cookies[0].maxAge).toBe(0); // token invalidated
    });
});

describe('UserService, database error', () => {
    beforeAll(async () => {
        await Application.instance.database.query('DROP TABLE users CASCADE;');
    });

    it('POST /login', async () => {
        const response = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'test',
                persist: false
            }
        });

        expect(response.statusCode).toBe(500);
        expect(response.json()).toEqual({error: "relation \"users\" does not exist"});
        expect(response.cookies.length).toBe(0); // no cookie set/changed
    });
});
